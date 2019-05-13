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

    // Create the scene and reset the viewport

	bullet::Scene scene{ btVector3(0, -10, 0) };

	scene.reset_viewport(window);

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
					scene.reset_viewport(window);
                    break;
                }
            }
        }

        // Perform the simulation

		scene.update(1.f / 60.f);

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
