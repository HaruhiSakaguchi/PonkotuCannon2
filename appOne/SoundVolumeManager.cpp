#include "SoundVolumeManager.h"
#include "Game.h"
#include "FILE_BUFFER.h"
#include "NAME.h"

SoundVolumeManager::SoundVolumeManager(class Game* game)
	: Manager(game)
	, mEffectVol(0)
	, mSetVolume(0)
	, mTmpEffectVol(0)
	, mTmpVolume(0)
	, mSoundFlag(true)
	, mBgmFlag(true)
{
	LoadText(mSaveFileName);
}

SoundVolumeManager::~SoundVolumeManager()
{
	SaveText(mSaveFileName);
}

void SoundVolumeManager::LoadText(const char* fileName)
{
	FILE_BUFFER fb(fileName);
	NAME name;

	fb.readString();
	while (!fb.end()) {
		if (fb == "SoundSwitch")
		{
			mSoundFlag = fb.readInt();
			fb.readString();
		}
		if (fb == "BgmSwitch")
		{
			mBgmFlag = fb.readInt();
			fb.readString();
		}
		if (fb == "Effect")
		{
			mEffectVol = fb.readInt();
			fb.readString();
		}
		if (fb == "Set")
		{
			mSetVolume = fb.readInt();
		}

		fb.readString();
	}
}

void SoundVolumeManager::SaveText(const char* fileName)
{
	FILE* fp = NULL;
	fopen_s(&fp, fileName, "w");
	if (fp != NULL)
	{
		fprintf_s(fp, "%s %d\n", "SoundSwitch ", mSoundFlag);
		fprintf_s(fp, "%s %d\n", "BgmSwitch ", mBgmFlag);
		fprintf_s(fp, "%s %d\n", "Effect ", mEffectVol);
		fprintf_s(fp, "%s %d", "Set ", mSetVolume);
	}
	fclose(fp);
}
