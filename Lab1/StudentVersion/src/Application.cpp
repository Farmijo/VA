#include "Application.h"
#include "Utils.h"
#include "Mesh.h"

#include <cmath>

//some globals
Mesh* mesh = NULL;

Application* Application::instance = NULL;

Application::Application( SDL_Window* window )
{
	this->window = window;
	instance = this;

	// initialize attributes
	// Warning: DO NOT CREATE STUFF HERE, USE THE INIT 
	// things create here cannot access opengl
	SDL_GetWindowSize( window, &window_width, &window_height );
	std::cout << " * Window size: " << window_width << " x " << window_height << std::endl;

	keystate = NULL;
}

//Here we have already GL working, so we can create meshes and textures
void Application::init( void )
{
	std::cout << " * Path: " << getPath() << std::endl;

	//OpenGL flags
	glEnable( GL_CULL_FACE ); //render both sides of every triangle
	glEnable( GL_DEPTH_TEST ); //check the occlusions using the Z buffer

	//create our camera
	camera = new Camera();
	camera->lookAt( Vector3( 0, 25, 25 ), Vector3( 0, 0, 0 ), Vector3( 0, 1, 0 ) ); //position the camera and point to 0,0,0
	camera->setPerspective( 70, window_width / (float)window_height, 0.1f, 10000 ); //set the projection, we want to be perspective

	//create a plane mesh
	mesh = new Mesh();
	mesh->createPlane( 10 );

	//hide the cursor
	SDL_ShowCursor( true ); //hide or show the mouse
}

//what to do when the image has to be draw
void Application::render( void )
{
	glClearColor( 1.0, 0.0, 0.0, 1.0 );
	glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );

	//set the clear color (the background color)
	glClearColor( 0.0, 0.0, 0.0, 1.0 );

	// Clear the window and the depth buffer
	glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );

	//Put the camera matrices on the stack of OpenGL (only for fixed rendering)
	camera->set();

	//Draw out world
	drawGrid( 500 ); //background grid

	mesh->render( GL_TRIANGLES );

	glDisable( GL_BLEND );

	//swap between front buffer and back buffer
	SDL_GL_SwapWindow( this->window );
}

void Application::update( float seconds_elapsed )
{
	// EXERCISE PRACT 1

	float speed = seconds_elapsed * 100; //the speed is defined by the seconds_elapsed so it goes constant
	
	if( mouse_state & SDL_BUTTON(SDL_BUTTON_LEFT) ) //is left button pressed?
	{
		//camera->rotate(speed * mouse_delta.x * 0.001, Vector3(0, -1, 0)); //Horizontal axis
		camera->rotate(speed * mouse_delta.y * 0.001,(Vector3(-1, 0, 0))); // Vertical axis
	}

	if (mouse_state & SDL_BUTTON(SDL_BUTTON_RIGHT)) //is right button pressed?
	{

		//camera->rotate(speed * mouse_delta.x * 0.001, Vector3(0, -1, 0));
		//camera->rotate(speed * mouse_delta.y * 0.001, camera->getLocalVector(Vector3(-1, 0, 0)));



	}
	
	if( keystate[ SDL_SCANCODE_LSHIFT ] ) speed *= 10; //move faster with left shift
	// to complete for being able to move the camera
}

//Keyboard event handler (sync input)
void Application::onKeyPressed( SDL_KeyboardEvent event )
{
	switch( event.keysym.sym )
	{
		case SDLK_ESCAPE: exit( 0 ); //ESC key, kill the app
	}
}


void Application::onMouseButton( SDL_MouseButtonEvent event )
{

}

void Application::setWindowSize( int width, int height )
{
	std::cout << "window resized: " << width << "," << height << std::endl;

	// EXERCISE PRACT 1	
}

