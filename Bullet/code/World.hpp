/**
* @file World.hpp
* @author Victor Mas Toledo
* @date 10/05/2019
* @class World
* @brief Clase que se encarga de montar el mundo de bullet, renderizarlo y actualizarlo
*/

#pragma once

#include <btBulletDynamicsCommon.h>
#include <memory>

namespace bullet
{

	class World
	{

		/**
		* @brief "CollisionConfiguration" por defecto
		*/

		btDefaultCollisionConfiguration collisionConfiguration;

		/**
		* @brief "CollisionDispatcher" por defecto
		*/

		btCollisionDispatcher collisionDispatcher;

		/**
		* @brief "Broadphase" por defecto
		*/

		btDbvtBroadphase overlappingPairCache;

		/**
		* @brief "ConstraintSolver" por defecto
		*/	

		btSequentialImpulseConstraintSolver constraintSolver;

	public:

		/**
		* @brief Puntero inteligente a un "btDiscreteDynamicsWorld"
		*/	

		std::shared_ptr< btDiscreteDynamicsWorld > world;

		/**
		* @brief Crea un mundo 
		* @param gravity -> es la gravedad de dicho mundo
		*/	

		World(btVector3 gravity);

		/**
		* @brief Actualiza el mundo cada frame
		* @param timeStep -> marca cada cuanto tiempo se realiza la actualizacion
		*/	

		void stepSimulation(btScalar timeStep);

		/**
		* @brief Resetea el mundo
		*/	

		void reset();

		/**
		* @brief Checkea las colisiones del mundo
		*/	

		void Chack_collisions();
	};		
}