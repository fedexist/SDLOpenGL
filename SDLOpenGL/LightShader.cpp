#include "stdafx.h"
#include "LightShader.h"


LightShader::LightShader()
{
}


LightShader::~LightShader()
{
}

bool LightShader::loadProgram()
{
	//Success flag
	GLint programSuccess = GL_TRUE;

	//Generate program
	mProgramID = glCreateProgram();

	//Create vertex shader
	GLuint vertexShader = glCreateShader( GL_VERTEX_SHADER );

	//Get vertex source
	const std::string vertexShaderSource =
			#include "shaders/pointlight.vert"
		;


	const char* src = vertexShaderSource.c_str();

	//Set vertex source
	glShaderSource( vertexShader, 1, &src, nullptr );

	//Compile vertex source
	glCompileShader( vertexShader );

	//Check vertex shader for errors
	GLint vShaderCompiled = GL_FALSE;
	glGetShaderiv( vertexShader, GL_COMPILE_STATUS, &vShaderCompiled );
	if( vShaderCompiled != GL_TRUE )
	{
		SDL_LogError(SDL_LOG_CATEGORY_VIDEO, "Unable to compile vertex shader %d!\n", vertexShader );
		printShaderLog( vertexShader );
		return false;
	}

	//Attach vertex shader to program
	glAttachShader( mProgramID, vertexShader );


	//Create fragment shader
	GLuint fragmentShader = glCreateShader( GL_FRAGMENT_SHADER );

	//Get fragment source
	const std::string fragmentShaderSource =
			#include "shaders/pointlight.frag"
		;

	src = fragmentShaderSource.c_str(); 
	//Set fragment source
	glShaderSource( fragmentShader, 1, &src, nullptr );

	//Compile fragment source
	glCompileShader( fragmentShader );

	//Check fragment shader for errors
	GLint fShaderCompiled = GL_FALSE;
	glGetShaderiv( fragmentShader, GL_COMPILE_STATUS, &fShaderCompiled );
	if( fShaderCompiled != GL_TRUE )
	{
		SDL_LogError(SDL_LOG_CATEGORY_VIDEO, "Unable to compile fragment shader %d!\n", fragmentShader );
		printShaderLog( fragmentShader );
		return false;
	}

	//Attach fragment shader to program
	glAttachShader( mProgramID, fragmentShader );


	//Link program
	glLinkProgram( mProgramID );

	//Check for errors
	glGetProgramiv( mProgramID, GL_LINK_STATUS, &programSuccess );
	if( programSuccess != GL_TRUE )
	{
		SDL_LogError(SDL_LOG_CATEGORY_VIDEO, "Error linking program %d!\n", mProgramID );
		printProgramLog( mProgramID );
		return false;
	}

	//Initialize clear color
	glClearColor(0.f, 0.f, 0.f, 1.f);

	//VBO data
	GLfloat vertexData[] =
	{
		0.5f, -0.5f, 0.0f,
		0.5f, 0.5f, 0.0f,
		-0.5f,  0.5f, 0.0f
	};

	GLint vertexColorLocation = glGetUniformLocation(mProgramID, "LightColor");
	glUniform4f(vertexColorLocation, 1.0f, 1.0f, 1.0f, 1.0f);


	glGenVertexArrays(1, &gVAO);
	glGenBuffers(1, &gVBO);
	// Bind the Vertex Array Object first, then bind and set vertex buffer(s) and attribute pointer(s).
	glBindVertexArray(gVAO);

	glBindBuffer(GL_ARRAY_BUFFER, gVBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertexData), vertexData, GL_STATIC_DRAW);

	// Position attribute
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(GLfloat), nullptr );
	glEnableVertexAttribArray(0);

	glBindVertexArray(0);

	return true;
}

void LightShader::render()
{
	GLint x, y;
	SDL_GetMouseState(&x, &y);

	//Enable vertex position
	//glEnableVertexAttribArray( gVertexPos2DLocation );

	glBindVertexArray(gVAO);
	glDrawArrays(GL_TRIANGLES, 0, 3);
	glBindVertexArray(0);
}
