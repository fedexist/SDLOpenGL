#include "stdafx.h"
#include "GLRenderer.h"


GLRenderer::GLRenderer()
{
}

GLRenderer::GLRenderer(LWindow* window)
{
	SDL_LogDebug(SDL_LOG_CATEGORY_RENDER, "GLRenderer initialised\n" );
	window_ = window;
}


GLRenderer::~GLRenderer()
{
	for (auto shader : ShaderQueue)
	{
		shader->unbind();
	}


}

GLvoid GLRenderer::Render()
{
	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	bindShaders();

	for (auto shader : ShaderQueue)
	{
		shader->render();
	}

	unbindShaders();
	
	
}

GLvoid GLRenderer::bindShaders()
{
	for (auto shader : ShaderQueue)
	{
		shader->bind();
	}

}

GLvoid GLRenderer::unbindShaders()
{
	for (auto shader : ShaderQueue)
	{
		shader->unbind();
	}
}


GLboolean GLRenderer::LoadShaders()
{
	GLboolean success = true;

	for (auto shader : ShaderQueue)
	{
		if( !shader->loadProgram() )
		{
			success = false;
			SDL_LogError(SDL_LOG_CATEGORY_VIDEO, "Unable to load shader %d\n", shader->getProgramID());
			break;
		}
		
	}


	SDL_LogDebug(SDL_LOG_CATEGORY_RENDER, "Shaders bound\n" );

	return success;
}

GLboolean GLRenderer::UpdateQueue(LShaderProgram* shader)
{
	if( !shader->loadProgram() )
	{
		SDL_LogError(SDL_LOG_CATEGORY_VIDEO, "Unable to load shader %d\n", shader->getProgramID() );
		return false;
	}
	SDL_LogDebug(SDL_LOG_CATEGORY_RENDER, "Shader Loaded");
	bindShaders();
	SDL_LogDebug(SDL_LOG_CATEGORY_RENDER, "Shader Bound");
	return true;

}

GLboolean GLRenderer::AddShaderToQueue(LShaderProgram* shader)
{
	ShaderQueue.push_back(shader);
	bool success = UpdateQueue(ShaderQueue.back());
	if (!success)
		ShaderQueue.pop_back();
	SDL_LogDebug(SDL_LOG_CATEGORY_RENDER, "Shader added to queue: %s\n", success ? "true" : "false" );
	return success;
}
