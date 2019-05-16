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

		//std::shared_ptr< glt::Model       > catapult(new glt::Model);

		//std::shared_ptr< glt::Model       > startFloor(new glt::Model);
		//std::shared_ptr< glt::Model       > middleFloor(new glt::Model);
		//std::shared_ptr< glt::Model       > lastFloor(new glt::Model);

		//std::shared_ptr< glt::Model       > platform(new glt::Model);
		//std::shared_ptr< glt::Model       > door(new glt::Model);
		//std::shared_ptr< glt::Model       > column(new glt::Model);

		std::shared_ptr< glt::Camera      > camera(new glt::Camera(20.f, 1.f, 50.f, 1.f));
		std::shared_ptr< glt::Light       > light(new glt::Light);

		// Es necesario añadir las mallas a los modelos antes de añadir los modelos a la escena:

		//catapult->add(std::shared_ptr< glt::Drawable >(new glt::Cube), glt::Material::default_material());

		//startFloor->add(std::shared_ptr< glt::Drawable >(new glt::Cube), glt::Material::default_material());
		//middleFloor->add(std::shared_ptr< glt::Drawable >(new glt::Cube), glt::Material::default_material());
		//lastFloor->add(std::shared_ptr< glt::Drawable >(new glt::Cube), glt::Material::default_material());		

		//platform->add(std::shared_ptr< glt::Drawable >(new glt::Cube), glt::Material::default_material());
		//door->add(std::shared_ptr< glt::Drawable >(new glt::Cube), glt::Material::default_material());
		//column->add(std::shared_ptr< glt::Drawable >(new glt::Cube), glt::Material::default_material());
		
		// Se añaden los nodos a la escena:

		renderNode->add("light", light);

		renderNode->add("camera", camera);
		renderNode->get("camera")->rotate_around_x(-0.7f);
		renderNode->get("camera")->translate(glt::Vector3(0.f, 0.f, 5.f));	

		//renderNode->add("catapult", catapult);
		//renderNode->get("catapult")->scale(0.1f, 0.2f, 0.1f);
		//renderNode->get("catapult")->translate(glt::Vector3(20.f, 10.f, 0.f));

		//renderNode->add("startFloor", startFloor);
		//renderNode->get("startFloor")->scale(0.5f, 1.5f, 1.5f);
		//renderNode->get("startFloor")->translate(glt::Vector3(5.f, 0.f, 0.f));

		//renderNode->add("middleFloor", middleFloor);
		//renderNode->get("middleFloor")->scale(0.5f, 1.5f, 1.5f);
		//renderNode->get("middleFloor")->translate(glt::Vector3(0.f, 0.f, 0.f));

		//renderNode->add("lastFloor", lastFloor);
		//renderNode->get("lastFloor")->scale(0.5f, 1.5f, 1.5f);
		//renderNode->get("lastFloor")->translate(glt::Vector3(-5.f, 0.f, 0.f));

		//renderNode->add("platform", platform);
		//renderNode->get("platform")->scale(0.3f, 0.1f, 0.5f);
		//renderNode->get("platform")->translate(glt::Vector3(5.7f, 14.f, 0.f));

		//renderNode->add("door", door);
		//renderNode->get("door")->scale(0.1f, 0.3f, 1.5f);
		//renderNode->get("door")->translate(glt::Vector3(0.f, 6.f, 0.f));

		//renderNode->add("column", column);
		//renderNode->get("column")->scale(0.1f, 0.3f, 0.5f);
		//renderNode->get("column")->translate(glt::Vector3(-25.f, 6.f, 0.f));

		renderNode->get("light")->translate(glt::Vector3(10.f, 10.f, 10.f));
		
		gameObjects["catapult"] = std::make_shared<GameObject>(*dynamicWorld->world, std::make_shared<btBoxShape>(btVector3(0.1f, 0.2f, 0.1f)), btVector3(2.8f, 1.7f, 0.f), glt::Vector3(0.1f, 0.2f, 0.1f), 1.f);

		gameObjects["startFloor"] = std::make_shared<GameObject>(*dynamicWorld->world, std::make_shared<btBoxShape>(btVector3(0.5f, 1.5f, 1.5f)), btVector3(2.5f, 0.f, 0.f));
		gameObjects["key"] = std::make_shared<GameObject>(*dynamicWorld->world, std::make_shared<btBoxShape>(btVector3(0.1f, 0.1f, 0.1f)), btVector3(0.3f, 1.6f, 1.3f), glt::Vector3(0.1f, 0.1f, 0.1f), 1.f);
		gameObjects["platform"] = std::make_shared<GameObject>(*dynamicWorld->world, std::make_shared<btBoxShape>(btVector3(0.3f, 0.1f, 0.5f)), btVector3(1.7f, 1.4f, 0.f), glt::Vector3(0.3f, 0.1f, 0.5f));

		gameObjects["doorFloor"] = std::make_shared<GameObject>(*dynamicWorld->world, std::make_shared<btBoxShape>(btVector3(0.5f, 1.5f, 1.5f)), btVector3(0.f, 0.f, 0.f));
		gameObjects["door"] = std::make_shared<GameObject>(*dynamicWorld->world, std::make_shared<btBoxShape>(btVector3(0.1f, 0.3f, 1.5f)), btVector3(-0.3f, 1.8f, 0.f), glt::Vector3(0.1f, 0.3f, 1.5f));

		gameObjects["columnFloor"] = std::make_shared<GameObject>(*dynamicWorld->world, std::make_shared<btBoxShape>(btVector3(0.5f, 1.5f, 1.5f)), btVector3(-2.5f, 0.f, 0.f));
		gameObjects["column"] = std::make_shared<GameObject>(*dynamicWorld->world, std::make_shared<btBoxShape>(btVector3(0.2f, 0.3f, 0.2f)), btVector3(-2.5f, 1.8f, 0.f), glt::Vector3(0.2f, 0.3f, 0.2f), 1.f);
		//gameObjects["ground"] = std::make_shared<GameObject>(*dynamicWorld->world, std::make_shared<btBoxShape>(btVector3(50.f, 1.f, 50.f)), btVector3(0.f , -4.f, 0.f), 0.7f);
		//gameObjects["ball"] = std::make_shared<GameObject>(*dynamicWorld->world, std::make_shared<btSphereShape>(0.3f), btVector3(0.f, 10.f, 0.f), 1.f, 1.f, "../../assets/sphere.obj");
		//gameObjects["ball2"] = std::make_shared<GameObject>(*dynamicWorld->world, std::make_shared<btSphereShape>(1.f), btVector3(0.f, 10.f, 0.f), 1.f, 1.f, "../../assets/sphere.obj");		

		for (it = gameObjects.begin(); it != gameObjects.end(); ++it)
		{			
			renderNode->add(it->first, it->second->model);
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