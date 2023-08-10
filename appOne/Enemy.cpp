#include "Enemy.h"
#include "Game.h"

Enemy::Enemy(class Game* game)
	: CharacterActor(game)
{
	GetGame()->GetActorManager()->AddEnemies(this);
}

Enemy::~Enemy()
{
	GetGame()->GetActorManager()->RemoveEnemies(this);
}