#include <time.h>

#include <jni.h>
#include <errno.h>

#include <android/sensor.h>
#include <android/log.h>
#include <android_native_app_glue.h>

#include <engine.h>
#include <renderer.h>
#include <memory>

#include <btBulletDynamicsCommon.h>

#define DEBUG

#ifdef DEBUG
#define LOGI(...) ((void)__android_log_print(ANDROID_LOG_INFO, "native-activity", __VA_ARGS__))
#define LOGW(...) ((void)__android_log_print(ANDROID_LOG_WARN, "native-activity", __VA_ARGS__))
#define LOGE(...) ((void)__android_log_print(ANDROID_LOG_ERROR, "nEngine", __VA_ARGS__))
#else
#define LOGI(...)
#define LOGW(...)
#define LOGE(...)
#endif


struct Controller{
    Renderer* renderer;
    Engine* engine;

    bool isRunning;
    bool animate_engine;
    bool animate_renderer;

    // Android hardware stuff
    ASensorManager* sensorManager;
    const ASensor* accelerometerSensor;
    ASensorEventQueue* sensorEventQueue;
};

static int32_t handle_input(struct android_app* app, AInputEvent* event)
{
    LOGE("Handle Input Called");
    switch (AInputEvent_getType(event))
    {
        // Screen touches
        case AINPUT_EVENT_TYPE_MOTION:
        {
            // The number of motion events in the queue?
            size_t pointerCount = AMotionEvent_getPointerCount(event);
            return 1;
        }
        // Key presses
        case AINPUT_EVENT_TYPE_KEY:
        {
            return 1;
        }
    }
    return 1;
}

// Handles activity lifecycle commands
static void handle_cmd(struct android_app* app, int32_t cmd)
{
    Controller* controller = (Controller*)app->userData;// Because app->userData is a void*
    Engine* engine = controller->engine;
    Renderer* renderer = controller->renderer;
    switch (cmd)
    {
        case APP_CMD_START:
            LOGE("START called");
            engine->init();
            controller->isRunning = true;
            break;
        case APP_CMD_RESUME:
            LOGE("RESUME called");
            controller->animate_engine = true;
            break;
        case APP_CMD_INIT_WINDOW:
            // get the window ready for showing
            LOGE("INIT_WINDOW Called");
            if(renderer->init()) LOGE("EGL Display initialized");
            else LOGE("Error initializing EGL Display");
            controller->animate_renderer = true;
            break;
        case APP_CMD_GAINED_FOCUS:
            LOGE("GAINED_FOCUS called");
            // Monitor accelerometer
            if(controller->accelerometerSensor != NULL)
            {
                ASensorEventQueue_enableSensor(controller->sensorEventQueue, controller->accelerometerSensor);
                // Request 60 updates/second
                ASensorEventQueue_setEventRate(controller->sensorEventQueue, controller->accelerometerSensor, (1000L/60)*1000);
            }
            break;
        case APP_CMD_LOST_FOCUS:
            LOGE("LOST_FOCUS called");
            // Stop monitoring accelerometer
            if(controller->accelerometerSensor != NULL)
            {
                ASensorEventQueue_disableSensor(controller->sensorEventQueue, controller->accelerometerSensor);
            }
            // Stop animating?
            break;
        case APP_CMD_SAVE_STATE:
            LOGE("SAVE_STATE called");
            // the OS asked us to save the state of the app TODO: this
            break;
        case APP_CMD_TERM_WINDOW:
            LOGE("TERM_WINDOW called");
            // clean up the window because it is being hidden/closed
            renderer->terminate();
            controller->animate_renderer = false;
            break;
        case APP_CMD_PAUSE:
            LOGE("PAUSE called");
            controller->animate_engine = false;
            break;
        case APP_CMD_STOP:
            LOGE("STOP called");
            engine->terminate();
            controller->isRunning = false;
            break;
        case APP_CMD_DESTROY:
            LOGE("DESTROY called");
            break;
        default:
            LOGE("OTHER_CMD(%d) called", cmd);
            break;
    }
}

/**
 * This is the main entry point of a native application that is using
 * android_native_app_glue.  It runs in its own thread, with its own
 * event loop for receiving input events and doing other things.
 */
void android_main(struct android_app* app) {
    // Make sure glue isn't stripped.
    app_dummy();
    Controller controller;
    controller.animate_engine = false;
    controller.animate_renderer = false;
    Engine engine;
    controller.engine = &engine;
    Renderer renderer;
    controller.renderer = &renderer;
    renderer.link(engine.dynamicsWorld, &(app->window));
    LOGE("Renderer Linked");

    app->userData = &controller;
    app->onAppCmd = &handle_cmd;
    app->onInputEvent = &handle_input;

    controller.sensorManager = ASensorManager_getInstance();
    controller.accelerometerSensor = ASensorManager_getDefaultSensor(controller.sensorManager, ASENSOR_TYPE_ACCELEROMETER);
    controller.sensorEventQueue = ASensorManager_createEventQueue(controller.sensorManager, app->looper, LOOPER_ID_USER, NULL, NULL);
    timespec prevT;
    clock_gettime(CLOCK_MONOTONIC, &prevT);
    //main loop code
    while (1) {
        int ident;
        int fdesc;
        int events;
        android_poll_source* source;
        // Function signature is: int ALooper_pollAll(int timeoutMillis, int* outFd, int* outEvents, void** outData);
        while((ident = ALooper_pollAll(0, &fdesc, &events, (void**)&source)) >= 0)
        {
            // Process event
            if(source) source->process(app, source);
            // If a sensor has data, process it now.
            if (ident == LOOPER_ID_USER)
            {
                if (controller.accelerometerSensor != NULL)
                {
                    ASensorEvent event;
                    ASensorVector worldAccel;
                    while (ASensorEventQueue_getEvents(controller.sensorEventQueue, &event, 1) > 0)
                    {
                       worldAccel = event.acceleration;
                    }
                    engine.update_gravity(worldAccel.x, worldAccel.y, worldAccel.z);
                }
            }
            while(!controller.isRunning){
                // Check if we are exiting.
                if (app->destroyRequested != 0) {
                    engine.terminate();
                    renderer.terminate();
                    return;
                }
            }
        }
        timespec currentT;
        clock_gettime(CLOCK_MONOTONIC, &currentT);
        float timeDelta = currentT.tv_sec-prevT.tv_sec + (float)(currentT.tv_nsec-prevT.tv_nsec)/1e9f;
        #ifdef DEBUG
            if(currentT.tv_sec != prevT.tv_sec){
                LOGE("RUNNING");
            }
        #endif // DEBUG
        prevT = currentT;
        if(controller.animate_engine) engine.simulate(timeDelta);
        if(controller.animate_renderer) renderer.drawFrame();
    }
}

#undef DEBUG
