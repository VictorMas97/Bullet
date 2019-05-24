#include "World.hpp"
#include "GameObject.hpp"
#include <iostream>

namespace bullet
{
	World::World(btVector3 gravity) : collisionDispatcher(&collisionConfiguration)
	{
		std::cout << "Dinamyc world" << std::endl;

		world = std::make_shared<btDiscreteDynamicsWorld>(&collisionDispatcher, &overlappingPairCache, &constraintSolver, &collisionConfiguration);

		world->setGravity(gravity);
	}

	void World::stepSimulation(btScalar timeStep)
	{
		world->stepSimulation(timeStep);
		Chack_collisions();
	}

	void World::reset()
	{
		world.reset();
	}

	void World::Chack_collisions()
	{
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
					if ((game_object_a->body->getUserIndex() == 4 && game_object_b->body->getUserIndex() == 6 && !game_object_a->active) || (game_object_a->body->getUserIndex() == 6 && game_object_b->body->getUserIndex() == 4 && !game_object_a->active))
					{
						game_object_a->active = true;
						game_object_b->active = true;
						std::cout << "catapult - platformExtra collision" << std::endl;
					}

					else if ((game_object_a->body->getUserIndex() == 2 && game_object_b->body->getUserIndex() == 5 && !game_object_a->active) || (game_object_a->body->getUserIndex() == 5 && game_object_b->body->getUserIndex() == 2 && !game_object_a->active))
					{
						game_object_a->active = true;
						game_object_b->active = true;
						std::cout << "platform - doorFloor collision" << std::endl;
					}

					else if ((game_object_a->body->getUserIndex() == 4 && game_object_b->body->getUserIndex() == 7 && !game_object_b->active) || (game_object_a->body->getUserIndex() == 7 && game_object_b->body->getUserIndex() == 4 && !game_object_b->active))
					{
						game_object_a->active = true;
						game_object_b->active = true;
						std::cout << "catapult - key collision" << std::endl;
					}
				}
			}
		}
	}
}

