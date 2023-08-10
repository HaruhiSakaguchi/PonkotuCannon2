#include "State.h"
#include "VECTOR.h"

class SatelliteNormal :
	public State
{
public:
	SatelliteNormal(class StateComponent* OwnerCompo) :State(OwnerCompo) {}
	const char* GetName() const override { return "Normal"; }
	void Update() override;
};
class SatelliteMove :
	public State
{
public:
	SatelliteMove(class StateComponent* OwnerCompo) :State(OwnerCompo) {}
	const char* GetName() const override { return "Move"; }
	virtual void OnEnter()override;
	void Update() override;
private:
	VECTOR mTarget;
	VECTOR mAdv;
	int mCnt = 0;
};
class SatelliteRockOn :
	public State
{
public:
	SatelliteRockOn(class StateComponent* OwnerCompo) : State(OwnerCompo) {}
	const char* GetName() const override { return "RockOn"; }
	virtual void OnEnter();
	void Update() override;
private:
	VECTOR mTarget;
	VECTOR mAdv;
};
class SatelliteAttack :
	public State
{
public:
	SatelliteAttack(class StateComponent* OwnerCompo) :State(OwnerCompo) {}
	const char* GetName() const override { return "Attack"; }
	virtual void OnEnter()override;
	virtual void OnExit()override;
	void Update() override;
private:
	VECTOR mTarget;
	VECTOR mAdv;
	int mCnt = 0;
	int mMaxCnt = 0;
	int mRotateCnt = 0;
};

class SatelliteGenerate :
	public State
{
public:
	SatelliteGenerate(class StateComponent* OwnerCompo) :State(OwnerCompo) {}
	const char* GetName()const override { return "Generate"; }
	void Update()override;
	virtual void OnEnter()override;
	virtual void OnExit()override;

private:
	VECTOR mTargetPos;
	VECTOR mFirstTarget;
	bool mFirstTargetCompleteFlag = false;
	bool mRotateFlag = false;
	bool mSwitch = false;
};