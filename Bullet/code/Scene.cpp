#include "Scene.hpp"
#include <iostream>

namespace bullet
{
	Scene::Scene(btVector3 gravity)
	{
		std::cout << "Scene" << std::endl;

		dynamicWorld = std::make_shared<World>(gravity);

		renderNode = std::make_shared<glt::Render_Node>();

		#pragma region SceneObjects

		std::shared_ptr< glt::Camera      > camera(new glt::Camera(20.f, 1.f, 50.f, 1.f));
		std::shared_ptr< glt::Light       > light(new glt::Light);

		renderNode->add("light", light);

		renderNode->add("camera", camera);
		renderNode->get("camera")->rotate_around_x(-0.7f);
		renderNode->get("camera")->translate(glt::Vector3(0.f, 0.f, 5.f));	

		renderNode->get("light")->translate(glt::Vector3(10.f, 10.f, 10.f));

		#pragma endregion

		#pragma region GameObjects

		gameObjects["startFloor"] = std::make_shared<GameObject>(*dynamicWorld->world, std::make_shared<btBoxShape>(btVector3(0.5f, 1.5f, 1.5f)), btVector3(2.5f, 0.f, 0.f), 1);
		gameObjects["doorFloor"] = std::make_shared<GameObject>(*dynamicWorld->world, std::make_shared<btBoxShape>(btVector3(0.5f, 1.5f, 1.5f)), btVector3(0.f, 0.f, 0.f), 2, glt::Vector3(0.5f, 1.5f, 1.5f), 1.f);
		//gameObjects["doorFloor"]->body->setCollisionFlags(gameObjects["doorFloor"]->body->getCollisionFlags() | btCollisionObject::CF_KINEMATIC_OBJECT);
		//gameObjects["doorFloor"]->Activate_state();
		gameObjects["doorFloor"]->Clamp(btVector3(0.0f, 0.0f, 0.0f), btVector3(0.0f, 0.0f, 0.0f));
		gameObjects["doorFloor"]->body->setGravity(btVector3(0.0f, 0.0f, 0.0f));

		gameObjects["columnFloor"] = std::make_shared<GameObject>(*dynamicWorld->world, std::make_shared<btBoxShape>(btVector3(0.5f, 1.5f, 1.5f)), btVector3(-2.5f, 0.f, 0.f), 3);

		gameObjects["catapult"] = std::make_shared<GameObject>(*dynamicWorld->world, std::make_shared<btBoxShape>(btVector3(0.1f, 0.2f, 0.1f)), btVector3(2.8f, 1.7f, 0.f), 4, glt::Vector3(0.1f, 0.2f, 0.1f), 1.f);
		//gameObjects["catapult"]->Clamp(btVector3(0.1f, 0.0f, 0.0f), btVector3(0.0f, 0.0f, 0.0f));
		gameObjects["catapult"]->Activate_state();

		gameObjects["platform"] = std::make_shared<GameObject>(*dynamicWorld->world, std::make_shared<btBoxShape>(btVector3(0.3f, 0.1f, 0.5f)), btVector3(1.7f, 1.4f, 0.f), 5, glt::Vector3(0.3f, 0.1f, 0.5f));
		//gameObjects["platform"]->Clamp(btVector3(0.1f, 0.0f, 0.0f), btVector3(0.0f, 0.0f, 0.0f));
		gameObjects["platform"]->body->setCollisionFlags(gameObjects["platform"]->body->getCollisionFlags() | btCollisionObject::CF_KINEMATIC_OBJECT);
		gameObjects["platform"]->Activate_state();

		gameObjects["platformExtra"] = std::make_shared<GameObject>(*dynamicWorld->world, std::make_shared<btBoxShape>(btVector3(0.1f, 0.1f, 0.1f)), btVector3(1.5f, 1.6f, -0.2f), 6, glt::Vector3(0.1f, 0.1f, 0.1f));
		gameObjects["platformExtra"]->body->setCollisionFlags(gameObjects["platformExtra"]->body->getCollisionFlags() | btCollisionObject::CF_KINEMATIC_OBJECT);
		gameObjects["platformExtra"]->Activate_state();
		//gameObjects["platformExtra"]->model->set_parent(gameObjects["platform"]->model.get());
		gameObjects["key"] = std::make_shared<GameObject>(*dynamicWorld->world, std::make_shared<btBoxShape>(btVector3(0.1f, 0.1f, 0.1f)), btVector3(0.3f, 1.6f, -0.1f), 7, glt::Vector3(0.1f, 0.1f, 0.1f));
		
		gameObjects["door"] = std::make_shared<GameObject>(*dynamicWorld->world, std::make_shared<btBoxShape>(btVector3(0.1f, 0.3f, 1.5f)), btVector3(-0.3f, 1.8f, 0.f), 8, glt::Vector3(0.1f, 0.3f, 1.5f));
		gameObjects["door"]->body->setCollisionFlags(gameObjects["door"]->body->getCollisionFlags() | btCollisionObject::CF_KINEMATIC_OBJECT); 
		gameObjects["door"]->Activate_state();
		//gameObjects["door"]->Set_velocity(btVector3(0.0f, 1.0f, 0.0f));

		gameObjects["column"] = std::make_shared<GameObject>(*dynamicWorld->world, std::make_shared<btBoxShape>(btVector3(0.2f, 0.3f, 0.2f)), btVector3(-2.5f, 1.8f, 0.f), 9, glt::Vector3(0.2f, 0.3f, 0.2f), 1.f);
	
		//gameObjects["ground"] = std::make_shared<GameObject>(*dynamicWorld->world, std::make_shared<btBoxShape>(btVector3(50.f, 1.f, 50.f)), btVector3(0.f , -4.f, 0.f), 0.7f);
		//gameObjects["ball"] = std::make_shared<GameObject>(*dynamicWorld->world, std::make_shared<btSphereShape>(0.3f), btVector3(0.f, 10.f, 0.f), 1.f, 1.f, "../../assets/sphere.obj");
		//gameObjects["ball2"] = std::make_shared<GameObject>(*dynamicWorld->world, std::make_shared<btSphereShape>(1.f), btVector3(0.f, 10.f, 0.f), 1.f, 1.f, "../../assets/sphere.obj");		

		#pragma endregion

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

		if (gameObjects["catapult"]->active && gameObjects["platformExtra"]->active  && !gameObjects["platform"]->active && !gameObjects["doorFloor"]->active)
		{
			gameObjects["platform"]->Set_kinematic_velocity(btVector3(-0.01f, 0.0f, 0.0f));
			gameObjects["platformExtra"]->Set_kinematic_velocity(btVector3(-0.01f, 0.0f, 0.0f));
		}

		if (gameObjects["catapult"]->active && gameObjects["key"]->active)
		{
			std::cout << "hhh" << std::endl;
			gameObjects["door"]->Set_kinematic_velocity(btVector3(0.0f, 0.1f, 0.0f));
		}

		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
		{
			gameObjects["catapult"]->Set_velocity(btVector3(-0.2f, 0.0f, 0.0f));
		}

		else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
		{
			gameObjects["catapult"]->Set_velocity(btVector3(0.2f, 0.0f, 0.0f));
		}

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