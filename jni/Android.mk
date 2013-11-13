# Copyright (C) 2010 The Android Open Source Project
#
# Licensed under the Apache License, Version 2.0 (the "License");
# you may not use this file except in compliance with the License.
# You may obtain a copy of the License at
#
#      http://www.apache.org/licenses/LICENSE-2.0
#
# Unless required by applicable law or agreed to in writing, software
# distributed under the License is distributed on an "AS IS" BASIS,
# WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
# See the License for the specific language governing permissions and
# limitations under the License.
#
LOCAL_PATH := $(call my-dir)

include $(CLEAR_VARS)

LOCAL_MODULE    := nEngine

LOCAL_C_INCLUDES := \
		$(LOCAL_PATH)/Bullet \
		$(LOCAL_PATH)/Bullet/BulletCollision \
		$(LOCAL_PATH)/Bullet/BulletCollision/BroadphaseCollision \
		$(LOCAL_PATH)/Bullet/BulletCollision/NarrowPhaseCollision \
		$(LOCAL_PATH)/Bullet/BulletCollision/CollisionDispatch \
		$(LOCAL_PATH)/Bullet/BulletCollision/CollisionShapes \
		$(LOCAL_PATH)/Bullet/BulletCollision/Gimpact \
		$(LOCAL_PATH)/Bullet/BulletSoftBody \
		$(LOCAL_PATH)/Bullet/BulletDynamics \
		$(LOCAL_PATH)/Bullet/BulletDynamics/Vehicle \
		$(LOCAL_PATH)/Bullet/BulletDynamics/ConstraintSolver \
		$(LOCAL_PATH)/Bullet/BulletDynamics/Dynamics \
		$(LOCAL_PATH)/Bullet/BulletDynamics/Character \
		$(LOCAL_PATH)/Bullet/LinearMath

libLinearMath_la_SOURCES := \
		Bullet/LinearMath/btQuickprof.cpp \
		Bullet/LinearMath/btGeometryUtil.cpp \
		Bullet/LinearMath/btAlignedAllocator.cpp \
		Bullet/LinearMath/btSerializer.cpp \
		Bullet/LinearMath/btConvexHull.cpp \
		Bullet/LinearMath/btConvexHullComputer.cpp \
		Bullet/LinearMath/btHashMap.h \
		Bullet/LinearMath/btConvexHull.h \
		Bullet/LinearMath/btAabbUtil2.h \
		Bullet/LinearMath/btGeometryUtil.h \
		Bullet/LinearMath/btQuadWord.h \
		Bullet/LinearMath/btPoolAllocator.h \
		Bullet/LinearMath/btScalar.h \
		Bullet/LinearMath/btMinMax.h \
		Bullet/LinearMath/btVector3.h \
		Bullet/LinearMath/btList.h \
		Bullet/LinearMath/btStackAlloc.h \
		Bullet/LinearMath/btMatrix3x3.h \
		Bullet/LinearMath/btMotionState.h \
		Bullet/LinearMath/btAlignedAllocator.h \
		Bullet/LinearMath/btQuaternion.h \
		Bullet/LinearMath/btAlignedObjectArray.h \
		Bullet/LinearMath/btQuickprof.h \
		Bullet/LinearMath/btSerializer.h \
		Bullet/LinearMath/btTransformUtil.h \
		Bullet/LinearMath/btTransform.h \
		Bullet/LinearMath/btDefaultMotionState.h \
		Bullet/LinearMath/btIDebugDraw.h \
		Bullet/LinearMath/btRandom.h

