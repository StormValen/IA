#include <iostream>
#include <SDL.h>
#include <SDL_image.h>

#include "SDL_SimpleApp.h"
#include "SceneKinematicSeek.h"
#include "SceneKinematicFlee.h"
#include "Scene_Seek.h"
#include "Scene_Flee.h"
#include "Scene_Arrive.h"
#include "Scene_Pursue.h"
#include "Scene_Evade.h"
#include "Scene_Wander.h"
#include "Scene_PathFollowing.h"


using namespace std;

int main(int argc, char ** argv)
{
	bool quit = false;
	SDL_Event event;

	SDL_SimpleApp *app = SDL_SimpleApp::Instance();

	Scene *curr_scene = new SceneKinematicSeek;
	app->setWindowTitle(curr_scene->getTitle());

	while (!quit)
	{
		// run app frame by frame
		event = app->run(curr_scene);

		/* Keyboard events */
		switch (event.type)
		{
		case SDL_KEYDOWN:
			if (event.key.keysym.scancode == SDL_SCANCODE_1)  //SEEK sin cambios en la aceleracion.
			{
				delete(curr_scene);
				curr_scene = new SceneKinematicSeek;
				app->setWindowTitle(curr_scene->getTitle());
			}
			if (event.key.keysym.scancode == SDL_SCANCODE_2) //FLEE sin cambios en la aceleracion.
			{
				delete(curr_scene);
				curr_scene = new SceneKinematicFlee;
				app->setWindowTitle(curr_scene->getTitle());
			}

			if (event.key.keysym.scancode == SDL_SCANCODE_3) //SEEK con cambios en la aceleracion al cambiar de direccion.
			{
				delete(curr_scene);
				curr_scene = new Scene_Seek;
				app->setWindowTitle(curr_scene->getTitle());
			}

			if (event.key.keysym.scancode == SDL_SCANCODE_4) //FLEE con cambios en la aceleracion al cambiar de direccion.
			{
				delete(curr_scene);
				curr_scene = new Scene_Flee;
				app->setWindowTitle(curr_scene->getTitle());
			}

			if (event.key.keysym.scancode == SDL_SCANCODE_5) //ARRIVE 
			{
				delete(curr_scene);
				curr_scene = new Scene_Arrive;
				app->setWindowTitle(curr_scene->getTitle());
			}

			if (event.key.keysym.scancode == SDL_SCANCODE_6) //PURSUE
			{
				delete(curr_scene);
				curr_scene = new Scene_Pursue;
				app->setWindowTitle(curr_scene->getTitle());
			}

			if (event.key.keysym.scancode == SDL_SCANCODE_7) //EVADE
			{
				delete(curr_scene);
				curr_scene = new Scene_Evade;
				app->setWindowTitle(curr_scene->getTitle());
			}

			if (event.key.keysym.scancode == SDL_SCANCODE_8) //WANDER
			{
				delete(curr_scene);
				curr_scene = new Scene_Wander;
				app->setWindowTitle(curr_scene->getTitle());
			}
			if (event.key.keysym.scancode == SDL_SCANCODE_9) //WANDER
			{
				delete(curr_scene);
				curr_scene = new Scene_PathFollowing;
				app->setWindowTitle(curr_scene->getTitle());
			}
		
			//PATH FOLLOWING - or - FLOCKING

			if ((event.key.keysym.scancode == SDL_SCANCODE_Q) || (event.key.keysym.scancode == SDL_SCANCODE_ESCAPE)) //EXIT
			{
				quit = true;
			}
			if (event.key.keysym.scancode == SDL_SCANCODE_F) //cambio del tipo de vista
			{
				app->setFullScreen();
			}
			break;
		case SDL_QUIT:
			quit = true;
			break;
		}

	}

	return 0;
}