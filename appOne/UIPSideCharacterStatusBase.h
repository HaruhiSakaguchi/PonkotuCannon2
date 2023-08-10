#pragma once
#include "UIScreen.h"
#include <sstream>
#include "COLOR.h"
#include "PSideCharacterActor.h"

class UIPSideCharacterStatusBase :
	public UIScreen
{
public:
	UIPSideCharacterStatusBase(class PSideCharacterActor* owner);
	virtual ~UIPSideCharacterStatusBase();
	class PSideCharacterActor* GetOwner() { return mOwner; }
	const VECTOR2& GetPosition() { return mPosition; }
	void SetPosition(const VECTOR2& pos) { mPosition = pos; }
	void Update()override;
	virtual void update() {};
	void DrawHpGauge(const VECTOR2& pos);
	void DrawBarrierHpGauge(const VECTOR2& pos);
	void OwnerLvUp();
	void DrawNameandLevel();
	void AddLvUpButton();

	enum class StatusUIState
	{
		EBase,
		EClose,
		EOpen
	};

	StatusUIState GetStatusState() { return mStatusState; }

	struct DATA
	{
		const char* mCloseButtonText = nullptr;
		const char* mOpenButtonText = nullptr;
		const char* mLvUpButtonText = nullptr;
		const char* mReturnHomeButtonText = nullptr;
		const char* mHomePatrollButtonText = nullptr;
		const char* mFieldPatrollButtonText = nullptr;
		const char* mStayButtonText = nullptr;
		const char* mLvUpButtonGuide = nullptr;
		const char* mReturnHomeButtonGuide = nullptr;
		const char* mHomePatrollButtonGuide = nullptr;
		const char* mFieldPatrollButtonGuide = nullptr;
		const char* mStayButtonGuide = nullptr;
		float mWidth = 0.0f;
		float mHeight = 0.0f;
		float mRadius = 0.0f;
		float mDiamiter = 0.0f;
		float mAngleOffset = 0.0f;
		float mAngle = 0.0f;//リングのアングルの一時保存用
		float mChangeAngleSpeed = 0.0f;
		float mChangeTimeSpeed = 0.0f;
		float mBarrierHpGaugeOffsetPosY = 0.0f;
		float mBarrierHpGaugeMaxWidth = 0.0f;
		float mBarrierHpGaugeHeight = 0.0f;
		float mLineSw = 0.0f;
		float mNameandLvTextSize = 0.0f;
		float mStateCursorSw = 0.0f;
		float mLaunchRingRadius = 0.0f;
		float mLaunchRingSw = 0.0f;
		float mStockItemWeight = 0.0f;
		int mMaxItemNum = 0;
		float mItemCylinderRadius = 0.0f;
		float mItemIconRadius = 0.0f;
		float mItemLvTextSize = 0.0f;
		float mWindowEdgeSw = 0.0f;
		float mItemGaugeWindowDim = 0.0f;
		float mStateCursorDim = 0.0f;
		float mHpGaugeMaxWidth = 0.0f;
		float mHpGaugeHeight = 0.0f;
		float mPopUpTextSize = 0.0f;
		float mUIOffsetPosY = 0.0f;

		COLOR mUIWindowColor;
		COLOR mTimeGaugeColor;
		COLOR mBarrierHpGaugeColor;
		COLOR mRingOnLineColor;
		COLOR mItemNameTextColor;
		COLOR mStateCursorColor;
		COLOR mWhiteRingColor;
		COLOR mGaugeRingColor;
		COLOR mItemColors[6];
		COLOR mNoItemColor;
		COLOR mOpenWindowEdgeColor;
		COLOR mWindowColor;
		COLOR mHpNormalColor;
		COLOR mHpDyingColor;
		COLOR mHpDangarColor;
		COLOR mPopUpPositiveColor;
		COLOR mPopUpNegativeColor;

		VECTOR2 mUIInitPos;
		VECTOR2 mCloseLvUpButtonOffset;
		VECTOR2 mOpenLvUpButtonOffset;
		VECTOR2 mCloseButtonOffset;
		VECTOR2 mOpenButtonOffset;
		VECTOR2 mSpeedGaugeOffset;
		VECTOR2 mPowerGaugeOffset;
		VECTOR2 mRapidGaugeOffset;
		VECTOR2 mBarrierGaugeOffset;
		VECTOR2 mStayButtonOffset;
		VECTOR2 mReturnButtonOffset;
		VECTOR2 mHomePatrollButtonOffset;
		VECTOR2 mFieldPatrollButtonOffset;
		VECTOR2 mHpGaugeOffset;
		VECTOR2 mLaunchRingOffset;
		VECTOR2 mItemGaugeWindowOffset;
		VECTOR2 mHpGaugeInitOffset;
	};
protected:
	DATA Data;
protected:
	float mHpGaugeWidth;
	float mBarrierHpGaugeWidth;
	class PSideCharacterActor* mOwner;
	enum class StatusUIState mStatusState;
	VECTOR2 mPosition;
	Button* mLvUpButton;
	bool mIsDraw;
	static float mUITop;
	static float mUIBottom;
};

