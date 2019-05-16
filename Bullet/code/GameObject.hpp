
// Autor: Víctor

#pragma once

#include <btBulletDynamicsCommon.h>
#include <memory>
#include <Model_Obj.hpp>

namespace bullet
{

	class GameObject
	{
		std::shared_ptr < btCollisionShape > shape;

		btDefaultMotionState state;

		std::shared_ptr < btRigidBody> body;

		btTransform physics_transform;

		glm::mat4 graphics_transform;

		glt::Vector3 objectScale = glt::Vector3(0.f, 0.f, 0.f);

	public:
			   
		std::shared_ptr < glt::Model > model;

		GameObject(btDiscreteDynamicsWorld & world, std::shared_ptr< btCollisionShape > given_shape, const btVector3 & initial_position,
				  const glt::Vector3 & object_scale = glt::Vector3(0.5f, 1.5f, 1.5f), float mass = 0.f, float bounce = 0.f, const std::string & obj_file_path = "");

		void Set_physic_transform();
	};
}