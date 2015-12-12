#ifndef PHYSICS_ENGINE_H_
#define PHYSICS_ENGINE_H_

#include "btBulletDynamicsCommon.h"

class PhysicsEngine
{
public:
	PhysicsEngine();
	~PhysicsEngine();

	void CreateWorld();
	void DestroyWorld();

private:

	btDefaultCollisionConfiguration* collision_conf_;
	btAlignedObjectArray<btCollisionShape*> collision_shapes_;
	btCollisionDispatcher* collision_dispatcher_;
	btBroadphaseInterface* broadphase_;
	btConstraintSolver* solver_;
	btDiscreteDynamicsWorld* dynamics_world_;


};

#endif //PHYSICS_ENGINE_H_