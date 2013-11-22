// This file handles drawing the world to screen
#ifndef _RENDERER
#define _RENDERER

#include <android/log.h>
#include <EGL/egl.h>
#include <GLES2/gl2.h>
#include <GLES2/gl2ext.h>

#include <btBulletDynamicsCommon.h>

#include <time.h>
#include <memory>

#undef NDEBUG

#ifdef NDEBUG
#define LOGI(...)
#define LOGW(...)
#define LOGE(...)
#else
#define LOGI(...) ((void)__android_log_print(ANDROID_LOG_INFO, "native-activity", __VA_ARGS__))
#define LOGW(...) ((void)__android_log_print(ANDROID_LOG_WARN, "native-activity", __VA_ARGS__))
#define LOGE(...) ((void)__android_log_print(ANDROID_LOG_ERROR, "nEngine", __VA_ARGS__))
#endif // NDEBUG

class Renderer
{
private:
    //Linking stuff
    ANativeWindow*& window;
    btCollisionObjectArray& collisionObjects;// this is a typedef for btAlignedObjectArray<class btCollisionObject*>, which is a vector wrapper
    //Display stuff
    EGLDisplay display;
    EGLSurface surface;
    EGLContext context;
    EGLint windowWidth, windowHeight;
    //openGL stuff
    GLuint glProgramHandle;
    void drawCollisionObject(btCollisionObject* collisionObject);

public:
    Renderer(btCollisionObjectArray& _collisionObjects, ANativeWindow*& _window): collisionObjects(_collisionObjects), window(_window){}
    int init();
    void drawFrame();
    void terminate();
};
//Putting these here b/c they don't need to be dynamically assigned to each instance of renderer.
//Unless I decide to make the user-definable, that is. In that case I'd have to read them in from a file
static const char fragmentShaderSrc[] =
    "precision mediump float;"
    "void main()"
    "{"
    "   gl_FragColor = vec4(1.0, 0.0, 0.0, 1.0);"
    "}";
static const char vertexShaderSrc[] =
    "attribute vec4 vPosition;"
    "void main()"
    "{"
    "   gl_Position = vPosition;"
    "}";
static const EGLint attribs[] =
{
        EGL_RENDERABLE_TYPE, EGL_OPENGL_ES2_BIT,
        EGL_SURFACE_TYPE, EGL_WINDOW_BIT,
        EGL_BLUE_SIZE, 8,
        EGL_GREEN_SIZE, 8,
        EGL_RED_SIZE, 8,
        EGL_NONE
};
static const EGLint attribList[] =
{
    EGL_CONTEXT_CLIENT_VERSION, 2,
    EGL_NONE
};

/**
 * Compile an openGL shader
 * Return: the compiled shader
 */
static GLuint compileShader(GLenum shaderType, const char* shaderSrc)
{
    GLuint shaderHandle = glCreateShader(shaderType);
    assert(shaderHandle && "Invalid shaderType");
    glShaderSource(shaderHandle, 1, &shaderSrc, NULL);
    glCompileShader(shaderHandle);
    #ifndef NDEBUG
        GLint compiled;
        glGetShaderiv(shaderHandle, GL_COMPILE_STATUS, &compiled);
        if(!compiled)
        {
            GLint infoMsgLength = 0;
            glGetShaderiv(shaderHandle, GL_INFO_LOG_LENGTH, &infoMsgLength);
            if(infoMsgLength > 1)
            {
                char* infoLogEntry = new char[infoMsgLength];//malloc(sizeof(char)*infoMsgLength);
                glGetShaderInfoLog(shaderHandle, infoMsgLength, NULL, infoLogEntry);
                LOGE("Error compiling shader:\n%s\n", infoLogEntry);
                delete[] infoLogEntry;//free(infoLogEntry);
            }
            glDeleteShader(shaderHandle);
            return 0;
        }
    #endif // DEBUG
    return shaderHandle;
}

/**
 * Create an openGL program and attach shaders
 * Return: the created program's handle
 */
static GLuint initGLProgram(const char* vertexShaderSrc, const char* fragmentShaderSrc)
{
    GLuint vertexShaderHandle = compileShader(GL_VERTEX_SHADER, vertexShaderSrc);
    GLuint fragmentShaderHandle = compileShader(GL_FRAGMENT_SHADER, fragmentShaderSrc);
    GLuint programHandle = glCreateProgram();
    assert(programHandle && "Error creating program");
    glAttachShader(programHandle, vertexShaderHandle);
    glAttachShader(programHandle, fragmentShaderHandle);
    glBindAttribLocation(programHandle, 0, "vPosition");// Not sure why this is necessary
    glLinkProgram(programHandle);
    #ifndef NDEBUG
        GLint programLinked;
        glGetProgramiv(programHandle, GL_LINK_STATUS, &programLinked);
        if(!programLinked)
        {
            GLint infoMsgLength = 0;
            glGetProgramiv(programHandle, GL_INFO_LOG_LENGTH, &infoMsgLength);
            if(infoMsgLength > 1)
            {
                char* infoLogEntry = new char[infoMsgLength];//malloc(sizeof(char)*infoMsgLength);
                glGetProgramInfoLog(programHandle, infoMsgLength, NULL, infoLogEntry);
                LOGE("Error linking program:\n%s\n", infoLogEntry);
                delete[] infoLogEntry;//free(infoLogEntry);
            }
            glDeleteProgram(programHandle);
            return 0;
        }
    #endif // NDEBUG
    glUseProgram(programHandle);// Should I call this more often??
    return programHandle;
}

