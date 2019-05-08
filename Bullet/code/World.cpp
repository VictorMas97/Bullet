#include "World.hpp"
#include <iostream>

namespace bullet
{
	/*World::World(btVector3 gravity)
	{
		// Collision configuration contains default setup for memory, collision setup.
		// Advanced users can create their own configuration.

		btDefaultCollisionConfiguration collisionConfiguration;

		// Use the default collision dispatcher. For parallel processing you can use a diffent dispatcher (see Extras/BulletMultiThreaded).

		btCollisionDispatcher collisionDispatcher(&collisionConfiguration);

		// btDbvtBroadphase is a good general purpose broadphase. You can also try out btAxis3Sweep.

		btDbvtBroadphase overlappingPairCache;

		// The default constraint solver. For parallel processing you can use a different solver (see Extras/BulletMultiThreaded).

		btSequentialImpulseConstraintSolver constraintSolver;

		// Create and configure the physiscs world:

		std::shared_ptr< btDiscreteDynamicsWorld > dynamicsWorld( new btDiscreteDynamicsWorld( &collisionDispatcher, &overlappingPairCache, 
																							   &constraintSolver, &collisionConfiguration));

		//dynamicsWorld{ new btDiscreteDynamicsWorld(&collisionDispatcher, &overlappingPairCache, &constraintSolver, &collisionConfiguration) };

		dynamicsWorld->setGravity(gravity);
	}*/

	World::World(btVector3 gravity)
	{

		std::cout << "Dinamyc world" << std::endl;

		// Collision configuration contains default setup for memory, collision setup.
		// Advanced users can create their own configuration.

		btDefaultCollisionConfiguration collisionConfiguration;

		// Use the default collision dispatcher. For parallel processing you can use a diffent dispatcher (see Extras/BulletMultiThreaded).

		btCollisionDispatcher collisionDispatcher(&collisionConfiguration);

		// btDbvtBroadphase is a good general purpose broadphase. You can also try out btAxis3Sweep.

		btDbvtBroadphase overlappingPairCache;

		// The default constraint solver. For parallel processing you can use a different solver (see Extras/BulletMultiThreaded).

		btSequentialImpulseConstraintSolver constraintSolver;

		// Create and configure the physiscs world:

		world = std::make_shared<btDiscreteDynamicsWorld>(&collisionDispatcher, &overlappingPairCache, &constraintSolver, &collisionConfiguration);

		world->setGravity(gravity);
	}
	void World::stepSimulation(btScalar timeStep)
	{
		world->stepSimulation(timeStep);
	}

	void World::reset()
	{
		world.reset();
	}
}

