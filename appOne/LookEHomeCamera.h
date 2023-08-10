#pragma once
#include "Camera.h"
class LookEHomeCamera :
	public Camera
{
public:
	LookEHomeCamera(class Game* game);
	void UpdateActor() override;
	struct IDATA
	{
		VECTOR mLookatPosOffset;
	};
private:
	IDATA iData;
};


