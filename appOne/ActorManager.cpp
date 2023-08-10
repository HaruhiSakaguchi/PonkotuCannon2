#include "ActorManager.h"
#include "Game.h"
#include "Map.h"
#include "Enemy.h"
#include "ItemObject.h"
#include "ActorsWeapon.h"
#include "PlayerHome.h"
#include "EnemyHome.h"
#include "CapsuleComponent.h"

ActorManager::ActorManager(class Game* game)
	: Manager(game)
	, mUpdatingActors(false)
	, mStage(nullptr)
	, mPHome(nullptr)
	, mEHome(nullptr)
{
};

ActorManager::~ActorManager()
{
	ActorClear();
}

void ActorManager::Update()
{
	if (mGame->GetState() == Game::GameState::EGameplay)
	{
		// mActors更新(更新中にnewされたActorはmPendingActorsに追加される)
		mUpdatingActors = true;
		for (auto actor : mActors)
		{
			actor->Update();
		}
		mUpdatingActors = false;

		// 追加を延期したActorをmActorsに追加する
		for (auto pending : mPendingActors)
		{
			mActors.emplace_back(pending);
		}
		mPendingActors.clear();

		// Dead状態のActorを直下のdeadActorsに抽出する
		std::vector<Actor*> deadActors;
		for (auto actor : mActors)
		{
			if (actor->GetState() == Actor::State::EDead)
			{
				deadActors.emplace_back(actor);
			}
		}
		// deadActorsを消去する(mActorsからも取り除かれる)
		for (auto actor : deadActors)
		{
			actor->Dead();
			delete actor;
		}

	}
}

void ActorManager::ProcessInput()
{
	mUpdatingActors = true;

	for (auto actor : mActors)
	{
		actor->ProcessInput();
	}

	mUpdatingActors = false;
}

void ActorManager::AddActor(class Actor* actor)
{
	if (mUpdatingActors)
	{
		mPendingActors.emplace_back(actor);
	}
	else
	{
		mActors.emplace_back(actor);
	}
}

void ActorManager::RemoveActor(class Actor* actor)
{
	//このactorがmActorsにあるか探す
	auto iter = std::find(mActors.begin(), mActors.end(), actor);
	if (iter != mActors.end())
	{
		//このActorとケツのActorを入れ替える(消去後コピー処理を避けるため)
		std::iter_swap(iter, mActors.end() - 1);
		mActors.pop_back();
	}
}

void ActorManager::AddCharacter(class CharacterActor* actor)
{
	mCharacters.emplace_back(actor);
}

void ActorManager::RemoveCharacter(class CharacterActor* actor)
{
	//このactorがmActorsにあるか探す
	auto iter = std::find(mCharacters.begin(), mCharacters.end(), actor);
	if (iter != mCharacters.end())
	{
		//このActorとケツのActorを入れ替える(消去後コピー処理を避けるため)
		std::iter_swap(iter, mCharacters.end() - 1);
		mCharacters.pop_back();
	}
}

void ActorManager::AddPSide(class PSideCharacterActor* actor)
{
	mPSideActors.emplace_back(actor);
}

void ActorManager::RemovePSide(class PSideCharacterActor* actor)
{
	auto iter = std::find(mPSideActors.begin(), mPSideActors.end(), actor);
	if (iter != mPSideActors.end())
	{
		//このActorとケツのActorを入れ替える(消去後コピー処理を避けるため)
		std::iter_swap(iter, mPSideActors.end() - 1);
		mPSideActors.pop_back();
	}
}

void ActorManager::AddWeapons(class ActorsWeapon* weapon)
{
	mWeapons.emplace_back(weapon);
}

void ActorManager::RemoveWeapons(class ActorsWeapon* weapon)
{
	//このactorがmActorsにあるか探す
	auto iter = std::find(mWeapons.begin(), mWeapons.end(), weapon);
	if (iter != mWeapons.end())
	{
		//このActorとケツのActorを入れ替える(消去後コピー処理を避けるため)
		std::iter_swap(iter, mWeapons.end() - 1);
		mWeapons.pop_back();
	}
}

void ActorManager::AddEnemies(class Enemy* enemy)
{
	mEnemies.emplace_back(enemy);
}

void ActorManager::RemoveEnemies(class Enemy* enemy)
{
	//このactorがmActorsにあるか探す
	auto iter = std::find(mEnemies.begin(), mEnemies.end(), enemy);
	if (iter != mEnemies.end())
	{
		//このActorとケツのActorを入れ替える(消去後コピー処理を避けるため)
		std::iter_swap(iter, mEnemies.end() - 1);
		mEnemies.pop_back();
	}
}

void ActorManager::AddItems(class ItemObject* item)
{
	mItems.emplace_back(item);
}

void ActorManager::RemoveItems(class ItemObject* item)
{
	//このactorがmActorsにあるか探す
	auto iter = std::find(mItems.begin(), mItems.end(), item);
	if (iter != mItems.end())
	{
		//このActorとケツのActorを入れ替える(消去後コピー処理を避けるため)
		std::iter_swap(iter, mItems.end() - 1);
		mItems.pop_back();
	}
}

void ActorManager::AddCapsule(CapsuleComponent* capsule)
{
	mCapsules.emplace_back(capsule);
}

void ActorManager::RemoveCapsule(CapsuleComponent* capsule)
{
	//このactorがmActorsにあるか探す
	auto iter = std::find(mCapsules.begin(), mCapsules.end(), capsule);
	if (iter != mCapsules.end())
	{
		//このActorとケツのActorを入れ替える(消去後コピー処理を避けるため)
		std::iter_swap(iter, mCapsules.end() - 1);
		mCapsules.pop_back();
	}
}

void ActorManager::ActorClear()
{
	while (!mActors.empty())
	{
		delete mActors.back();
	}
}

