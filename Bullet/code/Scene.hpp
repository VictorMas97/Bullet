#pragma once

#include "World.hpp"
#include "GameObject.hpp"
#include <Light.hpp>
#include <Model_Obj.hpp>
#include <Render_Node.hpp>
#include <SFML/Window.hpp>

namespace bullet
{
	class Scene 
	{
	public:

		Scene(btVector3 gravity);

		//std::shared_ptr< glt::Render_Node > create_scene(btDiscreteDynamicsWorld & world);

		//void configure_scene();

		void reset_viewport(const sf::Window & window);

		void update(btScalar timeStep);

		void render();

		void reset();


		std::shared_ptr< World > dynamicWorld;

		std::shared_ptr< glt::Render_Node > renderNode;

		std::map<std::string, std::shared_ptr<GameObject>> gameObjects;
	};
}