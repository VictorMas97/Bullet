
// Autor: Víctor

#pragma once

#include <btBulletDynamicsCommon.h>
#include <memory>
#include <Model_Obj.hpp>

namespace bullet
{

	class GameObject
	{

		std::shared_ptr < btRigidBody> body;

		std::shared_ptr < btCollisionShape > shape;

		btDefaultMotionState state;

	public:
			   
		std::shared_ptr < glt::Model > mesh;

		GameObject(btDiscreteDynamicsWorld & world, std::shared_ptr< btCollisionShape > given_shape, const btVector3 & initial_position, 
																	 float bounce, float mass = 0.f, const std::string & obj_file_path = "");
	};
}