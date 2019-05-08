
// Autor:

#include "GameObject.hpp"

namespace bullet
{
	GameObject::GameObject(btDiscreteDynamicsWorld & world, std::shared_ptr<btCollisionShape>& given_shape, const btVector3 & initial_position, float bounce, float mass)
		                  : shape(given_shape)
	{
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

	GameObject::GameObject(btDiscreteDynamicsWorld & world, std::shared_ptr<btCollisionShape>& given_shape, const btVector3 & initial_position, float bounce)
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
	}
}
