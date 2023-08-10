#pragma once
#include "State.h"
#include "VECTOR.h"
#include "sound.h"

class TamaWait :
	public State
{
public:
	TamaWait(class StateComponent* OwnerCompo) :State(OwnerCompo) {}
	const char* GetName() const override { return "Wait"; }
	virtual void OnEnter()override;
	void Update() override;
private:
	float elapsedTime = 0.0f;

};
class TamaMove :
	public State
{
public:
	TamaMove(class StateComponent* OwnerCompo) :State(OwnerCompo) {}
	const char* GetName() const override { return "Move"; }
	virtual void OnEnter()override;
	void Update() override;
private:
	VECTOR mAdv;
	VECTOR mTarget;
	VECTOR mTmpAngle;
	int mCnt = 0;
};

class TamaSeache :
	public State
{
public:
	TamaSeache(class StateComponent* OwnerCompo) :State(OwnerCompo) {}
	const char* GetName()const override { return "Search"; }
	void Update()override;
	virtual void OnEnter()override;
private:
	int mCnt = 0;
	int mRotateCnt = 0;
};

class TamaRockOn :
	public State
{
public:
	TamaRockOn(class StateComponent* OwnerCompo) :State(OwnerCompo) {}
	const char* GetName() const override { return "RockOn"; }
	virtual void OnEnter()override;
	virtual void OnExit()override;
	void Update() override;
private:
	VECTOR mAdv;
	VECTOR mTarget;
	VECTOR mTmpAngle;
	bool mDushFlag = true;
	int mCnt = 0;

};

class TamaCharge :
	public State
{
public:
	TamaCharge(class StateComponent* OwnerCompo) : State(OwnerCompo) {}
	const char* GetName() const override { return "Charge"; }
	virtual void OnEnter()override;
	virtual void OnExit()override;
	void Update()override;
private:
	VECTOR mTarget;
	VECTOR mDir;
	int mCnt = 0;
	float mReb = 1.0f;
};

class TamaAttack :
	public State
{
public:
	TamaAttack(class StateComponent* OwnerCompo) :State(OwnerCompo) {}
	const char* GetName() const override { return "Attack"; }
	void Update() override;
	virtual void OnEnter() override;
	virtual void OnExit() override;
private:
	int mCnt = 0;
	float mTime = 0;
	float mMaxTime = 120.0f;
	VECTOR mTarget;
	VECTOR mRotation;
	int mAttackFlame = 0;
};

class TamaGenerate :
	public State
{
public:
	TamaGenerate(class StateComponent* OwnerCompo) :State(OwnerCompo) {}
	const char* GetName()const override { return "Generate"; }
	void Update()override;
	virtual void OnEnter()override;
	virtual void OnExit()override;
private:
	VECTOR mTargetPos;
	VECTOR mFirstTarget;
	bool mFirstTargetCompleteFlag = false;
};



