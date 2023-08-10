#pragma once
#include "State.h"
#include "VECTOR.h"
class CannonGenerate :
	public State
{
public:
	CannonGenerate(class StateComponent* OwnerCompo) :State(OwnerCompo) {}
	const char* GetName() const override { return "Generate"; }
	void Update() override;
	void OnEnter() override;
	void OnExit()override;
private:
	VECTOR mTargetPos;
	VECTOR mFirstTarget;
	bool mFirstTargetCompleteFlag = false;
};
class CannonWait :
	public State
{
public:
	CannonWait(class StateComponent* OwnerCompo) :State(OwnerCompo) {}
	const char* GetName() const override { return "Wait"; }
	void Update() override;
};
class CannonMove :
	public State
{
public:
	CannonMove(class StateComponent* OwnerCompo) :State(OwnerCompo) {}
	const char* GetName() const override { return "Move"; }
	void Update() override;
};
class CannonMoveReturnHome :
	public State
{
public:
	CannonMoveReturnHome(class StateComponent* OwnerCompo) :State(OwnerCompo) {}
	const char* GetName() const override { return "Return"; }
	void Update() override;
};

class CannonMoveHomePatroll :
	public State
{
public:
	CannonMoveHomePatroll(class StateComponent* OwnerCompo) :State(OwnerCompo) {}
	const char* GetName() const override { return "HomePatroll"; }
	void Update() override;
};

class CannonMoveFieldPatroll :
	public State
{
public:
	CannonMoveFieldPatroll(class StateComponent* OwnerCompo) :State(OwnerCompo) {}
	const char* GetName() const override { return "FieldPatroll"; }
	void Update() override;
};

class CannonLaunch :
	public State
{
public:
	CannonLaunch(class StateComponent* OwnerCompo) : State(OwnerCompo) {}
	const char* GetName() const override { return "Launch"; }
	void OnEnter() override;
	void Update()override;
	void OnExit()override;
private:
	VECTOR mTarget;
	VECTOR mAdv;
};

class CannonRotate :
	public State
{
public:
	CannonRotate(class StateComponent* OwnerCompo) : State(OwnerCompo) {}
	const char* GetName() const override { return "Rotate"; }
	void OnEnter()override;
	void Update() override;
	void OnExit() override;
private:
	VECTOR mTarget;
	VECTOR mAdv;
};
