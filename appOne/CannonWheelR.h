#pragma once
#include "TreeMeshComponent.h"
#include "CharacterActor.h"
#include "Cannon.h"

class CannonWheelR : public CharacterActor
{
public:
	CannonWheelR(class Cannon* mOwner);
	void UpdateActor()override;
	int SetUp()override;
private:
	class Cannon* mOwner;
};

