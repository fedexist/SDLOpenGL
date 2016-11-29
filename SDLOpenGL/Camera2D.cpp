#include "stdafx.h"
#include "Camera2D.h"

Camera2D::Camera2D()
{
	
}

Camera2D::Camera2D(float)
{
}

Camera2D::Camera2D(float mass, float zoom_)
{
	cameraMass = mass; //Parametro principale
	if (zoom_ <= 1.000f)
		currentZoom = zoom_ * maxZoom;
	else
		currentZoom = maxZoom;
	isFreeMovement = false;
	followedGameObject = dummyObjectPointer = nullptr;
}


Camera2D::~Camera2D()
{
}

void Camera2D::follow(GameObject * obj)
{
	followedGameObject = dummyObjectPointer = obj;
	isFreeMovement = false;
}

void Camera2D::enablefreeMovement()
{
	if(!isFreeMovement)
	{
		isFreeMovement = true;
		followedGameObject = nullptr;
		isCameraCentered = false;	
	}
}

void Camera2D::disablefreeMovement()
{
	if(isFreeMovement)
	{
		isFreeMovement = false;
		followedGameObject = dummyObjectPointer;
	}
}

void Camera2D::update(float dt)
{
	if(!isFreeMovement)
	{
		//prima si centra la camera
		if (!isCameraCentered)
			centerOnObject(followedGameObject);

		//Traslazione in coordinate mondo
		glm::vec2 translation = followedGameObject->getLastTranslation();
		glMatrixMode(GL_PROJECTION);
		glTranslatef(-translation.x , -translation.y, 0.0f);

	}
	else
	{
		const Uint8* currentKeyStates = SDL_GetKeyboardState(nullptr);
		float local_dt = 1.0f;//(dt + 1) * 0.28f; //CHANGEEEEEE

		float alpha, beta, mu, nu; //alpha è la forza per ogni tick in cui è premuto il tasto, 
								//beta è la costante di resistenza(tipo attrito)
								//mu è la velocità massima
								//nu è la forza dopo un tick di forza partendo da fermo (resistenza statica) non utilizzato
		alpha = 1;
		mu = 20;
		beta = alpha/mu; //condizione per il quale a velocità massima mantenendo acceleratore la velocità sia costante
		nu = beta * cameraMass; //ragionevole e inutilizzato

		float oldVelocityX = cameraVelocityX;
		float oldVelocityY = cameraVelocityY;
		float oldMomentumX = cameraMomentumX;
		float oldMomentumY = cameraMomentumY;
		float ForceInputX;
		float ForceInputY;
		if (currentKeyStates[SDL_SCANCODE_W])
		{
			//SDL_LogDebug(SDL_LOG_CATEGORY_INPUT, "W is pressed");
			ForceInputY = 1;

		}
		else if (currentKeyStates[SDL_SCANCODE_S])
		{
			//SDL_LogDebug(SDL_LOG_CATEGORY_INPUT, "S is pressed");
			ForceInputY = -1;
		}
		else
		{
			ForceInputY = 0;
		}
		if (currentKeyStates[SDL_SCANCODE_D])
		{
			//SDL_LogDebug(SDL_LOG_CATEGORY_INPUT, "D is pressed");
			ForceInputX = 1;
		}
		else if (currentKeyStates[SDL_SCANCODE_A])
		{
			//SDL_LogDebug(SDL_LOG_CATEGORY_INPUT, "A is pressed");
			ForceInputX = -1;
		}
		else
		{
			ForceInputX = 0;
		}

		if (ForceInputX != 0 && ForceInputY != 0) //se vado in diagonale normalizzo il vettore
		{
			ForceInputX *= sqrt(2) / 2;
			ForceInputY *= sqrt(2) / 2;
		}
	
		float StaticResistanceX = 0;
		float StaticResistanceY = 0;

		if (oldVelocityX > -0.1 && oldVelocityX < 0.1)
			StaticResistanceX = - nu * ForceInputX;
	
		if (oldVelocityY > -0.1 && oldVelocityY < 0.1)
			StaticResistanceY = -nu * ForceInputY;

		float ForceX = alpha * ForceInputX - beta * oldVelocityX + StaticResistanceX; //la forza totale è quella di input meno la viscosità
		float ForceY = alpha * ForceInputY - beta * oldVelocityY + StaticResistanceY;

		float MomX = oldMomentumX + ForceX * local_dt * 2; //integro la forza per aggiornare la quantità di moto
		float MomY = oldMomentumY + ForceY * local_dt * 2;

		cameraMomentumX = MomX;
		cameraMomentumY = MomY;

		float VelX = MomX / cameraMass; //calcolo la velocità dalla quantità di moto
		float VelY = MomY / cameraMass;

		cameraVelocityX = VelX;
		cameraVelocityY = VelY;

		//SDL_LogDebug(SDL_LOG_CATEGORY_INPUT, "%f,%f,%f", VelX, VelY, sqrt(pow(VelX,2)+pow(VelY,2)));

		float translationX = VelX * local_dt * 2; //calcolo spostamento dalla velocità
		float translationY = VelY * local_dt * 2;

		bottom += translationY;
		top += translationY;
		right += translationX;
		left += translationX;

	

		glMatrixMode(GL_PROJECTION);
	
		glTranslatef(-translationX, -translationY, 0.0);
		SDL_PumpEvents();

	}
}

void Camera2D::setOrtho2DProjection(GLfloat left_, GLfloat right_, GLfloat bottom_, GLfloat top_)
{
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();

	left = left_;
	right = right_;
	bottom = bottom_;
	top = top_;

	gluOrtho2D(left, right, bottom, top);

	SDL_LogDebug(SDL_LOG_CATEGORY_RENDER, "Ortho2D projection set at: left: %f, right: %f, bottom: %f, top: %f", left, right, bottom, top);

}

void Camera2D::applyZoom()
{
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluOrtho2D(left/currentZoom, right/currentZoom, bottom/currentZoom, top/currentZoom);

}

void Camera2D::applyZoom(float zoom_)
{
	if (zoom_ <= 1.000f)
		currentZoom = zoom_ * maxZoom;
	else
		currentZoom = maxZoom;
	applyZoom();
}


void Camera2D::updateProjectionOnResize(GLfloat w, GLfloat h, GLfloat resize_w, GLfloat resize_h)
{
	//SDL_LogDebug(SDL_LOG_CATEGORY_APPLICATION, "Left: %f, right: %f, bottom: %f, top: %f", left, right, bottom, top);
	//SDL_LogDebug(SDL_LOG_CATEGORY_APPLICATION, "Viewport W: %f, Viewport H: %f, Resize W: %f, Resize H: %f", w, h, resize_w, resize_h);
	//SDL_LogDebug(SDL_LOG_CATEGORY_APPLICATION, "Aspect Ratio: %f, zoom/ratio: %f", ratio, currentZoom/ratio);

	if(!isFreeMovement)
	{
		glViewport(0, 0, w, h);
		setOrtho2DProjection(0, w, 0, h);
		centerOnObject(followedGameObject);		
	}
}

void Camera2D::centerOnObject(GameObject*)
{
		glm::vec2 worldPosition = followedGameObject->gridPositionToWorld();

		float n_left = (left - right)/currentZoom + worldPosition.x;
		float n_right = right/currentZoom + worldPosition.x;
		float n_bottom = (bottom - top)/currentZoom + worldPosition.y;
		float n_top = top/currentZoom + worldPosition.y;

		setOrtho2DProjection(n_left, n_right, n_bottom, n_top);

		isCameraCentered = true;
}
