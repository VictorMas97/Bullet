#include "World.hpp"
#include <iostream>

namespace bullet
{
	World::World(btVector3 gravity)
	:
		collisionDispatcher(&collisionConfiguration)
	{

		std::cout << "Dinamyc world" << std::endl;

		// Create and configure the physiscs world:

		world = std::make_shared<btDiscreteDynamicsWorld>(&collisionDispatcher, &overlappingPairCache, &constraintSolver, &collisionConfiguration);

		world->setGravity(gravity);
	}

	void World::stepSimulation(btScalar timeStep)
	{
		world->stepSimulation(timeStep);  // No work
	}

	void World::reset()
	{
		world.reset();
	}
}

