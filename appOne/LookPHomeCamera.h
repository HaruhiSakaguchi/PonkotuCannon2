#pragma once
#include "Camera.h"

class LookPHomeCamera :
	public Camera
{
public:
	LookPHomeCamera(class Game* game);
	void UpdateActor() override;
	struct IDATA
	{
		VECTOR mLookatPosOffset;
	};
private:
	IDATA iData;
};

