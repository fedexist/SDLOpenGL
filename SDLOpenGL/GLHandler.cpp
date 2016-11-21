#include "stdafx.h"
#include "GLHandler.h"
#include "LSampleShader.h"
#include "LVertexShader.h"
#include "LightShader.h"

GLHandler::GLHandler()
{
	gl_renderer_ = GLRenderer();
}

GLHandler::~GLHandler()
{
	SDL_GL_DeleteContext(gl_context_);
	SDL_LogDebug(SDL_LOG_CATEGORY_APPLICATION, "GLHandler destroyed\n");
}

bool GLHandler::initGL(LWindow* window)
{
	gl_renderer_ = GLRenderer(window);

	glClearColor(0.f, 0.f, 0.f, 1.f);
	glShadeModel(GL_SMOOTH);
	glClearDepth(1.0f);									// Depth Buffer Setup
	glEnable(GL_DEPTH_TEST);							// Enables Depth Testing
	glDepthFunc(GL_LEQUAL);								// The Type Of Depth Testing To Do
	glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);
	glViewport(0, 0, window->getWidth() , window->getHeight());

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();

	left = 0.0f;
	right = float(window->getWidth());
	bottom = 0.0f;
	top = float(window->getHeight());

	gluOrtho2D(left, right, bottom,  top);

	glEnable( GL_TEXTURE_2D );
	glEnable( GL_BLEND );
	glBlendFunc( GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA );

	SDL_LogDebug(SDL_LOG_CATEGORY_VIDEO, "OpenGL initialised correctly\n");

	return true;

}

bool GLHandler::testFunction()
{
	SDL_LogDebug(SDL_LOG_CATEGORY_RENDER, "About to add shader to queue\n" );

	LShaderProgram* sampleShader = new LSampleShader();
	//LShaderProgram* sampleShader1 = new LVertexShader();
	//LShaderProgram* lightShader = new LightShader();

	SDL_LogDebug(SDL_LOG_CATEGORY_RENDER, "SampleShader is constructed\n" );
	
	/*if(!gl_renderer_.AddShaderToQueue(sampleShader1))
	{
		SDL_LogDebug(SDL_LOG_CATEGORY_RENDER, "Failed to add shader to queue\n" );
		return false;
	}*/
	
	if(!gl_renderer_.AddShaderToQueue(sampleShader))
	{
		SDL_LogDebug(SDL_LOG_CATEGORY_RENDER, "Failed to add shader to queue\n" );
		return false;
	}

	/*if(!gl_renderer_.AddShaderToQueue(lightShader))
	{
		SDL_LogDebug(SDL_LOG_CATEGORY_RENDER, "Failed to add shader to queue\n" );
		return false;

	}*/
	return true;

}
