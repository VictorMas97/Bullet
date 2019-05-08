#pragma once

#include <btBulletDynamicsCommon.h>
#include <memory>

namespace bullet
{

	class World
	{

	public:

		//std::shared_ptr< btDiscreteDynamicsWorld > dynamicsWorld;

		World(btVector3 gravity);

		static std::shared_ptr< btDiscreteDynamicsWorld > create_world();

		//static std::shared_ptr< btDiscreteDynamicsWorld > create_world(btVector3 gravity);

	};		
}