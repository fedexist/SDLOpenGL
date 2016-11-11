#pragma once
#include <vector>
#include "LShaderProgram.h"
#include "GameClass.h"

class GLRenderer
{
	friend class GLHandler;
public:
	GLRenderer();
	GLRenderer(LWindow*);
	~GLRenderer();
	GLvoid Render(GameClass*);
	GLvoid bindShaders();
	GLvoid unbindShaders();
	GLboolean LoadShaders();
	GLboolean UpdateQueue(LShaderProgram*);
	GLboolean AddShaderToQueue(LShaderProgram*);
private:
	LWindow* window_;
	std::vector<LShaderProgram*> ShaderQueue;
};

