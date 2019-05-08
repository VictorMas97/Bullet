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

		static std::shared_ptr< glt::Render_Node > create_scene(btDiscreteDynamicsWorld & world);

		static void configure_scene(glt::Render_Node & scene);

		static void reset_viewport(const sf::Window & window, glt::Render_Node & scene);

		//static World * world;

		std::map<std::string, std::shared_ptr<GameObject>> gameObjects;
	};
}