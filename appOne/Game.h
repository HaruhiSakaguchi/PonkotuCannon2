#pragma once
#include <vector>
#include "Manager.h"
#include "Container.h"
#include "UIManager.h"
#include "ActorManager.h"
#include "CameraManager.h"
#include "SoundVolumeManager.h"

class Game
{
public:
	Game();
	bool Initialize();
	void RunLoop();
	void Shutdown();
private:
	void ProcessInput();
	void UpdateGame();
	void GenerateOutput();
	void LoadData();
public:
	//ステート系

	enum class GameState
	{
		EGameplay,
		EPaused,
		EQuit
	};

	GameState GetState() { return mGameState; }
	void SetState(GameState gameState) { mGameState = gameState; }
	void SetCurState(UIMainState* state) { mCurState = state; }
	UIMainState* GetCurState() { return mCurState; }

private:
	GameState mGameState;
public:

	enum class StagePhase : int
	{
		EFIRST = 0,
		ESECOND = 1,
		ETHIRD = 2,
		EFOURTH = 3,
		EEND
	};

	StagePhase GetPhase() { return mPhase; }
	void SetPhase(const StagePhase phase) { mPhase = phase; }
	StagePhase GetInitPhase() { return mInitPhase; }
private:
	StagePhase mPhase;
	StagePhase mInitPhase;
public:

	struct Container* GetAllData() { return &mContainer; }
	class Renderer* GetRenderer() { return mRenderer; }
	bool GetContinueFlag() { return mContinueFlag; }
	void SetContinueFlag(bool flag) { mContinueFlag = flag; }

	class CameraManager* GetCameraManager() { return mCameraManager; }
	void SetCameraManager(class CameraManager* manager) { mCameraManager = manager; }

	class ActorManager* GetActorManager() { return mActorManager; }
	class UIManager* GetUIManager() { return mUIManager; }
	class SoundVolumeManager* GetSoundVolumeManager() { return mSoundVolumeManager; }

	void AddManager(class Manager* manager);
	void RemoveManager(class Manager* manager);

private:
	struct Container mContainer;
	class Renderer* mRenderer;
	class CameraManager* mCameraManager;
	class UIMainState* mCurState;
	class ActorManager* mActorManager;
	class UIManager* mUIManager;
	class SoundVolumeManager* mSoundVolumeManager;
	class std::vector<class Manager*>mManagers;
	//続けて最後までプレイするか否か
	bool mContinueFlag;
	bool mUpdatingManagers;
	class std::vector<class Manager*> mPendingManagers;
};

