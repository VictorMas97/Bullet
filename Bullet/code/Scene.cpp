#include "Scene.hpp"
#include <iostream>

namespace bullet
{
	Scene::Scene(btVector3 gravity)
	{
		std::cout << "Scene" << std::endl;

		dynamicWorld = std::make_shared<World>(gravity);

		// Se crean los elementos (nodos) y la escena a la que se añadirán:

		renderNode = std::make_shared<glt::Render_Node>();

		std::shared_ptr< glt::Model       > cube(new glt::Model);
		std::shared_ptr< glt::Model       > cube1(new glt::Model);
		std::shared_ptr< glt::Model       > cube2(new glt::Model);
		std::shared_ptr< glt::Model       > platform(new glt::Model);
		std::shared_ptr< glt::Model       > door(new glt::Model);

		std::shared_ptr< glt::Camera      > camera(new glt::Camera(20.f, 1.f, 50.f, 1.f));
		std::shared_ptr< glt::Light       > light(new glt::Light);

		// Es necesario añadir las mallas a los modelos antes de añadir los modelos a la escena:

		cube->add(std::shared_ptr< glt::Drawable >(new glt::Cube), glt::Material::default_material());
		cube1->add(std::shared_ptr< glt::Drawable >(new glt::Cube), glt::Material::default_material());
		cube2->add(std::shared_ptr< glt::Drawable >(new glt::Cube), glt::Material::default_material());

		platform->add(std::shared_ptr< glt::Drawable >(new glt::Cube), glt::Material::default_material());
		door->add(std::shared_ptr< glt::Drawable >(new glt::Cube), glt::Material::default_material());
		
		// Se añaden los nodos a la escena:

		renderNode->add("light", light);

		renderNode->add("camera", camera);
		renderNode->get("camera")->rotate_around_x(-0.7f);
		renderNode->get("camera")->translate(glt::Vector3(0.f, 0.f, 5.f));	

		renderNode->add("cube", cube);
		renderNode->get("cube")->scale(0.5f, 1.5f, 1.5f);
		renderNode->get("cube")->translate(glt::Vector3(0.f, 0.f, 0.f));

		renderNode->add("cube1", cube1);
		renderNode->get("cube1")->scale(0.5f, 1.5f, 1.5f);
		renderNode->get("cube1")->translate(glt::Vector3(5.f, 0.f, 0.f));

		renderNode->add("cube2", cube2);
		renderNode->get("cube2")->scale(0.5f, 1.5f, 1.5f);
		renderNode->get("cube2")->translate(glt::Vector3(-5.f, 0.f, 0.f));

		renderNode->add("platform", platform);
		renderNode->get("platform")->scale(0.3f, 0.1f, 0.5f);
		renderNode->get("platform")->translate(glt::Vector3(5.7f, 14.f, 0.f));

		renderNode->add("door", door);
		renderNode->get("door")->scale(0.1f, 0.3f, 1.5f);
		renderNode->get("door")->translate(glt::Vector3(0.f, 6.f, 0.f));

		renderNode->get("light")->translate(glt::Vector3(10.f, 10.f, 10.f));
		


		//gameObjects["ground"] = std::make_shared<GameObject>(*dynamicWorld->world, std::make_shared<btBoxShape>(btVector3(50.f, 1.f, 50.f)), btVector3(0.f , -4.f, 0.f), 0.7f, 0.f, "../../assets/Lowpoly_tree_sample.obj");
		//gameObjects["ball"] = std::make_shared<GameObject>(*dynamicWorld->world, std::make_shared<btSphereShape>(1.f), btVector3(0.f, 10.f, 0.f), 1.f, 1.f, "../../assets/sphere.obj");
		//gameObjects["ball2"] = std::make_shared<GameObject>(*dynamicWorld->world, std::make_shared<btSphereShape>(1.f), btVector3(0.f, 10.f, 0.f), 1.f, 1.f, "../../assets/sphere.obj");

		for (it = gameObjects.begin(); it != gameObjects.end(); ++it)
		{			
			renderNode->add(it->first, it->second->model);
			it->second->mesh = renderNode->get(it->first);
		}
	}

	void Scene::reset_viewport(const sf::Window & window)
	{
		GLsizei width  = GLsizei(window.getSize().x);
		GLsizei height = GLsizei(window.getSize().y);

		renderNode->get_active_camera()->set_aspect_ratio(float(width) / height);

		glViewport(0, 0, width, height);
	}

	void Scene::update(btScalar timeStep)
	{
		dynamicWorld->stepSimulation(timeStep);

		for (it = gameObjects.begin(); it != gameObjects.end(); ++it)
		{
			it->second->Set_physic_transform();
		}
	}

	void Scene::render()
	{		
		renderNode->render();		
	}

	void Scene::reset()
	{
		dynamicWorld.reset();
	}
}