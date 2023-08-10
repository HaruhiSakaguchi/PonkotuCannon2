#pragma once
#include <vector>
#include "Manager.h"
#include "Actor.h"

class ActorManager
	: public Manager
{
public:
	ActorManager(class Game* game);
	~ActorManager();
	void Update()override;
	void ProcessInput()override;
	//getter&setter
	const class std::vector<class Actor*>& GetActors() { return mActors; }
	const class std::vector<class CharacterActor*>& GetCharacters() { return mCharacters; }
	const class std::vector<class Enemy*>& GetEnemies() { return mEnemies; }
	const class std::vector<class ActorsWeapon*>& GetWeapons() { return mWeapons; }
	const class std::vector<class ItemObject*>& GetItems() { return mItems; }
	const class std::vector<class PSideCharacterActor*>& GetPSide() { return mPSideActors; }
	const class std::vector<class CapsuleComponent*>& GetCapsules() { return mCapsules; }
	void AddActor(class Actor* actor);
	void RemoveActor(class Actor* actor);

	void AddCharacter(class CharacterActor* actor);
	void RemoveCharacter(class CharacterActor* actor);
	void AddWeapons(class ActorsWeapon* weapon);
	void RemoveWeapons(class ActorsWeapon* weapon);
	void AddEnemies(class Enemy* enemy);
	void RemoveEnemies(class Enemy* enemy);
	void AddItems(class ItemObject* item);
	void RemoveItems(class ItemObject* item);
	void AddPSide(class PSideCharacterActor* actor);
	void RemovePSide(class PSideCharacterActor* actor);

	//当たり判定コンポーネントをここで管理する
	void AddCapsule(class CapsuleComponent* capsule);
	void RemoveCapsule(class CapsuleComponent* capsule);

	void ActorClear();

	class Map* GetStage() { return mStage; }
	void SetStage(class Map* map) { mStage = map; }
	class PlayerHome* GetPHome() { return mPHome; }
	class EnemyHome* GetEHome() { return mEHome; }
	void SetPHome(class PlayerHome* home) { mPHome = home; }
	void SetEHome(class EnemyHome* home) { mEHome = home; }
private:
	std::vector<class Actor*>mActors;
	std::vector<class CharacterActor*>mCharacters;
	std::vector<class Enemy*>mEnemies;
	std::vector<class ItemObject*>mItems;
	std::vector<class PSideCharacterActor*>mPSideActors;
	std::vector<class ActorsWeapon*> mWeapons;
	std::vector<class Actor*> mPendingActors;
	std::vector<class CapsuleComponent*>mCapsules;
	bool mUpdatingActors;
	class Map* mStage;
	class PlayerHome* mPHome;
	class EnemyHome* mEHome;
};

