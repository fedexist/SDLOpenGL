#include "stdafx.h"
#include "LVertexShader.h"


bool LVertexShader::loadProgram()
{
	//Success flag
	GLint programSuccess = GL_TRUE;

	//Generate program
	mProgramID = glCreateProgram();

	//Create vertex shader
	GLuint vertexShader = glCreateShader( GL_VERTEX_SHADER );

	//Get vertex source
	const std::string vertexShaderSource =
			#include "shaders/sample2.vert"
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
		#include "shaders/sample2.frag"
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

	gVertexPos2DLocation = glGetAttribLocation(mProgramID, "LVertexPos2D");
	if (gVertexPos2DLocation == -1)
	{
		SDL_LogDebug(SDL_LOG_CATEGORY_APPLICATION,"LVertexPos2D is not a valid glsl program variable!\n");
		programSuccess = false;
	}
	else
	{
		//Initialize clear color
		glClearColor(0.f, 0.f, 0.f, 1.f);

		//VBO data
		GLfloat vertexData[] =
		{
			-1.0f, -1.0f,
			0.5f, -0.5f,
			-0.5f,  0.5f
		};

		//IBO data
		GLuint indexData[] = { 0, 1, 2};

		//Create VBO
		glGenBuffers(1, &gVBO);
		glBindBuffer(GL_ARRAY_BUFFER, gVBO);
		glBufferData(GL_ARRAY_BUFFER, 2 * 4 * sizeof(GLfloat), vertexData, GL_STATIC_DRAW);

		//Create IBO
		glGenBuffers(1, &gIBO);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, gIBO);
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, 4 * sizeof(GLuint), indexData, GL_STATIC_DRAW);


		return programSuccess;
	}
	return programSuccess;
}

void LVertexShader::render()
{
	GLfloat timeValue = SDL_GetTicks();
	GLfloat blueValue = sin(timeValue/144) / 2 + 0.5;
	GLint vertexColorLocation = glGetUniformLocation(mProgramID, "LSampleFrag");
	glUniform4f(vertexColorLocation, 0.0f, 0.1f , 0.1f, 1.0f);


	//Enable vertex position
	glEnableVertexAttribArray( gVertexPos2DLocation );

	//Set vertex data
	glBindBuffer( GL_ARRAY_BUFFER, gVBO );
	glVertexAttribPointer( gVertexPos2DLocation, 2, GL_FLOAT, GL_FALSE, 2 * sizeof(GLfloat), nullptr );
	

	//Set index data and render
	glBindBuffer( GL_ELEMENT_ARRAY_BUFFER, gIBO );
	glDrawElements( GL_TRIANGLES, 4, GL_UNSIGNED_INT, nullptr );

	//Disable vertex position
	glDisableVertexAttribArray( gVertexPos2DLocation );
}
