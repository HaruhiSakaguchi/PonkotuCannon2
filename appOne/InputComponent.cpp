#include "InputComponent.h"
#include "input.h"

InputComponent::InputComponent(Actor* owner)
	:MoveComponent(owner)
	, mMove(false)
	, mLaunch(false)
	, mSelectBullet(false)
	, mRight(0)
	, mLeft(0)
	, mUp(0)
	, mDown(0)
	, mJump(0)
	, mVerticalMove(false)
	, mSideMove(false)
{
}

void InputComponent::ProcessInput()
{
	mJump = isTrigger(KEY_SPACE);
	mLaunch = isPress(MOUSE_LBUTTON);

	mLeft = isPress(KEY_A);
	mRight = isPress(KEY_D);
	mUp = isPress(KEY_W);
	mDown = isPress(KEY_S);
	mSelectBullet = isPress(MOUSE_RBUTTON);

	mVerticalMove = mUp || mDown;
	mSideMove = mLeft || mRight;

	mMove = mLeft || mRight || mUp || mDown;

}