libBulletCollision_la_SOURCES := \
		Bullet/BulletCollision/NarrowPhaseCollision/btRaycastCallback.cpp \
		Bullet/BulletCollision/NarrowPhaseCollision/btMinkowskiPenetrationDepthSolver.cpp \
		Bullet/BulletCollision/NarrowPhaseCollision/btSubSimplexConvexCast.cpp \
		Bullet/BulletCollision/NarrowPhaseCollision/btGjkEpaPenetrationDepthSolver.cpp \
		Bullet/BulletCollision/NarrowPhaseCollision/btGjkConvexCast.cpp \
		Bullet/BulletCollision/NarrowPhaseCollision/btPersistentManifold.cpp \
		Bullet/BulletCollision/NarrowPhaseCollision/btConvexCast.cpp \
		Bullet/BulletCollision/NarrowPhaseCollision/btPolyhedralContactClipping.cpp \
		Bullet/BulletCollision/NarrowPhaseCollision/btContinuousConvexCollision.cpp \
		Bullet/BulletCollision/NarrowPhaseCollision/btGjkPairDetector.cpp \
		Bullet/BulletCollision/NarrowPhaseCollision/btGjkEpa2.cpp \
		Bullet/BulletCollision/NarrowPhaseCollision/btVoronoiSimplexSolver.cpp \
		Bullet/BulletCollision/CollisionDispatch/btActivatingCollisionAlgorithm.cpp \
		Bullet/BulletCollision/CollisionDispatch/btCollisionObject.cpp \
		Bullet/BulletCollision/CollisionDispatch/btEmptyCollisionAlgorithm.cpp \
		Bullet/BulletCollision/CollisionDispatch/btGhostObject.cpp \
		Bullet/BulletCollision/CollisionDispatch/btSphereSphereCollisionAlgorithm.cpp \
		Bullet/BulletCollision/CollisionDispatch/btSphereBoxCollisionAlgorithm.cpp \
		Bullet/BulletCollision/CollisionDispatch/btCollisionDispatcher.cpp \
		Bullet/BulletCollision/CollisionDispatch/btDefaultCollisionConfiguration.cpp \
		Bullet/BulletCollision/CollisionDispatch/btSimulationIslandManager.cpp \
		Bullet/BulletCollision/CollisionDispatch/btBoxBoxDetector.cpp \
		Bullet/BulletCollision/CollisionDispatch/btConvexPlaneCollisionAlgorithm.cpp \
		Bullet/BulletCollision/CollisionDispatch/btConvexConcaveCollisionAlgorithm.cpp \
		Bullet/BulletCollision/CollisionDispatch/btBoxBoxCollisionAlgorithm.cpp \
		Bullet/BulletCollision/CollisionDispatch/btBox2dBox2dCollisionAlgorithm.cpp \
		Bullet/BulletCollision/CollisionDispatch/SphereTriangleDetector.cpp \
		Bullet/BulletCollision/CollisionDispatch/btInternalEdgeUtility.cpp \
		Bullet/BulletCollision/CollisionDispatch/btManifoldResult.cpp \
		Bullet/BulletCollision/CollisionDispatch/btCollisionWorld.cpp \
		Bullet/BulletCollision/CollisionDispatch/btSphereTriangleCollisionAlgorithm.cpp \
		Bullet/BulletCollision/CollisionDispatch/btConvexConvexAlgorithm.cpp \
		Bullet/BulletCollision/CollisionDispatch/btConvex2dConvex2dAlgorithm.cpp \
		Bullet/BulletCollision/CollisionDispatch/btUnionFind.cpp \
		Bullet/BulletCollision/CollisionDispatch/btCompoundCollisionAlgorithm.cpp \
		Bullet/BulletCollision/CollisionShapes/btTetrahedronShape.cpp \
		Bullet/BulletCollision/CollisionShapes/btShapeHull.cpp \
		Bullet/BulletCollision/CollisionShapes/btMinkowskiSumShape.cpp \
		Bullet/BulletCollision/CollisionShapes/btCompoundShape.cpp \
		Bullet/BulletCollision/CollisionShapes/btConeShape.cpp \
		Bullet/BulletCollision/CollisionShapes/btConvexPolyhedron.cpp \
		Bullet/BulletCollision/CollisionShapes/btMultiSphereShape.cpp \
		Bullet/BulletCollision/CollisionShapes/btUniformScalingShape.cpp \
		Bullet/BulletCollision/CollisionShapes/btSphereShape.cpp \
		Bullet/BulletCollision/CollisionShapes/btTriangleIndexVertexArray.cpp \
		Bullet/BulletCollision/CollisionShapes/btBvhTriangleMeshShape.cpp \
		Bullet/BulletCollision/CollisionShapes/btTriangleMeshShape.cpp \
		Bullet/BulletCollision/CollisionShapes/btTriangleBuffer.cpp \
		Bullet/BulletCollision/CollisionShapes/btStaticPlaneShape.cpp \
		Bullet/BulletCollision/CollisionShapes/btPolyhedralConvexShape.cpp \
		Bullet/BulletCollision/CollisionShapes/btEmptyShape.cpp \
		Bullet/BulletCollision/CollisionShapes/btCollisionShape.cpp \
		Bullet/BulletCollision/CollisionShapes/btConvexShape.cpp \
		Bullet/BulletCollision/CollisionShapes/btConvex2dShape.cpp \
		Bullet/BulletCollision/CollisionShapes/btConvexInternalShape.cpp \
		Bullet/BulletCollision/CollisionShapes/btConvexHullShape.cpp \
		Bullet/BulletCollision/CollisionShapes/btTriangleCallback.cpp \
		Bullet/BulletCollision/CollisionShapes/btCapsuleShape.cpp \
		Bullet/BulletCollision/CollisionShapes/btConvexTriangleMeshShape.cpp \
		Bullet/BulletCollision/CollisionShapes/btConcaveShape.cpp \
		Bullet/BulletCollision/CollisionShapes/btConvexPointCloudShape.cpp \
		Bullet/BulletCollision/CollisionShapes/btBoxShape.cpp \
		Bullet/BulletCollision/CollisionShapes/btBox2dShape.cpp \
		Bullet/BulletCollision/CollisionShapes/btOptimizedBvh.cpp \
		Bullet/BulletCollision/CollisionShapes/btHeightfieldTerrainShape.cpp \
		Bullet/BulletCollision/CollisionShapes/btMultimaterialTriangleMeshShape.cpp \
		Bullet/BulletCollision/CollisionShapes/btCylinderShape.cpp \
		Bullet/BulletCollision/CollisionShapes/btScaledBvhTriangleMeshShape.cpp \
		Bullet/BulletCollision/CollisionShapes/btStridingMeshInterface.cpp \
		Bullet/BulletCollision/CollisionShapes/btTriangleIndexVertexMaterialArray.cpp \
		Bullet/BulletCollision/CollisionShapes/btTriangleMesh.cpp \
		Bullet/BulletCollision/BroadphaseCollision/btAxisSweep3.cpp \
		Bullet/BulletCollision/BroadphaseCollision/btOverlappingPairCache.cpp \
		Bullet/BulletCollision/BroadphaseCollision/btDbvtBroadphase.cpp \
		Bullet/BulletCollision/BroadphaseCollision/btMultiSapBroadphase.cpp \
		Bullet/BulletCollision/BroadphaseCollision/btDispatcher.cpp \
		Bullet/BulletCollision/BroadphaseCollision/btBroadphaseProxy.cpp \
		Bullet/BulletCollision/BroadphaseCollision/btQuantizedBvh.cpp \
		Bullet/BulletCollision/BroadphaseCollision/btCollisionAlgorithm.cpp \
		Bullet/BulletCollision/BroadphaseCollision/btDbvt.cpp \
		Bullet/BulletCollision/BroadphaseCollision/btSimpleBroadphase.cpp \
		Bullet/BulletCollision/NarrowPhaseCollision/btGjkEpaPenetrationDepthSolver.h \
		Bullet/BulletCollision/NarrowPhaseCollision/btVoronoiSimplexSolver.h \
		Bullet/BulletCollision/NarrowPhaseCollision/btConvexCast.h \
		Bullet/BulletCollision/NarrowPhaseCollision/btGjkEpa2.h \
		Bullet/BulletCollision/NarrowPhaseCollision/btGjkPairDetector.h \
		Bullet/BulletCollision/NarrowPhaseCollision/btMinkowskiPenetrationDepthSolver.h \
		Bullet/BulletCollision/NarrowPhaseCollision/btPointCollector.h \
		Bullet/BulletCollision/NarrowPhaseCollision/btConvexPenetrationDepthSolver.h \
		Bullet/BulletCollision/NarrowPhaseCollision/btSimplexSolverInterface.h \
		Bullet/BulletCollision/NarrowPhaseCollision/btRaycastCallback.h \
		Bullet/BulletCollision/NarrowPhaseCollision/btContinuousConvexCollision.h \
		Bullet/BulletCollision/NarrowPhaseCollision/btSubSimplexConvexCast.h \
		Bullet/BulletCollision/NarrowPhaseCollision/btPersistentManifold.h \
		Bullet/BulletCollision/NarrowPhaseCollision/btGjkConvexCast.h \
		Bullet/BulletCollision/NarrowPhaseCollision/btManifoldPoint.h \
		Bullet/BulletCollision/NarrowPhaseCollision/btDiscreteCollisionDetectorInterface.h \
		Bullet/BulletCollision/CollisionDispatch/btCollisionObject.h \
		Bullet/BulletCollision/CollisionDispatch/btGhostObject.h \
		Bullet/BulletCollision/CollisionDispatch/btSphereTriangleCollisionAlgorithm.h \
		Bullet/BulletCollision/CollisionDispatch/btBoxBoxCollisionAlgorithm.h \
		Bullet/BulletCollision/CollisionDispatch/btBox2dBox2dCollisionAlgorithm.h \
		Bullet/BulletCollision/CollisionDispatch/btConvexPlaneCollisionAlgorithm.h \
		Bullet/BulletCollision/CollisionDispatch/btEmptyCollisionAlgorithm.h \
		Bullet/BulletCollision/CollisionDispatch/btCollisionCreateFunc.h \
		Bullet/BulletCollision/CollisionDispatch/btConvexConvexAlgorithm.h \
		Bullet/BulletCollision/CollisionDispatch/btConvex2dConvex2dAlgorithm.h \
		Bullet/BulletCollision/CollisionDispatch/btBoxBoxDetector.h \
		Bullet/BulletCollision/CollisionDispatch/btCollisionDispatcher.h \
		Bullet/BulletCollision/CollisionDispatch/SphereTriangleDetector.h \
		Bullet/BulletCollision/CollisionDispatch/btConvexConcaveCollisionAlgorithm.h \
		Bullet/BulletCollision/CollisionDispatch/btUnionFind.h \
		Bullet/BulletCollision/CollisionDispatch/btCompoundCollisionAlgorithm.h \
		Bullet/BulletCollision/CollisionDispatch/btSimulationIslandManager.h \
		Bullet/BulletCollision/CollisionDispatch/btDefaultCollisionConfiguration.h \
		Bullet/BulletCollision/CollisionDispatch/btCollisionWorld.h \
		Bullet/BulletCollision/CollisionDispatch/btInternalEdgeUtility.h \
		Bullet/BulletCollision/CollisionDispatch/btManifoldResult.h \
		Bullet/BulletCollision/CollisionDispatch/btSphereSphereCollisionAlgorithm.h \
		Bullet/BulletCollision/CollisionDispatch/btSphereBoxCollisionAlgorithm.h \
		Bullet/BulletCollision/CollisionDispatch/btCollisionConfiguration.h \
		Bullet/BulletCollision/CollisionShapes/btConvexShape.h \
		Bullet/BulletCollision/CollisionShapes/btConvex2dShape.h \
		Bullet/BulletCollision/CollisionShapes/btTriangleCallback.h \
		Bullet/BulletCollision/CollisionShapes/btPolyhedralConvexShape.h \
		Bullet/BulletCollision/CollisionShapes/btMultimaterialTriangleMeshShape.h \
		Bullet/BulletCollision/CollisionShapes/btCompoundShape.h \
		Bullet/BulletCollision/CollisionShapes/btBoxShape.h \
		Bullet/BulletCollision/CollisionShapes/btBox2dShape.h \
		Bullet/BulletCollision/CollisionShapes/btMultiSphereShape.h \
		Bullet/BulletCollision/CollisionShapes/btCollisionMargin.h \
		Bullet/BulletCollision/CollisionShapes/btConcaveShape.h \
		Bullet/BulletCollision/CollisionShapes/btConvexTriangleMeshShape.h \
		Bullet/BulletCollision/CollisionShapes/btEmptyShape.h \
		Bullet/BulletCollision/CollisionShapes/btUniformScalingShape.h \
		Bullet/BulletCollision/CollisionShapes/btScaledBvhTriangleMeshShape.h \
		Bullet/BulletCollision/CollisionShapes/btMaterial.h \
		Bullet/BulletCollision/CollisionShapes/btTriangleIndexVertexArray.h \
		Bullet/BulletCollision/CollisionShapes/btTriangleInfoMap.h \
		Bullet/BulletCollision/CollisionShapes/btSphereShape.h \
		Bullet/BulletCollision/CollisionShapes/btConvexPointCloudShape.h \
		Bullet/BulletCollision/CollisionShapes/btCapsuleShape.h \
		Bullet/BulletCollision/CollisionShapes/btHeightfieldTerrainShape.h \
		Bullet/BulletCollision/CollisionShapes/btCollisionShape.h \
		Bullet/BulletCollision/CollisionShapes/btStaticPlaneShape.h \
		Bullet/BulletCollision/CollisionShapes/btBvhTriangleMeshShape.h \
		Bullet/BulletCollision/CollisionShapes/btTriangleMeshShape.h \
		Bullet/BulletCollision/CollisionShapes/btStridingMeshInterface.h \
		Bullet/BulletCollision/CollisionShapes/btTriangleMesh.h \
		Bullet/BulletCollision/CollisionShapes/btTriangleBuffer.h \
		Bullet/BulletCollision/CollisionShapes/btShapeHull.h \
		Bullet/BulletCollision/CollisionShapes/btMinkowskiSumShape.h \
		Bullet/BulletCollision/CollisionShapes/btOptimizedBvh.h \
		Bullet/BulletCollision/CollisionShapes/btTriangleShape.h \
		Bullet/BulletCollision/CollisionShapes/btTriangleIndexVertexMaterialArray.h \
		Bullet/BulletCollision/CollisionShapes/btCylinderShape.h \
		Bullet/BulletCollision/CollisionShapes/btTetrahedronShape.h \
		Bullet/BulletCollision/CollisionShapes/btConvexInternalShape.h \
		Bullet/BulletCollision/CollisionShapes/btConeShape.h \
		Bullet/BulletCollision/CollisionShapes/btConvexHullShape.h \
		Bullet/BulletCollision/BroadphaseCollision/btAxisSweep3.h \
		Bullet/BulletCollision/BroadphaseCollision/btDbvtBroadphase.h \
		Bullet/BulletCollision/BroadphaseCollision/btSimpleBroadphase.h \
		Bullet/BulletCollision/BroadphaseCollision/btMultiSapBroadphase.h \
		Bullet/BulletCollision/BroadphaseCollision/btDbvt.h \
		Bullet/BulletCollision/BroadphaseCollision/btOverlappingPairCallback.h \
		Bullet/BulletCollision/BroadphaseCollision/btDispatcher.h \
		Bullet/BulletCollision/BroadphaseCollision/btCollisionAlgorithm.h \
		Bullet/BulletCollision/BroadphaseCollision/btBroadphaseProxy.h \
		Bullet/BulletCollision/BroadphaseCollision/btOverlappingPairCache.h \
		Bullet/BulletCollision/BroadphaseCollision/btBroadphaseInterface.h \
		Bullet/BulletCollision/BroadphaseCollision/btQuantizedBvh.h \
		Bullet/BulletCollision/Gimpact/btGImpactBvh.cpp\
		Bullet/BulletCollision/Gimpact/btGImpactQuantizedBvh.cpp\
		Bullet/BulletCollision/Gimpact/btTriangleShapeEx.cpp\
		Bullet/BulletCollision/Gimpact/btGImpactCollisionAlgorithm.cpp\
		Bullet/BulletCollision/Gimpact/btGImpactShape.cpp\
		Bullet/BulletCollision/Gimpact/gim_box_set.cpp\
		Bullet/BulletCollision/Gimpact/gim_contact.cpp\
		Bullet/BulletCollision/Gimpact/gim_memory.cpp\
		Bullet/BulletCollision/Gimpact/gim_tri_collision.cpp

