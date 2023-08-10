#pragma once
#include "COLOR.h"
#include "Renderer.h"
#include "UIButton.h"
#include "Title.h"
#include "Quit.h"
#include "Option.h"
#include "Reconfirm.h"
#include "StageSelect.h"
#include "Pause.h"
#include "GamePlay.h"
#include "StageClear.h"
#include "GameOver.h"
#include "AllClear.h"
#include "Camera.h"
#include "Cannon.h"
#include "Items.h"
#include "PlayerBullet.h"
#include "Tama.h"
#include "TamaWeapon.h"
#include "SatelliteBullet.h"
#include "Satellite.h"
#include "SatelliteWing.h"
#include "ItemEffect.h"
#include "UIMiniMap.h"
#include "Map.h"
#include "UILog.h"
#include "UIPSideCharacterStatus.h"
#include "NormalCamera.h"
#include "LookPHomeCamera.h"
#include "LookFieldCenterCamera.h"
#include "PlayerHome.h"
#include "UIPlayerHome.h"
#include "UIGenerate.h"
#include "UIHelpBase.h"
#include "Stage.h"
#include "EnemyHome.h"
#include "Barricade.h"
#include "UIScroll.h"
#include "UILoading.h"
#include "LookEHomeCamera.h"
#include "Arrow.h"

struct Container
{
	float mWidth = 0.0f, mHeight = 0.0f;
	int mFullScreenFlag = 0;
	int mInitAllSoundVolume = 0;
	int mInitEffectSoundVolume = 0;
	COLOR mBackGroundColor = COLOR(0, 0, 0);
	COLOR mNormalDisplayColor = COLOR(0, 0, 0);
	COLOR mPauseDisplayColor = COLOR(0, 0, 0);
	struct Renderer::DATA rendererData;
	struct Button::DATA buttonData;
	struct Title::DATA titleData;
	struct Quit::DATA quitData;
	struct Option::DATA optionData;
	struct Reconfirm::DATA reconfirmData;
	struct StageSelect::DATA stageSelectData;
	struct Pause::DATA pauseData;
	struct GamePlay::DATA playData;
	struct StageClear::DATA stageClearData;
	struct GameOver::DATA overData;
	struct AllClear::DATA allClearData;
	struct Camera::DATA cameraData;
	struct Cannon::DATA cannonData;
	struct ItemObject::commonDATA itemCommonData;
	struct Recovery::individualDATA recoverData;
	struct PowerUp::individualDATA powerData;
	struct SpeedUp::individualDATA speedData;
	struct RapidFire::individualDATA rapidData;
	struct Barrier::individualDATA barrierData;
	struct RecoveryEffect::IDATA recoverEffectData;
	struct PowerUpEffect::IDATA powerEffectData;
	struct SpeedUpEffect::IDATA speedEffectData;
	struct RapidFireEffect::IDATA rapidEffectData;
	struct BarrierEffect::IDATA barrierEffectData;
	struct PlayerBullet::DATA pBulletData;
	struct PlayerBullet::IDATA pBulletIData;
	struct Tama::DATA tamaData;
	struct TamaWeapon::IDATA tWeaponIData;
	struct TamaWeapon::DATA tWeaponData;
	struct SatelliteBullet::DATA sBulletData;
	struct SatelliteBullet::IDATA sBulletIData;
	struct Satellite::DATA satelliteData;
	struct SatelliteWing::DATA sWingData;
	struct ItemEffect::CDATA itemEffectData;
	struct UIMiniMap::DATA miniMapData;
	struct Map::DATA mapData;
	struct UILog::DATA logData;
	struct UIPSideCharacterStatus::DATA psData;
	struct NormalCamera::IDATA normalCameraData;
	struct LookPHomeCamera::IDATA lookPHomeCameraData;
	struct LookFieldCenterCamera::IDATA lookCenterCameraData;
	struct PlayerHome::DATA pHomeData;
	struct UIPlayerHome::DATA uiPHomeData;
	struct UIGenerate::DATA uiGenerateData;
	struct UIHelpBase::DATA helpData;
	struct Stage::DATA stageData;
	struct EnemyHome::DATA eHomeData;
	struct Barricade::DATA barricadeData;
	struct UIScroll::DATA scrollData;
	struct UILoading::DATA loadingData;
	struct LookEHomeCamera::IDATA lookEHomeCameraData;
	struct Arrow::DATA arrowData;
	int mDeadSound = -1;
	int mFallSound = -1;
	int mDamageSound = -1;
	int mDamageSoundVolumeOffset = 0;
	int mGurdSound = -1;
	int mGurdSoundVolumeOffset = 0;
	int mCloseSound = -1;
	int mCloseSoundVolumeOffset = 0;
	int mDialog1 = -1, mDialog2 = -1;
	int mDeadSoundVolumeOffset = 0;
};

void SetAllData(struct Container& allData);
void loadGraphic(struct Container& allData);
void loadingSound(struct Container& allData);
void loadingImage(struct Container& allData);