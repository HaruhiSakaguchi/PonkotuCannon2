#include "UIState.h"
#include "Game.h"
#include "TransitionFade.h"

UIState::UIState(class Game* game)
	: UIScreen(game)
{
	SetUp();
};

void UIState::Update()
{
	if (mGame->GetRenderer()->GetTransition())
	{
		if (mGame->GetRenderer()->GetTransition()->outEndFlag())
		{
			ChangeOption();
			CloseMe();
		}
	}
}

void UIState::ChangeState()
{
	mGame->GetRenderer()->GetTransition()->outTrigger();
}


