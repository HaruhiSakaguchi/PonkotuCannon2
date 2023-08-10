#include "UIMainState.h"
#include "Game.h"

UIMainState::UIMainState(Game* game)
	: UIState(game)
	, mMState(State::EEmpty)
{
	mGame->SetCurState(this);
}
