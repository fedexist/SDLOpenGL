#pragma once
#include <vector>
#include "LShaderProgram.h"

class GLRenderer
{
	friend class GLHandler;
public:
	GLRenderer();
	GLRenderer(LWindow*);
	~GLRenderer();
	GLvoid Render();
	GLvoid bindShaders();
	GLvoid unbindShaders();
	GLboolean LoadShaders();
	GLboolean UpdateQueue(LShaderProgram*);
	GLboolean AddShaderToQueue(LShaderProgram*);
private:
	LWindow* window_;
	std::vector<LShaderProgram*> ShaderQueue;
};

