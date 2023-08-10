#pragma once
#include "Game.h"

class Transition
{
public:
	Transition(class Game* game);
	virtual ~Transition() {};
	virtual void create() {};
	void inTrigger();
	void outTrigger();
	void Draw();
	virtual void inTriggerProc() {};
	virtual bool inProc() { return true; }
	virtual void outTriggerProc() {};
	virtual bool outProc() { return true; }
	bool inEndFlag();
	bool outEndFlag();
	class Game* GetGame() { return mGame; }
private:
	enum class STATE {
		EIN_TRIGGER, EIN_NOW, EIN_END,
		EOUT_TRIGGER, EOUT_NOW, EOUT_END
	};
	STATE State;
private:
	class Game* mGame;
};

