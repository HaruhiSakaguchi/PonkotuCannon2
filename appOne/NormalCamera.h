#pragma once
#include "Camera.h"
class NormalCamera :
	public Camera
{
public:
	NormalCamera(class Game* game);
	void UpdateActor() override;
	struct IDATA
	{
		VECTOR mPos;
		VECTOR mLookatPosOffset;
		float mRotX = 0.0f;
	};
private:
	IDATA iData;
};


