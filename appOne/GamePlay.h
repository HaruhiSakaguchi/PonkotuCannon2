#pragma once
#include "UIMainState.h"
#include "sound.h"

class GamePlay : public UIMainState
{
public:
	GamePlay(class Game* game);
	~GamePlay();
	void Update()override;
	void ChangeBgm();
	void Draw()override;
	struct DATA
	{
		int mBgm1SoundVolumeOffset = 0;
		int mBgm2SoundVolumeOffset = 0;
		int mBgm1 = -1;
		int mBgm2 = -1;
		const char* mPauseButtonText = nullptr;
		const char* mPauseHelpText = nullptr;
	};
private:
	DATA Data;
private:
	int mGameOverFlag;
	int mGameClearFlag;
	class Map* mMap;
	int mBgm;
	int mSoundOffset;
	bool mPlayBgmFlag;
	class Button* mPauseButton;
};