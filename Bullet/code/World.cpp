#include "World.hpp"
#include "GameObject.hpp"
#include <iostream>

namespace bullet
{
	World::World(btVector3 gravity) : collisionDispatcher(&collisionConfiguration)
	{
		std::cout << "Dinamyc world" << std::endl;

		// Create and configure the physiscs world:

		world = std::make_shared<btDiscreteDynamicsWorld>(&collisionDispatcher, &overlappingPairCache, &constraintSolver, &collisionConfiguration);

		world->setGravity(gravity);
	}

	void World::stepSimulation(btScalar timeStep)
	{
		world->stepSimulation(timeStep);

		int manifold_count = world->getDispatcher()->getNumManifolds();

		for (int i = 0; i < manifold_count; i++)
		{
			btPersistentManifold * manifold = world->getDispatcher()->getManifoldByIndexInternal(i);

			btCollisionObject * object_a = (btCollisionObject *)(manifold->getBody0());
			btCollisionObject * object_b = (btCollisionObject *)(manifold->getBody1());

			GameObject * game_object_a = (GameObject *)object_a->getUserPointer();
			GameObject * game_object_b = (GameObject *)object_b->getUserPointer();

			int numContacts = manifold->getNumContacts();

			for (int j = 0; j < numContacts; j++)
			{
				btManifoldPoint & point = manifold->getContactPoint(j);

				if (point.getDistance() < 0.f)
				{
					if ((game_object_a->body->getUserIndex() == 4 && game_object_b->body->getUserIndex() == 9) || (game_object_a->body->getUserIndex() == 9 && game_object_b->body->getUserIndex() == 4))
					{
						std::cout << "colision" << std::endl;
						//game_object_b->Set_velocity(btVector3(-0.23f, 0.0f, 0.0f));
					}
				}
			}
		}
	}

	void World::reset()
	{
		world.reset();
	}
}

