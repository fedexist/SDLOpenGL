// stdafx.h : file di inclusione per file di inclusione di sistema standard
// o file di inclusione specifici del progetto utilizzati di frequente, ma
// modificati raramente
//

#pragma once

#include "targetver.h"

//standard libraries inclusions
#include <stdio.h>
#include <tchar.h>
#include <sstream>
#include <vector>
#include <algorithm>

//glew, glu and glm inclusions
#include <GL/glew.h>
#include <GL/GL.h>
#include <gl/GLU.h>
#include <glm.hpp>
#include <gtx/norm.hpp>
#include <gtc/matrix_transform.hpp>
#include <gtc/type_ptr.hpp>

//SDL inclusions
#include <SDL.h>
#include <SDL_image.h>
#include <SDL_opengl.h>

//Core engine header inclusion
#include "Core.h"

#pragma comment( lib, "opengl32.lib" )
#pragma comment( lib, "glu32.lib" )