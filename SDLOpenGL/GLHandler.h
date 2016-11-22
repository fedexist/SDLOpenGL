#pragma once
#include "stdafx.h"
#include "GLRenderer.h"

class GLHandler
{
	friend class Core;
public:
	GLHandler();
	~GLHandler();
	bool initGL(LWindow*);
	bool testFunction();
private:
	LWindow* window_;
	GLRenderer gl_renderer_;
	SDL_GLContext gl_context_;

	//Orthographic Projection Data
	GLfloat left, right, bottom, top;
	GLdouble cameraVelocityX = 0.0, cameraVelocityY = 0.0, cameraAcceleration = 1.5,/*questi sono test ->*/ cameraMomentumX = 0.0, cameraMomentumY = 0.0, cameraMass = 1.0;
};

