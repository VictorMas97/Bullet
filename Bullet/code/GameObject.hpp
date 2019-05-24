/**
* @file GameObject.hpp
* @author Victor Mas Toledo
* @date 10/05/2019
* @class GameObject
* @brief Clase en donde se construye y renderiza el objeto con fisicas de bullet
*/

#pragma once

#include <btBulletDynamicsCommon.h>
#include <memory>
#include <Model_Obj.hpp>

namespace bullet
{
	class GameObject
	{
		/**
		* @brief Puntero inteligente a la forma del objeto
		*/

		std::shared_ptr < btCollisionShape > shape;

		/**
		* @brief "MotionState" por defecto
		*/

		btDefaultMotionState state;

		/**
		* @brief Transform fisico del objeto 
		*/

		btTransform physics_transform;

		/**
		* @brief Transform grafico del objeto 
		*/

		glm::mat4 graphics_transform;

		/**
		* @brief La escala del objeto, por defecto es 0 en los tres ejes
		*/

		glt::Vector3 objectScale = glt::Vector3(0.f, 0.f, 0.f);

		/**
		* @brief Transform del objeto 
		*/

		btTransform transform;

	public:
		
		/**
		* @brief Booleano del objeto para algunas colisiones especificas
		*/

		bool active = false;

		/**
		* @brief Puntero inteligente al rigidbody
		*/

		std::shared_ptr < btRigidBody> body;

		/**
		* @brief Puntero inteligente a al modelo
		*/
			   
		std::shared_ptr < glt::Model > model;		

		/**
		* @brief Contruye un "GameObject"
		* @param world -> referencia al mundo
		* @param given_shape -> puntro inteligente a la forma de la colision
		* @param initial_position -> referencia a la posicion inicial
		* @param index_tag -> numero de objeto
		* @param object_scale -> escala del objeto, por defecto es "(0.5, 1.5, 1.5)" en los respectivos ejes
		* @param mass -> masa, por defecto es 0
		* @param bounce -> rebote, por defecto es 0
		* @param obj_file_path -> referencia a la ruta del modelo, por defecto esta vacia
		*/	

		GameObject(btDiscreteDynamicsWorld & world, std::shared_ptr< btCollisionShape > given_shape, const btVector3 & initial_position, int index_tag,
				   const glt::Vector3 & object_scale = glt::Vector3(0.5f, 1.5f, 1.5f), float mass = 0.f, float bounce = 0.f, const std::string & obj_file_path = "");

		/**
		* @brief Unifica el transform fisico al transform grafico
		*/

		void Set_physic_transform();

		/**
		* @brief Limita la velocidad lineal, velocidad angular y la gravedad
		* @param linearFactor -> limitacion de la velocidad lineal, por defecto es 0 en cada eje
		* @param angularFactor -> limitacion de la velocidad angular, por defecto es 0 en cada eje
		* @param gravityFactor -> limitacion de la gravedad, por defecto es 0 en cada eje
		*/	

		void Clamp(btVector3 & linearFactor = btVector3(0.0f, 0.0f, 0.0f), btVector3 & angularFactor = btVector3(0.0f, 0.0f, 0.0f),
				   btVector3 & gravityFactor = btVector3(0.0f, 0.0f, 0.0f));

		/**
		* @brief Mueve el objeto dinamico
		* @param velocity -> la velocidad con la que se mueve el objeto
		*/	

		void Set_dynamic_velocity(btVector3 & velocity);

		/**
		* @brief Mueve el objeto kinematico
		* @param velocity -> la velocidad con la que se mueve el objeto
		*/	

		void Set_kinematic_velocity(btVector3 & velocity);

		/**
		* @brief Tranforma a un objeto en kinematico
		*/

		void Set_kinematic_object();

		/**
		* @brief Activa el estado del objeto
		*/

		void Activate_state();
	};
}