#include "stdafx.h"
#include "Text.h"


//	TODO: [RELEASE] all'attuale implementazione, per ogni singolo testo viene caricato da memoria il relativo font \
	La struttura dovrebbe essere con una classe interna a Core che offre come "servizio" l'uso di Font caricati all'init: \
	Text text = FontManager->createText(std::string message, std::string font, SDL_color color, int size ); \
	dove FontManager incorpora una HashMap<std::string, TTF_font*>, oltre a gestire il caricamento e il rilascio dei font.

Text::Text(std::string path, std::string m, SDL_Color c, int size)
{
	pointSize = size;
	fontPath = path;
	message = m; 
	color = c;
	if (!loadFont())
	{
		SDL_LogDebug(SDL_LOG_CATEGORY_APPLICATION, "LoadFont failed: %s", TTF_GetError());
	}
}

bool Text::loadFont()
{
	//libero la memoria
	//free();
	//init del font e creazione della surface per il render
	font = TTF_OpenFont(fontPath.c_str(), pointSize);
	if (!(surface = TTF_RenderUTF8_Blended(font, message.c_str(), color)))
	{
		SDL_LogDebug(SDL_LOG_CATEGORY_APPLICATION, "Surface creation failed");
		return false;
	}
	
	//filtro la texture tramite maschere
	GLint texture_format;

	int colors = surface->format->BytesPerPixel;
	if (colors == 4) {   // alpha
		if (surface->format->Rmask == 0x000000ff)
			texture_format = GL_RGBA;
		else
			texture_format = GL_BGRA;
	}
	else {             // no alpha
		if (surface->format->Rmask == 0x000000ff)
			texture_format = GL_RGB;
		else
			texture_format = GL_BGR;
	}
	

	glGenTextures(1, &textureID);

	glBindTexture(GL_TEXTURE_2D, textureID);
	
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, surface->w, surface->h, 0, 
				 texture_format, GL_UNSIGNED_BYTE, surface->pixels);
	
	glGenerateMipmap(GL_TEXTURE_2D);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	textDimensions = glm::vec2(surface->w, surface->h);
	SDL_FreeSurface(surface);

	return true;
}

void Text::drawText(float posX, float posY)
{

	GLfloat Lvertices[] = {
		posX*textDimensions.x, posY*textDimensions.y,
		(posX + 1)*textDimensions.x, posY*textDimensions.y,
		(posX + 1)*textDimensions.x, (posY + 1)*textDimensions.y,
		posX*textDimensions.x, (posY + 1)*textDimensions.y
	};

	const float tex_verts[] = 
	{
		0,1,
		1,1,
		1,0,
		0,0
	};

	//SDL_LogDebug(SDL_LOG_CATEGORY_APPLICATION, "vertices: %f, %f", positionPx.x, positionPx.y);
	
	glEnableClientState(GL_VERTEX_ARRAY);
	glEnableClientState(GL_TEXTURE_COORD_ARRAY);
	glBindTexture(GL_TEXTURE_2D, textureID);
	glVertexPointer(2, GL_FLOAT, 0, Lvertices);
	
	glDrawArrays(GL_QUADS, 0, 4);

	glDisableClientState(GL_VERTEX_ARRAY);
	glDisableClientState(GL_TEXTURE_COORD_ARRAY);
}

Text::~Text()
{
	TTF_CloseFont(font);
}

void Text::free()
{
}