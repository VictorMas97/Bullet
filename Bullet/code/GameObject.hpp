
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

		btTransform physics_transform;

		glm::mat4 graphics_transform;

		glt::Vector3 objectScale = glt::Vector3(0.f, 0.f, 0.f);

		btTransform transform;

	public:

		bool active = false;

		std::shared_ptr < btRigidBody> body;
			   
		std::shared_ptr < glt::Model > model;

		GameObject(btDiscreteDynamicsWorld & world, std::shared_ptr< btCollisionShape > given_shape, const btVector3 & initial_position, int index_tag,
				   const glt::Vector3 & object_scale = glt::Vector3(0.5f, 1.5f, 1.5f), float mass = 0.f, float bounce = 0.f, const std::string & obj_file_path = "");

		void Set_physic_transform();

		void Clamp(btVector3 & linearFactor = btVector3(0.0f, 0.0f, 0.0f), btVector3 & angularFactor = btVector3(0.0f, 0.0f, 0.0f),
				   btVector3 & gravityFactor = btVector3(0.0f, 0.0f, 0.0f));

		void Set_dynamic_velocity(btVector3 & velocity);

		void Set_kinematic_velocity(btVector3 & velocity);

		void Set_kinematic_object();

		void Activate_state();
	};
}