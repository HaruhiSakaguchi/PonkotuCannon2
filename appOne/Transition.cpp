#include "Transition.h"
#include "graphic.h"

Transition::Transition(class Game* game)
	: mGame(game)
	, State(STATE::EOUT_END)
{
}

void Transition::inTrigger()
{
	if (State == STATE::EOUT_END)
	{
		State = STATE::EIN_TRIGGER;
	}
}

void Transition::outTrigger()
{
	if (State == STATE::EIN_END)
	{
		State = STATE::EOUT_TRIGGER;
	}
}

void Transition::Draw() {
	if (State == STATE::EIN_END || State == STATE::EOUT_END)
	{
		return;
	}
	switch (State)
	{
	case STATE::EIN_TRIGGER:
		inTriggerProc();
		State = STATE::EIN_NOW;
		break;
	case STATE::EIN_NOW:
		if (inProc())
		{
			State = STATE::EIN_END;
		}
		break;
	case STATE::EOUT_TRIGGER:
		outTriggerProc();
		State = STATE::EOUT_NOW;
		break;
	case STATE::EOUT_NOW:
		if (outProc())
		{
			State = STATE::EOUT_END;
		}
		break;
	case STATE::EIN_END:
		break;
	case STATE::EOUT_END:
		break;
	}
}

//inÇ‹ÇΩÇÕoutÇ™èIóπÇµÇΩÇ©Ç«Ç§Ç©
bool Transition::inEndFlag()
{
	bool flag = State == STATE::EIN_END;
	return flag;
}

bool Transition::outEndFlag()
{
	bool flag = State == STATE::EOUT_END;
	return flag;
}
