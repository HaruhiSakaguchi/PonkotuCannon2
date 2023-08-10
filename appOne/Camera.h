#pragma once
#include "Actor.h"
#include "VECTOR.h"
#include <string>

class Camera :
	public Actor
{
public:
	Camera(class Game* game);
	virtual ~Camera();
	const VECTOR& GetLookatPos() { return mLookatPos; }
	const std::string& GetCamName() { return mCamName; }

	struct DATA
	{
		float mDistanceFromLookatPos = 0.0f;
		VECTOR mOffsetPos;
		VECTOR mUpVec;
		float mChangePosSpeed = 0.0f;
	};
protected:
	DATA Data;
	std::string mCamName;
	VECTOR mLookatPos;
};
