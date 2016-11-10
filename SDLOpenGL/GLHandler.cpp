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

	//Enable texturing
	glEnable( GL_TEXTURE_2D );
	

	//Set blending
	glEnable( GL_BLEND );
	//glDisable( GL_DEPTH_TEST );
	glBlendFunc( GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA );

	SDL_LogDebug(SDL_LOG_CATEGORY_VIDEO, "OpenGL initialised correctly\n");

	return true;

	/*
	//Success flag
	auto success = true;

	//Generate program
	gProgramID = glCreateProgram();

	//Create vertex shader
	GLuint vertexShader = glCreateShader( GL_VERTEX_SHADER );

	//Get vertex source
	const GLchar* vertexShaderSource[] =
	{
		"#version 140\nin vec2 LVertexPos2D; void main() { gl_Position = vec4( LVertexPos2D.x, LVertexPos2D.y, 0, 1 ); }"
	};

	//Set vertex source
	glShaderSource( vertexShader, 1, vertexShaderSource, nullptr );

	//Compile vertex source
	glCompileShader( vertexShader );

	//Check vertex shader for errors
	auto vShaderCompiled = GL_FALSE;
	glGetShaderiv( vertexShader, GL_COMPILE_STATUS, &vShaderCompiled );
	if( vShaderCompiled != GL_TRUE )
	{
		SDL_LogDebug(SDL_LOG_CATEGORY_APPLICATION, "Unable to compile vertex shader %d!\n", vertexShader );
		printShaderLog( vertexShader );
		success = false;
	}
	else
	{
		//Attach vertex shader to program
		glAttachShader(gProgramID, vertexShader);


		//Create fragment shader
		GLuint fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);

		//Get fragment source
		const GLchar* fragmentShaderSource[] =
		{
			"#version 140\nout vec4 LFragment; void main() { LFragment = vec4( 1.0, 1.0, 1.0, 1.0 ); }"
		};

		//Set fragment source
		glShaderSource(fragmentShader, 1, fragmentShaderSource, nullptr);

		//Compile fragment source
		glCompileShader(fragmentShader);

		//Check fragment shader for errors
		GLint fShaderCompiled = GL_FALSE;
		glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &fShaderCompiled);
		if (fShaderCompiled != GL_TRUE)
		{
			SDL_LogDebug(SDL_LOG_CATEGORY_APPLICATION,"Unable to compile fragment shader %d!\n", fragmentShader);
			printShaderLog(fragmentShader);
			success = false;
		}
		else
		{
			//Attach fragment shader to program
			glAttachShader(gProgramID, fragmentShader);


			//Link program
			glLinkProgram(gProgramID);

			//Check for errors
			GLint programSuccess = GL_TRUE;
			glGetProgramiv(gProgramID, GL_LINK_STATUS, &programSuccess);
			if (programSuccess != GL_TRUE)
			{
				SDL_LogDebug(SDL_LOG_CATEGORY_APPLICATION,"Error linking program %d!\n", gProgramID);
				printProgramLog(gProgramID);
				success = false;
			}
			else
			{
				//Get vertex attribute location
				gVertexPos2DLocation = glGetAttribLocation(gProgramID, "LVertexPos2D");
				if (gVertexPos2DLocation == -1)
				{
					SDL_LogDebug(SDL_LOG_CATEGORY_APPLICATION,"LVertexPos2D is not a valid glsl program variable!\n");
					success = false;
				}
				else
				{
					//Initialize clear color
					glClearColor(0.f, 0.f, 0.f, 1.f);

					//VBO data
					GLfloat vertexData[] =
					{
						-0.5f, -0.5f,
						 0.5f, -0.5f,
						 0.5f,  0.5f,
						-0.5f,  0.5f
					};

					//IBO data
					GLuint indexData[] = { 0, 1, 2, 3 };

					//Create VBO
					glGenBuffers(1, &gVBO);
					glBindBuffer(GL_ARRAY_BUFFER, gVBO);
					glBufferData(GL_ARRAY_BUFFER, 2 * 4 * sizeof(GLfloat), vertexData, GL_STATIC_DRAW);

					//Create IBO
					glGenBuffers(1, &gIBO);
					glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, gIBO);
					glBufferData(GL_ELEMENT_ARRAY_BUFFER, 4 * sizeof(GLuint), indexData, GL_STATIC_DRAW);
				}
			}
		}
	}

	return success;*/
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
