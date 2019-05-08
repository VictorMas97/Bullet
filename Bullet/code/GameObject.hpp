
// Autor: Víctor

#pragma once

#include <btBulletDynamicsCommon.h>
#include <memory>

namespace bullet
{

	class GameObject
	{

		std::shared_ptr< btRigidBody > body;

		std::shared_ptr< btCollisionShape > shape;

		btDefaultMotionState state;

	public:

		GameObject(btDiscreteDynamicsWorld & world, std::shared_ptr< btCollisionShape > & given_shape, const btVector3 & initial_position, float bounce,	float mass);
			

		GameObject(btDiscreteDynamicsWorld & world, std::shared_ptr< btCollisionShape > & given_shape, const btVector3 & initial_position, float bounce);
	};
}