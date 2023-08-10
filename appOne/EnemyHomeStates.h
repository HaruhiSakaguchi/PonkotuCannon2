#pragma once
#include "State.h"

class EnemyHomeWait :
    public State
{
public:

    EnemyHomeWait(class StateComponent* OwnerCompo) :State(OwnerCompo) {};
    const char* GetName() const override { return "Wait"; }
    void Update() override;
};

class EnemyHomeGenerate :
    public State
{
public:

    EnemyHomeGenerate(class StateComponent* OwnerCompo) : State(OwnerCompo) {};
    const char* GetName() const override { return "Generate"; }
    void Update() override;
};

class EnemyHomeLvUp :
    public State
{
public:

    EnemyHomeLvUp(class StateComponent* OwnerCompo) :State(OwnerCompo) {};
    const char* GetName() const override { return "LvUp"; }
    void Update() override;
private:
    int mLvUpCnt = 0;
};

class EnemyHomeSpecial :
    public State
{
public:

    EnemyHomeSpecial(class StateComponent* OwnerCompo) :State(OwnerCompo) {};
    const char* GetName() const override { return "Special"; }
    void Update() override;
    void OnEnter() override;
    void OnExit()override;
private:
    int mSpecialCnt = 0;
    int mScnt = 0;
};

