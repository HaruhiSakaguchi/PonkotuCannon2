#pragma once
#include "UIScreen.h"
#include <chrono>

class UIPlayerHome :
	public UIScreen
{
public:
	UIPlayerHome(class PlayerHome* owner);
	void draw()override;
	void Update()override;
	void DrawAfterButton()override;
	void SetGenerate(class UIGenerate* gene) { mGenerate = gene; }
	void DrawRing(const VECTOR2& pos, float radius, float sw, float angle = 1, const COLOR& color = COLOR(255, 255, 55), float angleOffset = 0);

	UIGenerate* GetGenerate() { return mGenerate; }
	struct DATA
	{
		float mHpGaugeMaxWidth = 0.0f;
		float mHpGaugeHeight = 0.0f;
		float mBarrierHpGaugeMaxWidth = 0.0f;
		float mBarrierHpGaugeHeight = 0.0f;
		float mMoveOnInterval = 0.0f;
		float mReturnInterval = 0.0f;
		float mPopUpTextSize = 0.0f;
		float mHpGaugeEdgeSw = 0.0f;
		float mIntervalGaugeRingAngleOffset = 0.0f;
		float mIntervalGaugeRingSw = 0.0f;
		float mIntervalGaugeRingRadius = 0.0f;
		float mSpecialButtonRadius = 0.0f;

		int mHomeLvUpUsePoint = 0;
		int mCanItemGenerateHomeLv = 0;
		const char* mPopUpNotMoveOnText = nullptr;
		const char* mPopUpNotReturnText = nullptr;
		const char* mMoveOnButtonText = nullptr;
		const char* mReturnButtonText = nullptr;
		const char* mMoveOnButtonGuide = nullptr;
		const char* mReturnButtonGuide = nullptr;
		const char* mGenerateUnitButtonText = nullptr;
		const char* mHomeLvUpButtonGuide = nullptr;
		const char* mGenerateItemButtonText = nullptr;
		const char* mHomeLvUpButtonText = nullptr;
		const char* mCanGenerateItemLogText = nullptr;
		const char* mPopUpFullUnitText = nullptr;
		const char* mPopUpPHomeMoveNotGenerateText = nullptr;
		const char* mPopUpPHomeGenerateNotMoveText = nullptr;
		const char* mPopUpHomeLvUpText = nullptr;
		const char* mPopUpCanGenerateItemText = nullptr;
		const char* mPopUpNotEnoughPointText = nullptr;
		const char* mPopUpNotGenerateInGenerateText = nullptr;
		const char* mPopUpNotHomeLvUpText = nullptr;
		const char* mSpecialButtonText = nullptr;
		const char* mSpecialButtonGuide = nullptr;
		const char* mPopUpCanUseSpecialText = nullptr;
		const char* mLogUseSpecialText = nullptr;
		const char* mPopUpEmemyEmptyText = nullptr;
		const char* mPopUpReleaseSpecialText = nullptr;
		const char* mPopUpGenerateSpecialText = nullptr;
		const char* mPopUpMoveSpecialText = nullptr;
		VECTOR2 mHomeMoveButtonDim;
		VECTOR2 mMoveOnButtonOffset;
		VECTOR2 mReturnButtonOffset;
		VECTOR2 mHomeLvUpButtonOffset;
		VECTOR2 mGenerateUnitButtonOffset;
		VECTOR2 mGenerateItemButtonOffset;
		VECTOR2 mUnitSizeTextPos;
		VECTOR2 mPointTextPos;
		VECTOR2 mSpecialButtonOffset;
		VECTOR2 mSpecialGuideOffset;
		COLOR mHpGaugeEdgeColor;
		COLOR mPopUpNegativeColor;
		COLOR mPopUpPositiveColor;
		COLOR mNormalColor;
		COLOR mDyingColor;
		COLOR mDangarColor;
		COLOR mHpWindowColor;
		COLOR mOverMaxHpColor;
		COLOR mBarrierHpGaugeColor;
		COLOR mIntervalGaugeRingRadiusColor;
	};
private:
	DATA Data;
	float mHpGaugeWidth;
	float mBarrierHpGaugeWidth;
	float mTime;
	float mInterval;
	float mIntervalAngle;
	int mUnitMaxNum;
	int mEnemySize;
	int mCnt;
	class PSideCharacterActor* mOwner;
	VECTOR2 mPos;
	Button* mMoveOnButton;
	Button* mReturnButton;
	Button* mHomeLvUpButton;
	Button* mGenerateUnitButton;
	Button* mGenerateItemButton;
	Button* mSpecialButton;
	class UIGenerate* mGenerate;
	std::chrono::system_clock::time_point mStart;
	bool mSpecialFlag;
	bool mSpecialEffectFlag;
	int mSpecialReleaseSound;
};

