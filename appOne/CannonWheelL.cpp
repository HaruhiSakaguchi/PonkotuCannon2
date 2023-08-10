#include "CannonWheelL.h"
#include "Game.h"

CannonWheelL::CannonWheelL(class Cannon* owner)
	: CharacterActor(owner->GetGame())
	, mOwner(owner)
{
	SetUp();
}

int CannonWheelL::SetUp()
{
	auto tc = new TreeMeshComponent(this);
	tc->SetTree("CannonWheel");

	SetNormalMesh(tc);
	SetCategory(Actor::ActorsCategory::EObject);
	return 0;
}

void CannonWheelL::UpdateActor()
{
	if (mOwner->GetState() == State::EActive)
	{
		MATRIX Master;
		Master.identity();

		Master.mulTranslate(mOwner->GetPosition() + mOwner->GetCapsulOffset());
		Master.mulRotateY(mOwner->GetRotation().y);
		Master.mulRotateY(3.141592f);

		MATRIX WheelLModel;
		WheelLModel.identity();
		WheelLModel.mulTranslate(GetGame()->GetAllData()->cannonData.mWheelOffsetPos);

		WheelLModel.mulRotateY(-GetGame()->GetAllData()->cannonData.mWheelAngleOffset);
		WheelLModel = Master * WheelLModel;
		SetPosition(WheelLModel._14, WheelLModel._24, WheelLModel._34);
		SetRotation(VECTOR(0.0f, mOwner->GetRotation().y - 3.1415926f / 2.0f, 0.0f));
		SetDamageInterval(mOwner->GetDamageInterval());
	}
	else
	{
		SetState(State::EDead);
	}

}