#pragma once
#include "MoveComponent.h"
#include "Actor.h"
class InputComponent :
	public MoveComponent
{
public:
	InputComponent(class Actor* owner);
	void ProcessInput() override;
	//getter
	bool Right() { return mRight; }
	bool Left() { return mLeft; }
	bool Up() { return mUp; }
	bool Down() { return mDown; }
	bool StartMove() { return mMove; }
	bool StopMove() { return !mMove; }
	bool StartLaunch() { return mLaunch; }
	bool StopLaunch() { return !mLaunch; }
	bool Vertical() { return mVerticalMove; }
	bool Side() { return mSideMove; }
	bool Jump() { return mJump; }
	bool SelectBullet() { return mSelectBullet; }

private:
	bool mMove;
	bool mLaunch;
	bool mSelectBullet;
	int mRight;
	int mLeft;
	int mUp;
	int mDown;
	int mJump;

	bool mVerticalMove;
	bool mSideMove;

};
