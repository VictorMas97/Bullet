
// Autor:
#include "GameObject.hpp"
#include <Cube.hpp>
#include <iostream>

namespace bullet
{
	GameObject::GameObject(btDiscreteDynamicsWorld & world, std::shared_ptr<btCollisionShape> given_shape, const btVector3 & initial_position, int index_tag,
						                 const glt::Vector3 & object_scale, float mass, float bounce, const std::string & obj_file_path) : shape(given_shape)
	{

		if (obj_file_path == "")
		{
			std::cout << "New game object without path" << std::endl;
			model = std::make_shared<glt::Model>();
			model->add(std::shared_ptr< glt::Drawable >(new glt::Cube), glt::Material::default_material());
		}

		else
		{
			std::cout << "New game object with path" << std::endl;
			model = std::make_shared<glt::Model_Obj>(obj_file_path);
		}

		objectScale = object_scale;

		btTransform transform;
		transform.setIdentity();
		transform.setOrigin(initial_position);

		state.setWorldTransform(transform);

		btVector3 localInertia(0, 0, 0);

		shape->calculateLocalInertia(mass, localInertia);

		btRigidBody::btRigidBodyConstructionInfo info(mass, &state, shape.get(), localInertia);

		body.reset(new btRigidBody(info));

		body->setRestitution(bounce);

		body->setUserIndex(index_tag);

		body->setUserPointer(this);

		std::cout << body->getUserIndex() << std::endl;

		world.addRigidBody(body.get());
	}

	void GameObject::Set_physic_transform()
	{
		body->getMotionState()->getWorldTransform(physics_transform);

		physics_transform.getOpenGLMatrix(glm::value_ptr(graphics_transform));

		model->set_transformation(graphics_transform);

		model->scale(objectScale.x, objectScale.y, objectScale.z);
	}

	void GameObject::Clamp(btVector3 & linearFactor, btVector3 & angularFactor)
	{
		body->setLinearFactor(linearFactor);
		body->setAngularFactor(angularFactor);
	}

	void GameObject::Set_velocity(btVector3 & velocity)
	{
		body->setLinearVelocity(velocity);
		body->applyImpulse(body->getLinearVelocity(), btVector3(0.0f, 0.0f, 0.0f));
	}

	void GameObject::Activate_state()
	{
		body->setActivationState(DISABLE_DEACTIVATION);		
	}
}