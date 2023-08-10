#include "Manager.h"
#include "Game.h"

Manager::Manager(Game* game)
	:mGame(game)
{
	mGame->AddManager(this);
}

Manager::~Manager()
{
	mGame->RemoveManager(this);
}
