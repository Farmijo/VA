/*  by Javi Agenjo 2013 UPF  javi.agenjo@gmail.com
	This class encapsulates the game, is in charge of creating the game, getting the user input, process the update and render.
*/

#ifndef GAME_H
#define GAME_H

#include "includes.h"
#include "Camera.h"

class Application
{
public:
	static Application* instance;

	//window
	SDL_Window* window;
	int window_width;
	int window_height;

	float time;

	//keyboard state
	const Uint8* keystate;

	//mouse state
	int mouse_state; //tells which buttons are pressed
	Vector2 mouse_position; //last mouse position
	Vector2 mouse_delta; //mouse movement in the last frame

	Camera* camera; //our global camera

	Application( SDL_Window* window );
	void init( void );
	void render( void );
	void update( float dt );

	void onKeyPressed( SDL_KeyboardEvent event );
	void onMouseButton( SDL_MouseButtonEvent event );
	void onResize( SDL_Event e );
	void onMouseWheel(SDL_Event event);

	void setWindowSize( int width, int height );
};


#endif 