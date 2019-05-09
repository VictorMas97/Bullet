
// Autor:
#include "GameObject.hpp"
#include <iostream>

namespace bullet
{
	GameObject::GameObject(btDiscreteDynamicsWorld & world, std::shared_ptr<btCollisionShape> given_shape, const btVector3 & initial_position, 
		                                                     float bounce, float mass, const std::string & obj_file_path) : shape(given_shape)
	{
		mesh = std::make_shared<glt::Model_Obj>(obj_file_path);

		std::cout << "New game object" << std::endl;

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

		/*//scene->get("sphere");


		// Apply the physics transform to the graphics model:

		//body->getMotionState ()->getWorldTransform (physics_transform);

		//physics_transform.getOpenGLMatrix(glm::value_ptr(graphics_transform));

		//sphere_model->set_transformation (graphics_transform);

		//sphere_model->scale (0.5f);*/
	}

	void GameObject::Add_physic_transform()
	{
		//std::cout << "Update" << std::endl;

		body->getMotionState()->getWorldTransform(physics_transform);

		physics_transform.getOpenGLMatrix(glm::value_ptr(graphics_transform));

		sphere_model->set_transformation(graphics_transform);

		sphere_model->scale(0.5f);
	}

	/*GameObject::GameObject(btDiscreteDynamicsWorld & world, std::shared_ptr<btCollisionShape> given_shape, const btVector3 & initial_position, float bounce)
						  : shape(given_shape)
	{
		// Se establece la posición inicial:

		btTransform transform;
		transform.setIdentity();
		transform.setOrigin(initial_position);

		state.setWorldTransform(transform);

		btRigidBody::btRigidBodyConstructionInfo info(0, &state, shape.get());

		body.reset(new btRigidBody(info));

		body->setRestitution(bounce);

		world.addRigidBody(body.get());
	}*/
}
