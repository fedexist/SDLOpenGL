#include "stdafx.h"
#include "LSampleShader.h"


bool LSampleShader::loadProgram()
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

	//gVertexPos2DLocation = glGetAttribLocation(mProgramID, "SamplePosition");
	/*if (gVertexPos2DLocation == -1)
	{
		SDL_LogDebug(SDL_LOG_CATEGORY_APPLICATION,"SamplePosition is not a valid glsl program variable!\n");
		programSuccess = false;
	}
	else
	{*/
		//Initialize clear color
		glClearColor(0.f, 0.f, 0.f, 1.f);

		//VBO data
		GLfloat vertexData[] =
		{
			-1.0f, 1.0f, 0.0f,
			-1.0f, -1.0f, 0.0f,
			1.0f,  -1.0f, 0.0f,
			1.0f, 1.0f, 0.0f,
			-1.0f, 1.0f, 0.0f,
			1.0f, -1.0f, 0.0f
		};

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

		//IBO data
		//GLuint indexData[] = { 0, 1, 2};

		/*
		//Create VBO
		glGenBuffers(1, &gVBO);
		glBindBuffer(GL_ARRAY_BUFFER, gVBO);
		glBufferData(GL_ARRAY_BUFFER, 2 * 4 * sizeof(GLfloat), vertexData, GL_STATIC_DRAW);

		//Create IBO
		glGenBuffers(1, &gIBO);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, gIBO);
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, 4 * sizeof(GLuint), indexData, GL_STATIC_DRAW);
		



		return true;
	}*/


	return true;

}

void LSampleShader::render() { 	 

	GLfloat timeValue = SDL_GetTicks();
	GLfloat greenValue = 1.0f;//(sin(timeValue/288) / 2) + 0.5;
	GLfloat radius = 0.6;	//*((sin(timeValue / 1000) / 2) + 0.5);
	GLfloat parameters[] = { 1, 0.0, 10, 0.5+0.05*(sin(timeValue / 500) )};
	GLint vertexColorLocation = glGetUniformLocation(mProgramID, "LSampleFrag");
	GLint radiusLocation = glGetUniformLocation(mProgramID, "radius");
	GLint paramLocation = glGetUniformLocation(mProgramID, "parameters");
	glUniform4f(vertexColorLocation, 0.08f, 0.3f, 0.7f, 1.0f);
	glUniform4f(paramLocation, parameters[0], parameters[1], parameters[2],parameters[3]);
	glUniform1f(radiusLocation, radius);

	//Enable vertex position
	//glEnableVertexAttribArray( gVertexPos2DLocation );

	glBindVertexArray(gVAO);
	glDrawArrays(GL_TRIANGLES, 0, 6);
	glBindVertexArray(0);

	/*
	//Set vertex data
	glBindBuffer( GL_ARRAY_BUFFER, gVBO );
	glVertexAttribPointer( gVertexPos2DLocation, 2, GL_FLOAT, GL_FALSE, 2 * sizeof(GLfloat), nullptr );

	//Set index data and render
	glBindBuffer( GL_ELEMENT_ARRAY_BUFFER, gIBO );
	glDrawElements( GL_TRIANGLE_FAN, 4, GL_UNSIGNED_INT, nullptr );
	*/

	//Disable vertex position
	//glDisableVertexAttribArray( gVertexPos2DLocation );

}
