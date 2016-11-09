#pragma once
#include "LShaderProgram.h"
class LightShader :
	public LShaderProgram
{
public:
	LightShader();
	~LightShader();
	bool loadProgram() override;
	void render() override;

private:
	float radius;
	GLuint resolution;
	glm_vec4 colors;
	GLuint gVBO;
	GLuint gVAO;
};

