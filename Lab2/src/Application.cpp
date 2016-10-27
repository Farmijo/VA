#include "Application.h"
#include "Utils.h"
#include "Triangle.h"
#include "Mesh.h"
#include <GL\GL.h>
#include <SDL_opengl.h>
#include <cmath>

//some globals
Mesh* mesh = NULL;
std::vector<std::string> ASES = { "teapot.ASE", "Girl.ASE", "Box2.ASE" };
float sizes[3] = { 0.1 , 10 , 0.1 };
int primitive = GL_TRIANGLES;
int aseModel = 3;
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

	mesh->loadASE(ASES[aseModel%3], sizes[aseModel%3]);
	//mesh->createCube(6);

	
	//render();

	//hide the cursor
	SDL_ShowCursor( true ); //hide or show the mouse
}

//what to do when the image has to be draw
void Application::render( )
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

	mesh->render(primitive);


	glDisable( GL_BLEND );

	//swap between front buffer and back buffer
	SDL_GL_SwapWindow( this->window );
}

void Application::update( float seconds_elapsed )
{
	// EXERCISE PRACT 1	

	float speed = seconds_elapsed * 100; //the speed is defined by the seconds_elapsed so it goes constant
	
	if (keystate[SDL_SCANCODE_LSHIFT]) speed *= 10;

	if( mouse_state & SDL_BUTTON(SDL_BUTTON_LEFT) ) //is left button pressed?
	{
		camera->rotate(speed * mouse_delta.x * 0.01, Vector3(0, 1, 0)); //Horizontal axis
		camera->rotate(speed * mouse_delta.y * 0.01,Vector3(1, 0, 0)); // Vertical axis
	}

	if (mouse_state & SDL_BUTTON(SDL_BUTTON_RIGHT)) //is right button pressed?	
	{

		camera->move(Vector3(1, 0, 0) * mouse_delta.x *0.2);
		camera->move(Vector3(0, 1, 0) * mouse_delta.y * 0.2);
	}	
}

//Keyboard event handler (sync input)
void Application::onKeyPressed(SDL_KeyboardEvent event)
{
	switch (event.keysym.sym)
	{
	case SDLK_ESCAPE: exit(0); //ESC key, kill the app
		break;

	case SDLK_LEFT: {
		camera->move(Vector3(1, 0, 0));
	
	}
					break;

	case SDLK_RIGHT: {
		camera->move(Vector3(-1, 0, 0));
		
	}
					 break;

	case SDLK_UP: {
		camera->move(Vector3(0, -1, 0));
		
	}
				  break;

	case SDLK_DOWN: {
		camera->move(Vector3(0, 1, 0));
		
	}
					break;

	case SDLK_p: {
		primitive = GL_POINTS;
	
		
	}
		break;

	case SDLK_l: {
		primitive = GL_LINES;
	


	}
				 break;


	case SDLK_f: {
		
		primitive = GL_TRIANGLES;


	}
	break;

	case SDLK_PLUS: {

		aseModel++;
		init();
	

	}
				 break;

	case SDLK_MINUS: {
		if (aseModel < 3) {
			aseModel=aseModel + 3;
		}
		aseModel--;
	

		init();


	}
				 break;

	
	}
}


void Application::onMouseWheel(SDL_Event event)
{
	if (event.wheel.y > 0) {
		camera->move(Vector3(0, 0, -1) * 10);
	}
	else {
		camera->move(Vector3(0, 0, 1) * 10);

	}
		
}

void Application::onMouseButton( SDL_MouseButtonEvent event )

{

}

void Application::setWindowSize( int width, int height )
{
	

	std::cout << "window resized: " << width << "," << height << std::endl;

	glViewport(0, 0, width, height);
	
	
	/*const float ratio = (width) / height;
	float xInit = 1;
	float yInit = 1;

	if (ratio > 1) {
	
		xInit *= ratio;
	}
	else {
		
		yInit = xInit / ratio;
	}

	glOrtho(-1 * xInit, xInit, -1 * yInit, yInit, 0.1f, 10000);

	*/
}

