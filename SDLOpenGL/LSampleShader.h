#pragma once
class LSampleShader : public LShaderProgram
{
public:
	bool loadProgram() override;

	void render() override;
private:
	GLuint gVBO;
	GLuint gIBO;
	GLuint gVAO;
	GLint gVertexPos2DLocation;

};

