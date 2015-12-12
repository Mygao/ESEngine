#include "physics_engine.h"

PhysicsEngine::PhysicsEngine()
	: collision_conf_(nullptr),
	  collision_dispatcher_(nullptr),
	  broadphase_(nullptr),
	  solver_(nullptr),
	  dynamics_world_(nullptr)

{

}

PhysicsEngine::~PhysicsEngine()
{

}

void PhysicsEngine::CreateWorld()
{
	collision_conf_ = new btDefaultCollisionConfiguration();

	collision_dispatcher_ = new btCollisionDispatcher(collision_conf_);

	broadphase_ = new btDbvtBroadphase();

	solver_ = new btSequentialImpulseConstraintSolver();

	dynamics_world_ = 
		new btDiscreteDynamicsWorld(collision_dispatcher_, broadphase_,
									solver_, collision_conf_);

	dynamics_world_->setGravity(btVector3(0, -9.8, 0));
}

void PhysicsEngine::DestroyWorld()
{
	if (dynamics_world_)
	{
		for (int i = dynamics_world_->getNumConstraints() - 1;
			 i >= 0; i--)
		{
			dynamics_world_
				->removeConstraint(dynamics_world_->getConstraint(i));
		}

		for (int i = dynamics_world_->getNumCollisionObjects() - 1;
		     i >= 0; i--)
		{
			btCollisionObject* obj =
				dynamics_world_->getCollisionObjectArray()[i];
			btRigidBody* body = btRigidBody::upcast(obj);
			
			if (body && body->getMotionState())
			{
				delete body->getMotionState();
			}

			dynamics_world_->removeCollisionObject(obj);
			delete obj;
		 }

		 for (int i = 0; i < collision_shapes_.size(); i++)
		 {
			 btCollisionShape* shape = collision_shapes_[i];
			 delete shape;
		 }

		 collision_shapes_.clear();

		 delete dynamics_world_;
		 dynamics_world_ = 0;

		 delete solver_;
		 solver_ = 0;

		 delete broadphase_;
		 broadphase_ = 0;

		 delete collision_dispatcher_;
		 collision_dispatcher_ = 0;

		 delete collision_conf_;
		 collision_conf_ = 0;
	}
}