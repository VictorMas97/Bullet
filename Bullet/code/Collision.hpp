#pragma once

#include "World.hpp"
#include <btBulletDynamicsCommon.h>
#include <iostream>

namespace bullet
{
	class Collision
	{

	public:

		void Check_collisions(btDiscreteDynamicsWorld world)
		{
			int manifold_count = world.getDispatcher()->getNumManifolds();

			for (int i = 0; i < manifold_count; i++)
			{
				btPersistentManifold * manifold = world.getDispatcher()->getManifoldByIndexInternal(i);

				btCollisionObject * object_a = (btCollisionObject *)(manifold->getBody0());
				btCollisionObject * object_b = (btCollisionObject *)(manifold->getBody1());

				int numContacts = manifold->getNumContacts();

				for (int j = 0; j < numContacts; j++)
				{
					btManifoldPoint & point = manifold->getContactPoint(j);

					if (point.getDistance() < 0.f)
					{
						if((object_a->getIslandTag() == 2 && object_b->getIslandTag() == 5) || (object_a->getIslandTag() == 5 && object_b->getIslandTag() == 2))
						{
							std::cout << "colision" << std::endl;
						}
					}
				}
			}
		}
	};
}