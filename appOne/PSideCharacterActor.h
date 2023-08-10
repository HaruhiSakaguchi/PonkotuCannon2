#pragma once
#include "CharacterActor.h"
#include "UIPSideCharacterStatusBase.h"
#include "Items.h"

class PSideCharacterActor :
	public CharacterActor
{
public:
	PSideCharacterActor(class Game* game);
	virtual ~PSideCharacterActor();
	virtual void Dead()override;
	void SetUI(UIScreen* ui) { mUI = ui; }
	class UIScreen* GetUI() { return mUI; }
	void SetNum(int num) { mNum = num; }
	int GetNum() { return mNum; }
	class PowerUpEffect* GetPower() { return mPower; }
	class SpeedUpEffect* GetSpeed() { return mSpeed; }
	class BarrierEffect* GetBarrier() { return mBarrier; }
	class RapidFireEffect* GetRapid() { return mRapid; }
	void SetPower(class PowerUpEffect* power) { mPower = power; }
	void SetSpeed(class SpeedUpEffect* speed) { mSpeed = speed; }
	void SetBarrier(class BarrierEffect* barrier) { mBarrier = barrier; }
	void SetRapid(class RapidFireEffect* rapid) { mRapid = rapid; }
	virtual void Damage(int damage = 0)override;
protected:
	//ƒAƒCƒeƒ€‚Ì•ª—Þ
	class PowerUpEffect* mPower;
	class SpeedUpEffect* mSpeed;
	class BarrierEffect* mBarrier;
	class RapidFireEffect* mRapid;
private:
	int mNum;
	class UIScreen* mUI;
protected:
	float mMaxDamageInterval;
};

