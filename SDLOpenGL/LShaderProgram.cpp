#include "stdafx.h"
#include "LShaderProgram.h"


LShaderProgram::LShaderProgram()
{
	mProgramID = NULL;
}

LShaderProgram::~LShaderProgram()
{
	//Free program if it exists
	freeProgram();
}

void LShaderProgram::freeProgram()
{
	//Delete program
	glDeleteProgram( mProgramID );
}

bool LShaderProgram::bind()
{
	//Use shader
	glUseProgram( mProgramID );

	//Check for error
	GLenum error = glGetError();
	if( error != GL_NO_ERROR )
	{
		SDL_LogError(SDL_LOG_CATEGORY_VIDEO, "Error binding shader! %s\n", gluErrorString( error ) );
		printProgramLog( mProgramID );
		return false;
	}

	return true;
}

void LShaderProgram::unbind()
{
	//Use default program
	glUseProgram( NULL );
}

GLuint LShaderProgram::getProgramID()
{
	return mProgramID;
}

void LShaderProgram::printProgramLog( GLuint program )
{
	//Make sure name is shader
	if( glIsProgram( program ) )
	{
		//Program log length
		int infoLogLength = 0;
		int maxLength = infoLogLength;

		//Get info string length
		glGetProgramiv( program, GL_INFO_LOG_LENGTH, &maxLength );

		//Allocate string
		char* infoLog = new char[ maxLength ];

		//Get info log
		glGetProgramInfoLog( program, maxLength, &infoLogLength, infoLog );
		if( infoLogLength > 0 )
		{
			//Print Log
			SDL_LogError(SDL_LOG_CATEGORY_VIDEO, "%s\n", infoLog );
		}

		//Deallocate string
		delete[] infoLog;
	}
	else
	{
		SDL_LogError(SDL_LOG_CATEGORY_VIDEO, "Name %d is not a program\n", program );
	}
}

void LShaderProgram::printShaderLog( GLuint shader )
{
	//Make sure name is shader
	if( glIsShader( shader ) )
	{
		//Shader log length
		int infoLogLength = 0;
		int maxLength = infoLogLength;

		//Get info string length
		glGetShaderiv( shader, GL_INFO_LOG_LENGTH, &maxLength );

		//Allocate string
		char* infoLog = new char[ maxLength ];

		//Get info log
		glGetShaderInfoLog( shader, maxLength, &infoLogLength, infoLog );
		if( infoLogLength > 0 )
		{
			//Print Log
			SDL_LogError(SDL_LOG_CATEGORY_VIDEO, "%s\n", infoLog );
		}

		//Deallocate string
		delete[] infoLog;
	}
	else
	{
		SDL_LogError(SDL_LOG_CATEGORY_VIDEO, "Name %d is not a shader\n", shader );
	}
}
