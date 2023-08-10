#include "Stage.h"
#include "Game.h"
#include "COLLISION_MAP.h"
#include "Cannon.h"
#include "TreeMeshComponent.h"
#include "UILog.h"
#include "PlayerHome.h"
#include "EnemyHome.h"
#include "CameraManager.h"
#include "NormalCamera.h"
#include "LookFieldCenterCamera.h"
#include "LookPHomeCamera.h"
#include "LookEHomeCamera.h"


Stage::Stage(Game* game)
	: Map(game)
{
	Data = GetGame()->GetAllData()->stageData;

	SetCollisionText(mMaptext1);
	CreateCollisions(mMaptext1);
	SetCollisionMap(new COLLISION_MAP(0.5f, mMaptext1));

	class TreeMeshComponent* tc = new TreeMeshComponent(this);
	tc->SetTree("background");
	mMiniMap = new UIMiniMap(GetGame(), this);
	mMiniMap->Create();

	PlayerHome* ph = new PlayerHome(GetGame(), Data.mPlayerHomeDefaultPos);
	ph->CreateHomeArea();

	EnemyHome* eh = new EnemyHome(GetGame());
	eh->SetUp();
	eh->SetPosition(Data.mEnemyHomeDefaultPos);
	eh->SetRotationY(Data.mEnemyHomeAngleOffset);
	eh->CreateHomeArea();

	new NormalCamera(GetGame());
	new LookFieldCenterCamera(GetGame());
	new LookPHomeCamera(GetGame());
	new LookEHomeCamera(GetGame());

	GetGame()->GetCameraManager()->ChangeCamera("PHomeCamera");

	//mModelCollisionsはマップ生成したら必要ないのでプレイするときだけ全消去
	while (!GetModelCollisions().empty())
	{
		delete GetModelCollisions().back();
	}
}

int Stage::SetUp()
{
	auto c = new Cannon(GetGame());
	if (GetGame()->GetActorManager()->GetPHome()->GetFirstGenerateCannonFlag() == 0)
	{
		GetGame()->GetActorManager()->GetPHome()->SetFirstGenerateCannonFlag(1);
		c->SetCNum(0);
	}
	c->SetUp();
	c->SetInitPosition(Data.mFirstCannonDefaultPos);
	c->SetPosition(GetGame()->GetActorManager()->GetPHome()->GetPosition());
	c->SetRotationY(Data.mFirstCannonAngleOffset);

	return 1;
}