libBulletDynamics_la_SOURCES := \
		Bullet/BulletDynamics/Dynamics/btContinuousDynamicsWorld.cpp \
		Bullet/BulletDynamics/Dynamics/btRigidBody.cpp \
		Bullet/BulletDynamics/Dynamics/btSimpleDynamicsWorld.cpp \
		Bullet/BulletDynamics/Dynamics/Bullet-C-API.cpp \
		Bullet/BulletDynamics/Dynamics/btDiscreteDynamicsWorld.cpp \
		Bullet/BulletDynamics/ConstraintSolver/btGeneric6DofConstraint.cpp \
		Bullet/BulletDynamics/ConstraintSolver/btGeneric6DofSpringConstraint.cpp \
		Bullet/BulletDynamics/ConstraintSolver/btSolve2LinearConstraint.cpp \
		Bullet/BulletDynamics/ConstraintSolver/btPoint2PointConstraint.cpp \
		Bullet/BulletDynamics/ConstraintSolver/btTypedConstraint.cpp \
		Bullet/BulletDynamics/ConstraintSolver/btContactConstraint.cpp \
		Bullet/BulletDynamics/ConstraintSolver/btSliderConstraint.cpp \
		Bullet/BulletDynamics/ConstraintSolver/btConeTwistConstraint.cpp \
		Bullet/BulletDynamics/ConstraintSolver/btHingeConstraint.cpp \
		Bullet/BulletDynamics/ConstraintSolver/btHinge2Constraint.cpp \
		Bullet/BulletDynamics/ConstraintSolver/btUniversalConstraint.cpp \
		Bullet/BulletDynamics/ConstraintSolver/btSequentialImpulseConstraintSolver.cpp \
		Bullet/BulletDynamics/Vehicle/btWheelInfo.cpp \
		Bullet/BulletDynamics/Vehicle/btRaycastVehicle.cpp \
		Bullet/BulletDynamics/Character/btKinematicCharacterController.cpp \
		Bullet/BulletDynamics/Character/btKinematicCharacterController.h \
		Bullet/BulletDynamics/Character/btCharacterControllerInterface.h \
		Bullet/BulletDynamics/Dynamics/btActionInterface.h \
		Bullet/BulletDynamics/Dynamics/btContinuousDynamicsWorld.h \
		Bullet/BulletDynamics/Dynamics/btSimpleDynamicsWorld.h \
		Bullet/BulletDynamics/Dynamics/btRigidBody.h \
		Bullet/BulletDynamics/Dynamics/btDiscreteDynamicsWorld.h \
		Bullet/BulletDynamics/Dynamics/btDynamicsWorld.h \
		Bullet/BulletDynamics/ConstraintSolver/btSolverBody.h \
		Bullet/BulletDynamics/ConstraintSolver/btConstraintSolver.h \
		Bullet/BulletDynamics/ConstraintSolver/btConeTwistConstraint.h \
		Bullet/BulletDynamics/ConstraintSolver/btTypedConstraint.h \
		Bullet/BulletDynamics/ConstraintSolver/btContactSolverInfo.h \
		Bullet/BulletDynamics/ConstraintSolver/btContactConstraint.h \
		Bullet/BulletDynamics/ConstraintSolver/btPoint2PointConstraint.h \
		Bullet/BulletDynamics/ConstraintSolver/btJacobianEntry.h \
		Bullet/BulletDynamics/ConstraintSolver/btSolverConstraint.h \
		Bullet/BulletDynamics/ConstraintSolver/btSequentialImpulseConstraintSolver.h \
		Bullet/BulletDynamics/ConstraintSolver/btGeneric6DofConstraint.h \
		Bullet/BulletDynamics/ConstraintSolver/btGeneric6DofSpringConstraint.h \
		Bullet/BulletDynamics/ConstraintSolver/btSliderConstraint.h \
		Bullet/BulletDynamics/ConstraintSolver/btHingeConstraint.h \
		Bullet/BulletDynamics/ConstraintSolver/btHinge2Constraint.h \
		Bullet/BulletDynamics/ConstraintSolver/btUniversalConstraint.h \
		Bullet/BulletDynamics/ConstraintSolver/btSolve2LinearConstraint.h \
		Bullet/BulletDynamics/Vehicle/btVehicleRaycaster.h \
		Bullet/BulletDynamics/Vehicle/btRaycastVehicle.h \
		Bullet/BulletDynamics/Vehicle/btWheelInfo.h

