#include "Scene.hpp"

namespace bullet
{
	std::shared_ptr< glt::Render_Node > Scene::create_scene(btDiscreteDynamicsWorld & world)
	{
		// Se crean los elementos (nodos) y la escena a la que se añadirán:

		std::shared_ptr< glt::Render_Node > scene(new glt::Render_Node);
		std::shared_ptr< glt::Model       > model(new glt::Model_Obj("../../assets/sphere.obj"));
		std::shared_ptr< glt::Camera      > camera(new glt::Camera(20.f, 1.f, 50.f, 1.f));
		std::shared_ptr< glt::Light       > light(new glt::Light);

		//gameObjects["ball"] = std::make_shared<GameObject>(world, )

		// Se añaden los nodos a la escena:
		
		scene->add("sphere", model);
		scene->add("camera", camera);
		scene->add("light", light);

		//world = new World(btVector3(0, -10, 0));

		return scene;
	}

	void Scene::configure_scene(glt::Render_Node & scene)
	{
		scene["light"]->translate(glt::Vector3(10.f, 10.f, 10.f));
		scene["camera"]->translate(glt::Vector3(0.f, 0.f, 5.f));
	}

	void Scene::reset_viewport(const sf::Window & window, glt::Render_Node & scene)
	{
		GLsizei width = GLsizei(window.getSize().x);
		GLsizei height = GLsizei(window.getSize().y);

		scene.get_active_camera()->set_aspect_ratio(float(width) / height);

		glViewport(0, 0, width, height);
	}
}