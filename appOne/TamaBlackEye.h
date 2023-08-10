#pragma once
#include "Tama.h"
#include "CharacterActor.h"

class TamaBlackEye : public CharacterActor
{
public:
	TamaBlackEye(class Tama* owner);
	int SetUp()override;
	void UpdateActor();
private:
	VECTOR mOffsetPos;
	class Tama* mOwner;
	float mScale;
};