/**
 * Initialize an EGL context for the current display
 * Return: 1 if no errors, otherwise the ID of the error encountered
 */
int Renderer::init()
{
    EGLint format;
    EGLint numConfigs;
    EGLConfig config;
    display = eglGetDisplay(EGL_DEFAULT_DISPLAY);
    eglInitialize(display,0,0);
    eglChooseConfig(display, attribs, &config, 1, &numConfigs);
    eglGetConfigAttrib(display, config, EGL_NATIVE_VISUAL_ID, &format);
    ANativeWindow_setBuffersGeometry(window, 0, 0, format);

    surface = eglCreateWindowSurface(display, config,  window, NULL);
    context = eglCreateContext(display, config, NULL, attribList);

    eglMakeCurrent(display, surface, surface, context);

    eglQuerySurface(display, surface, EGL_WIDTH, &windowWidth);
    eglQuerySurface(display, surface, EGL_HEIGHT, &windowHeight);
//    LOGE("display dimensions: %d, %d", windowWidth, windowHeight);
    // Initialize GL state.
    glProgramHandle = initGLProgram(vertexShaderSrc, fragmentShaderSrc);
    glEnable(GL_CULL_FACE);
    glEnable(GL_DEPTH_TEST);
    LOGE("Renderer initialized");
    return 1;
}

/**
 * Tear down the EGL context currently associated with the display.
 */
void Renderer::terminate()
{
    if(display != EGL_NO_DISPLAY)
    {
        eglMakeCurrent(display, EGL_NO_SURFACE, EGL_NO_SURFACE, EGL_NO_CONTEXT);
        if(context != EGL_NO_CONTEXT) eglDestroyContext(display, context);
        if(surface != EGL_NO_SURFACE) eglDestroySurface(display, surface);
        eglTerminate(display);
    }
    display = EGL_NO_DISPLAY;
    context = EGL_NO_CONTEXT;
    surface = EGL_NO_SURFACE;
    LOGE("Renderer terminated");
}

void Renderer::drawFrame()
{
    assert((display != NULL || display != EGL_BAD_DISPLAY) && "Display not ready");

    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
//    LOGE("Num collision objects: %d", collisionObjects.size());
    for(int i = 0; i < collisionObjects.size(); i++)
    {
        drawCollisionObject(collisionObjects[i]);
    }
//    GLfloat vVertices[] = {0.0f, 0.5f, 0.0f,
//        -0.5f, -0.5f, 0.0f,
//        0.5f, -0.5f, 0.0f};
//    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, vVertices);
//    glEnableVertexAttribArray(0);
//    glDrawArrays(GL_TRIANGLES, 0, 3);

    eglSwapBuffers(display,surface);
//    LOGE("FRAME DRAWN");
}

void Renderer::drawCollisionObject(btCollisionObject* collisionObject)
{
    btScalar worldTransform[16];//This will only ever hold 15 elements, but maybe 16 is better for memory alignment?
    collisionObject->getInterpolationWorldTransform().getOpenGLMatrix(worldTransform);
    for(int n = 0; n < 16; n++){
        LOGE("worldTransform[%d]: %f",n,worldTransform[n]);
    }
    btCollisionShape* collisionShape = collisionObject->getCollisionShape();
    switch(collisionShape->getShapeType())
    {
        case CUSTOM_CONVEX_SHAPE_TYPE:
        {
            break;
        }
        case BOX_SHAPE_PROXYTYPE:
        {
            btBoxShape* boxShape = static_cast<btBoxShape*>(collisionShape);
            btVector3 halfExtents = boxShape->getHalfExtentsWithMargin();
            LOGE("BoxShape HalfExtents: %f, %f, %f",halfExtents[0],halfExtents[1],halfExtents[2]);
            break;
        }
        case UNIFORM_SCALING_SHAPE_PROXYTYPE:
            break;
        case COMPOUND_SHAPE_PROXYTYPE:
            break;
        case SPHERE_SHAPE_PROXYTYPE:
            break;
    }
}

#endif // _RENDERER