#pragma once
#include "ItemObject.h"
#include "ItemEffect.h"
#include "sound.h"

class Recovery : public ItemObject
{
public:
	Recovery(class Game* game);
	bool update()override;
};

class RecoveryEffect : public ItemEffect
{
public:
	RecoveryEffect(class PSideCharacterActor* owner);
private:
	int mRecoveryHp = 3;
};

class SpeedUp : public ItemObject
{
public:
	SpeedUp(class Game* game);
	bool update()override;
};

class SpeedUpEffect : public ItemEffect
{
public:
	SpeedUpEffect(class PSideCharacterActor* owner);
	void UpdateActor()override;
	void Dead()override;
private:
	float mSpeedUpRate = 0.1f;
};

class PowerUp : public ItemObject
{
public:
	PowerUp(class Game* game);
	bool update()override;
};

class PowerUpEffect : public ItemEffect
{
public:
	PowerUpEffect(class PSideCharacterActor* owner);
	void UpdateActor()override;
	void Dead()override;
};

class RapidFire : public ItemObject
{
public:
	RapidFire(class Game* game);
	bool update()override;
};

class RapidFireEffect : public ItemEffect
{
public:
	RapidFireEffect(class PSideCharacterActor* owner);
	void UpdateActor()override;
	void Dead()override;
private:
	float mLaunchIntervalDecreaseRate = 0.1f;
};

class Barrier : public ItemObject
{
public:
	Barrier(class Game* game);
	bool update()override;
};

class BarrierEffect : public ItemEffect
{
public:
	BarrierEffect(class PSideCharacterActor* owner);
	void Dead()override;
};