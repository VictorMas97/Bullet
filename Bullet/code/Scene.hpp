/**
* @file Scene.hpp
* @author Victor Mas Toledo
* @date 10/05/2019
* @class Scene
* @brief Clase que se encarga de montar la escena, renderizarla y actualizarla
*/

#pragma once

#include "World.hpp"
#include "GameObject.hpp"
#include <Cube.hpp>
#include <Light.hpp>
#include <Render_Node.hpp>
#include <SFML/Window.hpp>

namespace bullet
{
	class Scene 
	{
		/**
		* @brief Puntero inteligente al mundo dinamico
		*/

		std::shared_ptr< World > dynamicWorld;

		/**
		* @brief Puntero inteligente a un "Render_Node"
		*/

		std::shared_ptr< glt::Render_Node > renderNode;

		/**
		* @brief Mapa que contiene todos los "GameObjects"
		*/

		std::map<std::string, std::shared_ptr<GameObject>> gameObjects;

		/**
		* @brief Puntero inteligente a un "HingeConstraint"
		*/

		std::unique_ptr<btHingeConstraint> constraint;

		/**
		* @brief Puntero inteligente a un "HingeConstraint"
		*/

		std::unique_ptr<btHingeConstraint> constraint2;

		/**
		* @brief Tiempo que trascurre hasta el proximo disparo
		*/

		float time;   

		/**
		* @brief El cooldown del disparo
		*/

		float nextShoot;

	public:

		/**
		* @brief Actualiza la variabla "reset" con la información del parametro
		* @param gravity -> es la gravedad del mando, por defecto es de -10 en el eje Y
		*/	

		Scene(btVector3 gravity = btVector3(0, -10, 0));

		/**
		* @brief Resetea el viewport
		* @param window -> referencia de la ventana en donde esta la escena
		*/	

		void reset_viewport(const sf::Window & window);

		/**
		* @brief Actualiza la escena
		* @param timeStep -> marca cada cuanto tiempo se realiza la actualizacion
		*/	

		void update(btScalar timeStep);


		/**
		* @brief Renderiza la escena
		*/

		void render();


		/**
		* @brief Resetea la escena
		*/

		void reset();
	};
}