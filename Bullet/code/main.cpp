#include "Scene.hpp"
#include "GameObject.hpp"
#include "World.hpp"
#include <SFML/Window.hpp>
#include <btBulletDynamicsCommon.h>


int main ()
{
	//std::shared_ptr< btDiscreteDynamicsWorld > dynamicsWorld = bullet::World::create_world(btVector3(0, -10, 0));

	/*
	#pragma region PHYSISCS WORLD INITIALIZATION
	//std::shared_ptr< btDiscreteDynamicsWorld > dynamicsWorld;

    // Collision configuration contains default setup for memory, collision setup.
    // Advanced users can create their own configuration.

    btDefaultCollisionConfiguration collisionConfiguration;

    // Use the default collision dispatcher. For parallel processing you can use a diffent dispatcher (see Extras/BulletMultiThreaded).

    btCollisionDispatcher collisionDispatcher(&collisionConfiguration);

    // btDbvtBroadphase is a good general purpose broadphase. You can also try out btAxis3Sweep.

    btDbvtBroadphase overlappingPairCache;

    // The default constraint solver. For parallel processing you can use a different solver (see Extras/BulletMultiThreaded).

    btSequentialImpulseConstraintSolver constraintSolver;

    // Create and configure the physiscs world:

	std::shared_ptr< btDiscreteDynamicsWorld > dynamicsWorld
    (
        new btDiscreteDynamicsWorld
        (
            &collisionDispatcher,
            &overlappingPairCache,
            &constraintSolver,
            &collisionConfiguration
        )
    );

    dynamicsWorld->setGravity (btVector3(0, -10, 0));
	#pragma endregion*/

	/*#pragma region RIGID BODIES SETUP
	
	
    // Keep track of the shapes, states and rigid bodies.
    // Make sure to reuse collision shapes among rigid bodies whenever possible!

	std::vector< std::shared_ptr< btRigidBody          > > rigidBodies;
	std::vector< std::shared_ptr< btDefaultMotionState > > motionStates;
	std::vector< std::shared_ptr< btCollisionShape     > > collisionShapes;
 
    // GROUND
    {
		std::shared_ptr< btCollisionShape > shape(new btBoxShape(btVector3(50, 1, 50)));

        btTransform transform;
        transform.setIdentity ();
        transform.setOrigin (btVector3(0, -4, 0));

        // Using motionstate is optional for static objects.

		std::shared_ptr< btDefaultMotionState >       state(new btDefaultMotionState(transform));
        btRigidBody::btRigidBodyConstructionInfo info (0, state.get (), shape.get ());
		std::shared_ptr< btRigidBody >                body (new btRigidBody(info));

        body->setRestitution (0.7f);

        // Add the body to the dynamics world.

        dynamicsWorld->addRigidBody (body.get ());

        // Save the smart pointers for automatic cleanup.

        rigidBodies    .push_back (body );
        motionStates   .push_back (state);
        collisionShapes.push_back (shape);
    }

    // DYNAMIC OBJECT

	std::shared_ptr< btRigidBody > sphere_body;

    {
		std::shared_ptr< btCollisionShape > shape(new btSphereShape(btScalar(1.)));

        // Create Dynamic Objects.

        btTransform transform;
        transform.setIdentity ();
        transform.setOrigin (btVector3(0, 10, 0));

        btScalar  mass = 1.f;
        btVector3 localInertia(0, 0, 0);

        shape->calculateLocalInertia (mass, localInertia);

        // Using motionstate is recommended, it provides interpolation capabilities, and only synchronizes 'active' objects

		std::shared_ptr< btDefaultMotionState >       state(new btDefaultMotionState(transform));
        btRigidBody::btRigidBodyConstructionInfo info (mass, state.get (), shape.get (), localInertia);
        
        sphere_body.reset (new btRigidBody(info));

        sphere_body->setRestitution (1.0);

        dynamicsWorld->addRigidBody (sphere_body.get ());

        // Save the smart pointers for automatic cleanup.

        rigidBodies    .push_back (sphere_body);
        motionStates   .push_back (state);
        collisionShapes.push_back (shape);
    }

	#pragma endregion*/

	#pragma region SIMULATION

    // Se crea la ventana y el contexto de OpenGL asociado a ella:

    sf::Window window
    (
        sf::VideoMode(1024, 720),
        "Bullet Rigid Bodies",
        sf::Style::Default,
        sf::ContextSettings(24, 0, 0, 3, 2, sf::ContextSettings::Core)      // Se usa OpenGL 3.2 core profile
    );

    // Se determinan las características de OpenGL disponibles en la máquina:

	if (!glt::initialize_opengl_extensions())
	{
		exit (-1);
	}

    // Se activa la sincronización vertical:

    window.setVerticalSyncEnabled (true);

    // Se crea y se configura la escena:

	bullet::Scene scene{ btVector3(0, -10, 0) };

	scene.reset_viewport(window);

	//std::shared_ptr< glt::Render_Node > scene = bullet::Scene::create_scene(*dynamicsWorld);

	//bullet::Scene::configure_scene (*scene);

    //glt::Node * sphere_model = scene->get ("sphere");  // Get the model 3D in the Scene class over the Model class??

    // Se inicializan algunos elementos de OpenGL:

	//bullet::Scene::reset_viewport (window, *scene);

    glClearColor (0.2f, 0.2f, 0.2f, 1.f);

    bool running = true;
    int  frame   = 0;

    do
    {
        // Read the user input:

        sf::Event event;

        while (window.pollEvent (event))
        {
            switch (event.type)
            {
                case sf::Event::Closed:
                {
                    running = false;
                    break;
                }

                case sf::Event::Resized:
                {
					//bullet::Scene::reset_viewport (window, *scene);
					scene.reset_viewport(window);
                    break;
                }
            }
        }

        // Perform the simulation:  // Scene??
		scene.update(1.f / 60.f);
        //dynamicsWorld->stepSimulation (1.f / 60.f);    // Ángel

        // Apply the physics transform to the graphics model:  // Model??

        btTransform physics_transform;

        //sphere_body->getMotionState ()->getWorldTransform (physics_transform);

        glm::mat4 graphics_transform;

        physics_transform.getOpenGLMatrix (glm::value_ptr(graphics_transform));

        //sphere_model->set_transformation (graphics_transform);

        //sphere_model->scale (0.5f);

        // Render the scene:

        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        //sphere_model->rotate_around_y (0.01f);

        scene.render();

        window.display ();
    }
    while (running);

    // Se debe destruir el mundo físico antes de que se destruyan los cuerpos rígidos:

    scene.reset ();

    return EXIT_SUCCESS;
	#pragma endregion
}
