// This file handles all world simulation
#ifndef _ENGINE
#define _ENGINE

#include <btBulletDynamicsCommon.h>

#include <android/sensor.h>
#include <vector>

#ifdef DEBUG
#define LOGI(...) ((void)__android_log_print(ANDROID_LOG_INFO, "native-activity", __VA_ARGS__))
#define LOGW(...) ((void)__android_log_print(ANDROID_LOG_WARN, "native-activity", __VA_ARGS__))
#define LOGE(...) ((void)__android_log_print(ANDROID_LOG_ERROR, "nEngine", __VA_ARGS__))
#else
#define LOGI(...)
#define LOGW(...)
#define LOGE(...)
#endif

struct Engine
{
    // Bullet physics stuff
    btBroadphaseInterface* broadphase;
    btDefaultCollisionConfiguration* collisionConfiguration;
    btCollisionDispatcher* dispatcher;
    btSequentialImpulseConstraintSolver* solver;
    btDiscreteDynamicsWorld* dynamicsWorld;

    std::vector<btRigidBody> objects;
    void init();
    void update(float timeDelta);
    void terminate();
};

/**
 * Initializes the bullet discrete dynamics world
 */
void Engine::init()
{
    broadphase = new btDbvtBroadphase();
    collisionConfiguration = new btDefaultCollisionConfiguration();
    dispatcher = new btCollisionDispatcher(collisionConfiguration);
    solver = new btSequentialImpulseConstraintSolver;
    btDiscreteDynamicsWorld* dynamicsWorld = new btDiscreteDynamicsWorld(dispatcher,broadphase,solver,collisionConfiguration);
    dynamicsWorld->setGravity(btVector3(0,-10,0));// TODO: change this?
    LOGE("Engine init finished");
}

/**
 * Simulates the world for timeDelta seconds
 */
void Engine::update(float timeDelta)
{
    dynamicsWorld->stepSimulation(timeDelta, 10);
}

/**
 * Delete all of the dynamic-memory bullet things
 */
void Engine::terminate()
{
    delete dynamicsWorld;
    delete solver;
    delete dispatcher;
    delete collisionConfiguration;
    delete broadphase;
}

#endif
