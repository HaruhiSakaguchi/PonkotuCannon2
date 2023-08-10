#pragma once
#include "VECTOR.h"
#include "Map.h"
#include "UIScreen.h"

class UIMiniMap : public UIScreen
{
public:
	UIMiniMap(class Game* game, class Map* owner, bool scroll = true);
	~UIMiniMap();
	void Draw()override;
	void Update()override;
	void Create();
	void Arrow(const VECTOR2& pos = VECTOR2(0, 0), const COLOR& color = COLOR(255, 255, 255), float angle = 0);
	const VECTOR2& PosConvert2D(const VECTOR& pos);
	bool IsMiniMapCharaOnMouseCursor(const VECTOR2& pos);
	struct DATA
	{
		float mMiniHpGaugeMaxWidth = 0.0f;
		float mMiniHpGaugeHeight = 0.0f;
		float mMiniMapWindowWidth = 0.0f;
		float mMiniMapWindowHeight = 0.0f;
		float mMiniMapEdgeWidth = 0.0f;
		int mNumModels = 0;
		float mOffsetX = 0.0f;
		float mOffsetY = 0.0f;
		float mSw = 0.0f;
		float mMinPosX = 0.0f;
		float mMinPosY = 0.0f;
		float mMiniMapOffsetX = 0.0f;
		float mMiniMapOffsetY = 0.0f;
		float mMiniMapWindowLength = 0.0f;
		float mItemSw = 0.0f;
		float mWeaponSw = 0.0f;
		float mItemCircleRadius = 0.0f;
		float m3DCoordinate2DConvertRate = 0.0f;
		float mStage1OffsetX = 0.0f;
		float mStage1OffsetY = 0.0f;
		float mStage2OffsetX = 0.0f;
		float mStage2OffsetY = 0.0f;
		float mStage3OffsetX = 0.0f;
		float mHomeAreaCircleSw = 0.0f;
		float mHomeAreaDiamiter = 0.0f;
		float mHomeNameTextSize = 0.0f;
		float mCharacterNameTextSize = 0.0f;
		float mCharacterNameContainsAreaRadius = 0.0f;
		float mHomeAreaAlpha = 0.0f;
		VECTOR2 mMiniMapCornerPos;
		COLOR mItemStrokeColor;
		COLOR mArrowStrokeColor;
		COLOR mWindowColor;
		COLOR mFloorColor;
		COLOR mPlayerHomeAreaColor;
		COLOR mEnemyHomeAreaColor;
		COLOR mPlayerHomeNameColor;
		COLOR mEnemyHomeNameColor;
		COLOR mHpGaugeNormalColor;
		COLOR mHpGaugeDangerColor;
		COLOR mHpGaugeDyingColor;
		COLOR mCharacterNameTextColor;
	};
private:
	DATA Data;
private:
	class Map* mMap;
	VECTOR2* mPositions;
	float* mWidths;
	float* mHeights;
	VECTOR** mAreaPoints;
	VECTOR2 m3DConvert2DPos;
	float* mMaxX;
	float* mMaxZ;
	float* mMinX;
	float* mMinZ;
	float m0toMaxYDist;
	bool mScroll;
	bool mIsDraw;
};

