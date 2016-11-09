#pragma once
#include "LShaderProgram.h"
class LVertexShader :
	public LShaderProgram
{
public:
	bool loadProgram() override;
	void render() override;
private:
	GLuint gVBO;
	GLuint gIBO;
	GLint gVertexPos2DLocation;

};

