#include "World.hpp"

namespace bullet
{
	World::World(btVector3 gravity)
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
	}

	std::shared_ptr<btDiscreteDynamicsWorld> World::create_world()
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

		std::shared_ptr< btDiscreteDynamicsWorld > dynamicsWorld = std::make_shared<btDiscreteDynamicsWorld>(&collisionDispatcher, &overlappingPairCache,
																							 &constraintSolver, &collisionConfiguration);

		//dynamicsWorld{ new btDiscreteDynamicsWorld(&collisionDispatcher, &overlappingPairCache, &constraintSolver, &collisionConfiguration) };

		//dynamicsWorld->setGravity(gravity);

		dynamicsWorld->setGravity(btVector3(0, -10, 0));

		//dynamicsWorld->stepSimulation(1.f / 60.f);
		
		return dynamicsWorld;
	}
}

