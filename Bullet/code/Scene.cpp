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
		//std::shared_ptr< glt::Model       > model(new glt::Model_Obj("../../assets/sphere.obj"));
		std::shared_ptr< glt::Camera      > camera(new glt::Camera(20.f, 1.f, 50.f, 1.f));
		std::shared_ptr< glt::Light       > light(new glt::Light);

		gameObjects["ground"] = std::make_shared<GameObject>(*dynamicWorld->world, std::make_shared<btBoxShape>(btVector3(50.f, 1.f, 50.f)), btVector3(0.f , -4.f, 0.f), 0.7f);
		gameObjects["ball"] = std::make_shared<GameObject>(*dynamicWorld->world, std::make_shared<btSphereShape>(1.f), btVector3(0.f, 10.f, 0.f), 1.f, 1.f, "../../assets/sphere.obj");
		
		// Se añaden los nodos a la escena:

		renderNode->add("ball", gameObjects["ball"]->mesh);
		renderNode->add("camera", camera);
		renderNode->add("light", light);	

		renderNode->get("light")->translate(glt::Vector3(10.f, 10.f, 10.f));
		renderNode->get("camera")->translate(glt::Vector3(0.f, 0.f, 5.f));	


		gameObjects["ball"]->sphere_model = renderNode->get("ball");
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
		//std::cout << "Update" << std::endl;
		dynamicWorld->stepSimulation(timeStep);
		gameObjects["ball"]->Set_physic_transform();
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