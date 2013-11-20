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

#define DEBUG

#ifdef DEBUG
#define LOGI(...) ((void)__android_log_print(ANDROID_LOG_INFO, "native-activity", __VA_ARGS__))
#define LOGW(...) ((void)__android_log_print(ANDROID_LOG_WARN, "native-activity", __VA_ARGS__))
#define LOGE(...) ((void)__android_log_print(ANDROID_LOG_ERROR, "nEngine", __VA_ARGS__))
#else
#define LOGI(...)
#define LOGW(...)
#define LOGE(...)
#endif // DEBUG

struct Renderer
{
    //Linking stuff
    ANativeWindow** window;
//    btCollisionObjectArray* collisionObjects;// this is a typedef for btAlignedObjectArray<class btCollisionObject*>, which is a vector wrapper
    btDiscreteDynamicsWorld* dynamicsWorld;
    //Display stuff
    EGLDisplay display;
    EGLSurface surface;
    EGLContext context;
    int32_t width;
    int32_t height;
    //openGL stuff
    GLuint glProgramHandle;

    int init();
    void link(btDiscreteDynamicsWorld* dynamicsWorld, ANativeWindow** window);
    void drawFrame();
    void terminate();
    GLuint compileShader(GLenum shaderType, const char* shaderSrc);
    GLuint createProgram(const char* vertexShaderSrc, const char* fragmentShaderSrc);
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
 * Link this instance to an app and an engine
 */
void Renderer::link(btDiscreteDynamicsWorld* dynamicsWorld, ANativeWindow** window)
{
    this->dynamicsWorld = dynamicsWorld;
    this->window = window;
}

/**
 * Initialize an EGL context for the current display
 * Return: 0 if no errors, otherwise the ID of the error encountered
 */
int Renderer::init()
{
    LOGE("renderer init called");
    EGLint w, h, dummy, format;
    EGLint numConfigs;
    EGLConfig config;
    EGLSurface surface;
    EGLContext context;
    EGLDisplay display = eglGetDisplay(EGL_DEFAULT_DISPLAY);
    eglInitialize(display,0,0);
    /* Here, the application chooses the configuration it desires. In this
     * sample, we have a very simplified selection process, where we pick
     * the first EGLConfig that matches our criteria
     * TODO: find this function's declaration and fix if necessary
     */
    eglChooseConfig(display, attribs, &config, 1, &numConfigs);
    /* EGL_NATIVE_VISUAL_ID is an attribute of the EGLConfig that is
     * guaranteed to be accepted by ANativeWindow_setBuffersGeometry().
     * As soon as we picked a EGLConfig, we can safely reconfigure the
     * ANativeWindow buffers to match, using EGL_NATIVE_VISUAL_ID. */
    eglGetConfigAttrib(display, config, EGL_NATIVE_VISUAL_ID, &format);
    ANativeWindow_setBuffersGeometry(*window, 0, 0, format);

    surface = eglCreateWindowSurface(display, config,  *window, NULL);
    context = eglCreateContext(display, config, NULL, attribList);

    if (eglMakeCurrent(display, surface, surface, context) == EGL_FALSE)
    {
        LOGE("Unable to eglMakeCurrent");
        return 1;
    }

    eglQuerySurface(display, surface, EGL_WIDTH, &w);
    eglQuerySurface(display, surface, EGL_HEIGHT, &h);
//    LOGE("display dimensions: %d, %d", w, h);

    this->display = display;
    this->context = context;
    this->surface = surface;
    width = w;
    height = h;
    LOGE("GL init started");
    // Initialize GL state.
    glEnable(GL_CULL_FACE);
    glEnable(GL_DEPTH_TEST);// Originally glDisable
    glProgramHandle = createProgram(vertexShaderSrc, fragmentShaderSrc);
//    LOGE("Program handle: %d",glProgramHandle);
    glLinkProgram(glProgramHandle);
    LOGE("FLAG1");
    #ifdef DEBUG
        GLint programLinked;
        glGetProgramiv(glProgramHandle, GL_LINK_STATUS, &programLinked);
        LOGE("FLAG2");
        if(!programLinked)
        {
            GLint infoMsgLength = 0;
            glGetProgramiv(glProgramHandle, GL_INFO_LOG_LENGTH, &infoMsgLength);
            LOGE("FLAG3");
            if(infoMsgLength > 1)
            {
                LOGE("Flag4");
                char* infoLogEntry = new char[infoMsgLength];//malloc(sizeof(char)*infoMsgLength);
                glGetProgramInfoLog(glProgramHandle, infoMsgLength, NULL, infoLogEntry);
                LOGE("Error linking program:\n%s\n", infoLogEntry);
                delete[] infoLogEntry;//free(infoLogEntry);
            }
            glDeleteProgram(glProgramHandle);
            return 2;
        }
    #endif // DEBUG
    LOGE("FLAG10");
    glUseProgram(glProgramHandle);// Should I call this more often??
    LOGE("GL init finished");
    return 0;
}

/**
 * Compile an openGL shader
 * Return: the compiled shader
 */
GLuint Renderer::compileShader(GLenum shaderType, const char* shaderSrc)
{
    GLuint shaderHandle = glCreateShader(shaderType);
    #ifdef DEBUG
        if(!shaderHandle)
        {
            LOGE("Invalid Shader Type");
            return 0;
        }
    #endif // DEBUG
    glShaderSource(shaderHandle, 1, &shaderSrc, NULL);
    glCompileShader(shaderHandle);
    #ifdef DEBUG
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
 * Return: the created program
 */
GLuint Renderer::createProgram(const char* vertexShaderSrc, const char* fragmentShaderSrc)
{
    GLuint vertexShaderHandle = compileShader(GL_VERTEX_SHADER, vertexShaderSrc);
    GLuint fragmentShaderHandle = compileShader(GL_FRAGMENT_SHADER, fragmentShaderSrc);
    GLuint programHandle = glCreateProgram();
    #ifdef DEBUG
    if(!programHandle)
    {
        LOGE("Error creating program");
        return 0;
    }
    #endif // DEBUG
    glAttachShader(programHandle, vertexShaderHandle);
    glAttachShader(programHandle, fragmentShaderHandle);
//    glBindAttribLocation(programHandle, 0, "vPosition");// Not sure why this is necessary
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
}

void Renderer::drawFrame()
{
    if(display == NULL)
    {
//        LOGE("Display not ready");
        return;
    }

    // Temp test function: just fill the screen with a color
    timespec t;
    clock_gettime(CLOCK_MONOTONIC, &t);
//    glClearColor((float)(t.tv_sec%3)/3.0, (float)((t.tv_sec+1)%3)/3.0, (float)((t.tv_sec+2)%3)/3.0, 1);
//    glClearColor(1,0,0,1);

    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);


    for(int i = 0; i < dynamicsWorld->getNumCollisionObjects(); i++)
    {
        btCollisionObject* collisionObject = dynamicsWorld->getCollisionObjectArray()[i];
        btScalar worldTransform[16];
        collisionObject->getInterpolationWorldTransform().getOpenGLMatrix(worldTransform);
        switch(collisionObject->getCollisionShape()->getShapeType())
        {
            case CUSTOM_CONVEX_SHAPE_TYPE:
                break;
            case BOX_SHAPE_PROXYTYPE:
                break;
            case UNIFORM_SCALING_SHAPE_PROXYTYPE:
                break;
            case COMPOUND_SHAPE_PROXYTYPE:
                break;

        }
        GLfloat vVertices[] = {0.0f, 0.5f, 0.0f,
         -0.5f, -0.5f, 0.0f,
         0.5f, -0.5f, 0.0f};
         glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, vVertices);
          glEnableVertexAttribArray(0);
          glDrawArrays(GL_TRIANGLES, 0, 3);
    }
    eglSwapBuffers(display,surface);

//    LOGE("FRAME DRAWN");
}

#undef DEBUG

#endif // _RENDERER

