#pragma once

#include <btBulletDynamicsCommon.h>
#include <memory>

namespace bullet
{

	class World
	{

	public:

		World(btVector3 gravity);

		void stepSimulation(btScalar timeStep);

		void reset();

		std::shared_ptr< btDiscreteDynamicsWorld > world;
	};		
}