libBulletSoftBody_la_SOURCES := \
		Bullet/BulletSoftBody/btDefaultSoftBodySolver.cpp \
		Bullet/BulletSoftBody/btSoftBodyRigidBodyCollisionConfiguration.cpp \
		Bullet/BulletSoftBody/btSoftBody.cpp \
		Bullet/BulletSoftBody/btSoftRigidCollisionAlgorithm.cpp \
		Bullet/BulletSoftBody/btSoftBodyConcaveCollisionAlgorithm.cpp \
		Bullet/BulletSoftBody/btSoftRigidDynamicsWorld.cpp \
		Bullet/BulletSoftBody/btSoftBodyHelpers.cpp \
		Bullet/BulletSoftBody/btSoftSoftCollisionAlgorithm.cpp \
		Bullet/BulletSoftBody/btSparseSDF.h \
		Bullet/BulletSoftBody/btSoftRigidCollisionAlgorithm.h \
		Bullet/BulletSoftBody/btSoftBodyRigidBodyCollisionConfiguration.h \
		Bullet/BulletSoftBody/btSoftBody.h \
		Bullet/BulletSoftBody/btSoftSoftCollisionAlgorithm.h \
		Bullet/BulletSoftBody/btSoftBodyInternals.h \
		Bullet/BulletSoftBody/btSoftBodyConcaveCollisionAlgorithm.h \
		Bullet/BulletSoftBody/btSoftRigidDynamicsWorld.h \
		Bullet/BulletSoftBody/btSoftBodyHelpers.h

LOCAL_SRC_FILES := \
		$(libLinearMath_la_SOURCES) \
		$(libBulletCollision_la_SOURCES) \
		$(libBulletDynamics_la_SOURCES) \
		$(libBulletSoftBody_la_SOURCES) \
		activity_main.cpp

LOCAL_LDLIBS    := -llog -landroid -lEGL -lGLESv2 -ldl
LOCAL_STATIC_LIBRARIES := android_native_app_glue

include $(BUILD_SHARED_LIBRARY)

$(call import-module,android/native_app_glue)
