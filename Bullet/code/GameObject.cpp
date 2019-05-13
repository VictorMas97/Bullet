
// Autor:
#include "GameObject.hpp"
#include <iostream>

namespace bullet
{
	GameObject::GameObject(btDiscreteDynamicsWorld & world, std::shared_ptr<btCollisionShape> given_shape, const btVector3 & initial_position, 
		                                                     float bounce, float mass, const std::string & obj_file_path) : shape(given_shape)
	{
		
		std::cout << "New game object" << std::endl;

		model = std::make_shared<glt::Model_Obj>(obj_file_path);

		//std::dynamic_pointer_cast <glt::Model_Obj> (model)->get_error();
		//std::cout << std::dynamic_pointer_cast <glt::Model_Obj> (model)->get_error() << std::endl;

		// Se establece la posición inicial:

		btTransform transform;
		transform.setIdentity();
		transform.setOrigin(initial_position);

		state.setWorldTransform(transform);

		// Se calcula el "local inertia" en función de la geometría y la masa:

		btVector3 localInertia(0, 0, 0);

		shape->calculateLocalInertia(mass, localInertia);

		btRigidBody::btRigidBodyConstructionInfo info(mass, &state, shape.get(), localInertia);

		body.reset(new btRigidBody(info));

		body->setRestitution(bounce);

		world.addRigidBody(body.get());
	}

	void GameObject::Set_physic_transform()
	{
		body->getMotionState()->getWorldTransform(physics_transform);

		physics_transform.getOpenGLMatrix(glm::value_ptr(graphics_transform));

		mesh->set_transformation(graphics_transform);

		mesh->scale(0.5f);
	}
}
