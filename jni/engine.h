// This file handles all world simulation
#ifndef _ENGINE
#define _ENGINE

#include <btBulletDynamicsCommon.h>

#include <android/sensor.h>
#include <vector>

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

struct Engine
{
    // Bullet physics stuff
    btBroadphaseInterface* broadphase;
    btDefaultCollisionConfiguration* collisionConfiguration;
    btCollisionDispatcher* dispatcher;
    btSequentialImpulseConstraintSolver* solver;
    btDiscreteDynamicsWorld* dynamicsWorld;
    std::vector<btRigidBody*> rigidBodies;
    std::vector<btCollisionShape*> collisionShapes;

    void init();
    void simulate(float timeDelta);
    void update_world_accel(float x, float y, float z);
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
    dynamicsWorld = new btDiscreteDynamicsWorld(dispatcher,broadphase,solver,collisionConfiguration);
    dynamicsWorld->setGravity(btVector3(0,-10,0));// TODO: change this?
    LOGE("Engine init finished");

    //Test stuff
    // Add ground
    btCollisionShape* groundShape = new btStaticPlaneShape(btVector3(0,0,0),1);
    btDefaultMotionState* groundMotionState = new btDefaultMotionState(btTransform(btQuaternion(0,0,0,1),btVector3(0,0,0)));
    btRigidBody::btRigidBodyConstructionInfo groundRigidBodyCI(0,groundMotionState,groundShape,btVector3(0,0,0));
    btRigidBody* groundRigidBody = new btRigidBody(groundRigidBodyCI);
    dynamicsWorld->addRigidBody(groundRigidBody);
    rigidBodies.push_back(groundRigidBody);
    collisionShapes.push_back(groundShape);
//    delete groundShape;

    //Add a sphere
    btCollisionShape* sphereShape = new btSphereShape(1);
    btDefaultMotionState* sphereMotionState = new btDefaultMotionState(btTransform(btQuaternion(0,0,0,1),btVector3(0,10,0)));
    btScalar mass = 1;
    btVector3 sphereInertia(0,0,0);
    sphereShape->calculateLocalInertia(mass,sphereInertia);
    btRigidBody::btRigidBodyConstructionInfo sphereRigidBodyCI(mass,sphereMotionState,sphereShape,sphereInertia);
    btRigidBody* sphereRigidBody = new btRigidBody(sphereRigidBodyCI);
    dynamicsWorld->addRigidBody(sphereRigidBody);
    rigidBodies.push_back(sphereRigidBody);
    collisionShapes.push_back(sphereShape);
//    delete sphereShape;

    LOGE("Test init finished");
}

/**
 * Simulates the world for timeDelta seconds
 */
void Engine::simulate(float timeDelta)
{
    LOGE("Simulate Called");
    dynamicsWorld->stepSimulation(timeDelta, 10);
    LOGE("Frame Simulated");
}

void Engine::update_world_accel(float x, float y, float z)
{
    dynamicsWorld->setGravity(btVector3(x,-y,z));
}

/**
 * Delete all of the dynamic-memory bullet things
 */
void Engine::terminate()
{
    for(btRigidBody* rigidBody : rigidBodies)
    {
        dynamicsWorld->removeRigidBody(rigidBody);
        delete rigidBody->getMotionState();
        delete rigidBody;
    }
    for(btCollisionShape* collisionShape : collisionShapes)
    {
        delete collisionShape;
    }
    delete dynamicsWorld;
    delete solver;
    delete dispatcher;
    delete collisionConfiguration;
    delete broadphase;
    LOGE("Engine terminated");
}

#undef DEBUG

#endif
