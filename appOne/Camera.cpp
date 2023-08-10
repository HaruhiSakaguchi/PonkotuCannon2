#include "Camera.h"
#include "Game.h"

Camera::Camera(Game* game)
	: Actor(game)
	, mLookatPos(0.0f, 0.0f, 0.0f)
{
	Data = GetGame()->GetAllData()->cameraData;
	GetGame()->GetCameraManager()->AddCamera(this);
	mCamName = "Camera";
}

Camera::~Camera()
{
	GetGame()->GetCameraManager()->RemoveCamera(this);
}