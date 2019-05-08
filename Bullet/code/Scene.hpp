#pragma once

#include "World.hpp"
#include <Light.hpp>
#include <Model_Obj.hpp>
#include <Render_Node.hpp>
#include <SFML/Window.hpp>

namespace bullet
{
	class Scene 
	{
	public:

		static std::shared_ptr< glt::Render_Node > create_scene();

		static void configure_scene(glt::Render_Node & scene);

		static void reset_viewport(const sf::Window & window, glt::Render_Node & scene);

		//static World * world;
	};
}