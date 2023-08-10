#pragma once
#include "Camera.h"

class LookFieldCenterCamera :
	public Camera
{
public:
	LookFieldCenterCamera(class Game* game);
	void UpdateActor() override;
	struct IDATA
	{
		VECTOR mPos;
		float mRotX = 0.0f;
	};
private:
	IDATA iData;
};

