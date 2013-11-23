#ifndef _GLDATA
#define _GLDATA

#include <btBulletDynamicsCommon.h>
#include <GLES2/gl2.h>

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

class GLData
{
public:
    GLuint indexBufferHandle;
    GLuint vertexBufferHandle;
    GLsizei nVertices;
    GLData(btCollisionShape* collisionShape);
};

GLData::GLData(btCollisionShape* collisionShape)
{
    glGenBuffers(1,&indexBufferHandle);
    glGenBuffers(1,&vertexBufferHandle);
    switch(collisionShape->getShapeType())
    {
        case BOX_SHAPE_PROXYTYPE:
        {
            nVertices = 8;
            btBoxShape* boxShape = static_cast<btBoxShape*>(collisionShape);
            btVector3 halfExtents = boxShape->getHalfExtentsWithoutMargin();
//            LOGE("BoxShape HalfExtents: %f, %f, %f",halfExtents[0],halfExtents[1],halfExtents[2]);
            float vertexBuffer[8*3];
            //create vertex buffer data
            for(int i = 0; i < 8; i++)// Just spatial data, no color or normal data yet
            {
                vertexBuffer[i] = halfExtents.x() * (1-(i&1)) - halfExtents.x() * (i&1);
                vertexBuffer[i+1] = halfExtents.y() * (1-((i&2)>>1)) - halfExtents.y() * ((i&2)>>1);
                vertexBuffer[i+2] = halfExtents.z() * (1-((i&4)>>2)) - halfExtents.z() * ((i&4)>>2);
            }
            glBufferData(GL_ARRAY_BUFFER, 8*3*sizeof(float) , vertexBuffer, GL_STATIC_DRAW);
            //Create index buffer data
            unsigned short indexBuffer[14] = {2,3,1,0,4,3,7,6,4,5,1,6,2,3};
            glBufferData(GL_ELEMENT_ARRAY_BUFFER, 14*sizeof(short), indexBuffer, GL_STATIC_DRAW);
            break;
        }
        case SPHERE_SHAPE_PROXYTYPE:
        {

            break;
        }
        default:
        {
            LOGE("Shape type not supported yet.");
            /**
             * List of a few other shape types:
             * CUSTOM_CONVEX_SHAPE_TYPE
             * UNIFORM_SCALING_SHAPE_PROXYTYPE
             * COMPOUND_SHAPE_PROXYTYPE
             */
            break;
        }
    }
}
#undef NDEBUG
#endif // _GLDATA