#include "Scene.hpp"
#include "GameObject.hpp"
#include "World.hpp"
#include <SFML/Window.hpp>
#include <btBulletDynamicsCommon.h>


int main ()
{
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

	// Create the scene

	/*//std::shared_ptr< glt::Render_Node > scene = bullet::Scene::create_scene(*dynamicsWorld);

	//bullet::Scene::configure_scene (*scene);

    //glt::Node * sphere_model = scene->get ("sphere");  // Get the model 3D in the Scene class over the Model class??

    // Se inicializan algunos elementos de OpenGL:

	//bullet::Scene::reset_viewport (window, *scene);*/

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

        // Perform the simulation

		scene.update(1.f / 60.f);

        // Apply the physics transform to the graphics model

       /* btTransform physics_transform;

        //sphere_body->getMotionState ()->getWorldTransform (physics_transform);

        glm::mat4 graphics_transform;

        physics_transform.getOpenGLMatrix (glm::value_ptr(graphics_transform));

        //sphere_model->set_transformation (graphics_transform);

        //sphere_model->scale (0.5f);*/

        // Render the scene

        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        //sphere_model->rotate_around_y (0.01f);

        scene.render();

        window.display ();
    }
    while (running);

    // Se debe destruir el mundo físico antes de que se destruyan los cuerpos rígidos:

    scene.reset ();

    return EXIT_SUCCESS;
}
