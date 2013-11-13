// This file handles drawing the world to screen
#ifndef _RENDERER
#define _RENDERER

#include <android/log.h>
#include <EGL/egl.h>
#include <GLES2/gl2.h>
#include <GLES2/gl2ext.h>

#include <btBulletDynamicsCommon.h>

#include <vector>
#include <time.h>

#ifdef DEBUG
#define LOGI(...) ((void)__android_log_print(ANDROID_LOG_INFO, "native-activity", __VA_ARGS__))
#define LOGW(...) ((void)__android_log_print(ANDROID_LOG_WARN, "native-activity", __VA_ARGS__))
#define LOGE(...) ((void)__android_log_print(ANDROID_LOG_ERROR, "nEngine", __VA_ARGS__))
#else
#define LOGI(...)
#define LOGW(...)
#define LOGE(...)
#endif

struct Renderer
{
    ANativeWindow** window;
    EGLDisplay display;
    EGLSurface surface;
    EGLContext context;
    int32_t width;
    int32_t height;
    std::vector<btRigidBody>* objects;
    bool isReady;

    int eglInit();
    void link(std::vector<btRigidBody>* linkedObjects, ANativeWindow** window);
    void drawFrame();
    void terminate();
};

/**
 * Link this instance to an app and an engine
 */
void Renderer::link(std::vector<btRigidBody>* linkedObjects, ANativeWindow** window)
{
    objects = linkedObjects;
    this->window = window;
}

/**
 * Initialize an EGL context for the current display
 */
int Renderer::eglInit()
{
    LOGE("eglInit called");
    const EGLint attribs[] =
    {
            EGL_RENDERABLE_TYPE, EGL_OPENGL_ES2_BIT,
            EGL_BLUE_SIZE, 8,
            EGL_GREEN_SIZE, 8,
            EGL_RED_SIZE, 8,
            EGL_NONE
    };
    EGLint AttribList[] =
    {
        EGL_CONTEXT_CLIENT_VERSION, 2,
        EGL_NONE
    };
    EGLint w, h, dummy, format;
    EGLint numConfigs;
    EGLConfig config;
    EGLSurface surface;
    EGLContext context;
    EGLDisplay display = eglGetDisplay(EGL_DEFAULT_DISPLAY);
    LOGE("FLAG1");
    eglInitialize(display,0,0);
    LOGE("FLAG2");
    /* Here, the application chooses the configuration it desires. In this
     * sample, we have a very simplified selection process, where we pick
     * the first EGLConfig that matches our criteria
     * TODO: find this function's declaration and fix if necessary
     */
    eglChooseConfig(display, attribs, &config, 1, &numConfigs);
    LOGE("FLAG3");
    /* EGL_NATIVE_VISUAL_ID is an attribute of the EGLConfig that is
     * guaranteed to be accepted by ANativeWindow_setBuffersGeometry().
     * As soon as we picked a EGLConfig, we can safely reconfigure the
     * ANativeWindow buffers to match, using EGL_NATIVE_VISUAL_ID. */
    eglGetConfigAttrib(display, config, EGL_NATIVE_VISUAL_ID, &format);
    LOGE("FLAG4");
    ANativeWindow_setBuffersGeometry(*window, 0, 0, format);
    LOGE("FLAG5");

    surface = eglCreateWindowSurface(display, config,  *window, NULL);
    LOGE("FLAG6");
    context = eglCreateContext(display, config, NULL, NULL);
    LOGE("FLAG7");

    if (eglMakeCurrent(display, surface, surface, context) == EGL_FALSE) {
        LOGE("Unable to eglMakeCurrent");
        return 1;
    }

    eglQuerySurface(display, surface, EGL_WIDTH, &w);
    eglQuerySurface(display, surface, EGL_HEIGHT, &h);

    this->display = display;
    this->context = context;
    this->surface = surface;
    width = w;
    height = h;

    // Initialize GL state.
    glEnable(GL_CULL_FACE);
    glEnable(GL_DEPTH_TEST);// Originally glDisable
    isReady = true;
    return 0;
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
    isReady = false;
}

void Renderer::drawFrame()
{
    if(display == NULL || !isReady)
    {
//        LOGE("Display not ready");
        return;
    }

    // Temp test function: just fill the screen with a color
    timespec t;
    clock_gettime(CLOCK_MONOTONIC, &t);
    glClearColor((float)(t.tv_sec%3)/3.0, (float)((t.tv_sec+1)%3)/3.0, (float)((t.tv_sec+2)%3)/3.0, 1);
//    glClearColor(1,0,0,1);

    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    eglSwapBuffers(display,surface);


//    for(btRigidBody o : *objects)
//    {
//        // TODO: draw the object
//    }

//    LOGE("FRAME DRAWN");
}

#endif

