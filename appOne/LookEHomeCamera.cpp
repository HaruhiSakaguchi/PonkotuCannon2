#include "LookEHomeCamera.h"
#include "Game.h"
#include "PlayerHome.h"

LookEHomeCamera::LookEHomeCamera(Game* game)
	: Camera(game)
{
	mCamName = "EHomeCamera";
	GetGame()->GetCameraManager()->RegisterCamera(this);
	iData = GetGame()->GetAllData()->lookEHomeCameraData;
}

void LookEHomeCamera::UpdateActor()
{
	VECTOR pos = GetPosition();

	if (GetGame()->GetActorManager()->GetEHome())
	{
		SetPosition(GetGame()->GetActorManager()->GetEHome()->GetPosition());
		mLookatPos = GetGame()->GetActorManager()->GetEHome()->GetPosition();
	}
	pos = GetPosition() + iData.mLookatPosOffset;

	SetPosition(pos);
}