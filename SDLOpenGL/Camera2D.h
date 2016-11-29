#pragma once
class Camera2D
{
	bool isFreeMovement;
	bool isCameraCentered = false;
	GameObject* followedGameObject = nullptr;
	GameObject* dummyObjectPointer = nullptr;

	//Orthographic Projection Data
	GLfloat left, right, bottom, top;

	GLdouble cameraAcceleration = 1.5;
	GLfloat cameraMass;

	float cameraVelocityX = 0.0f;
	float cameraVelocityY = 0.0f;
	float cameraMomentumX = 0.0f;
	float cameraMomentumY = 0.0f;

	const float maxZoom = 2.0f; //zoom massimo
	float currentZoom;
public:
	Camera2D();
	Camera2D(float);
	Camera2D(float, float);
	~Camera2D();
	void follow(GameObject*);
	void enablefreeMovement();
	void disablefreeMovement();
	void update(float dt);
	void setOrtho2DProjection(GLfloat left, GLfloat right, GLfloat bottom, GLfloat top);
	void applyZoom();
	void applyZoom(float zoom_);
	void updateProjectionOnResize(GLfloat w, GLfloat h, GLfloat old_w, GLfloat old_h);
	void centerOnObject(GameObject*);
};

