#pragma once
#include "UIScreen.h"
#include "VECTOR.h"

class UIGenerate :
	public UIScreen
{
public:
	void draw()override;
	void Update()override;
	void CreateItemButtons();
	void CreateGenerateActorLvUpandDownButtons();
	void CreateChangeItemGenerateButtons();
	void Closed()override;
	void SetGenerateLv(int lv) { mGenerateActorLevel = lv; }
	enum class GenerateActor_Id : int
	{
		ECannon,
		EBarricade,
		EBarrier,
		EPower,
		ESpeed,
		ERapid,
		ERecover,
		EEmpty
	};
	UIGenerate(class UIPlayerHome* owner, Game* game, GenerateActor_Id id = GenerateActor_Id::EEmpty);
	struct DATA
	{
		int mItemGeneratePoint = 0;
		int mCannonGenerateBasePoint = 0;
		int mBarricadeGenerateBasePoint = 0;
		int mLvEveryUpCannonPoint = 0;
		int mLvEveryUpBarricadePoint = 0;
		float mGenerateMouseCenterDistX = 0.0f;
		float mItemButtonOffsetY = 0.0f;
		const char* mCancellText = nullptr;
		const char* mChangeItemText = nullptr;
		const char* mChangeCharacterText = nullptr;
		const char* mChangeUnitTexts[2]{ nullptr, nullptr };
		const char* mReconfirmTexts[7]{ nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr };
		const char* mPopUpSuccessText = nullptr;
		const char* mPopUpAreaOutText = nullptr;
		const char* mPopUpInEnemyAreaText = nullptr;
		const char* mItemNames[5]{ nullptr,nullptr,nullptr,nullptr,nullptr };
		const char* mItemTexts[5]{ nullptr,nullptr,nullptr,nullptr,nullptr };
		const char* mResetLvText = nullptr;
		const char* mPlusLvText = nullptr;
		const char* mMinusLvText = nullptr;
		const char* mMaxLvText = nullptr;
		const char* mPopUpLimitLvText = nullptr;
		const char* mPopUpZeroLvText = nullptr;
		VECTOR2 mCancellButtonOffset;
		VECTOR2 mUnitChangeButtonOffset;
		VECTOR2 mBPTextPos;
		VECTOR2 mGenerateReconfirmTextPos;
		VECTOR2 mLvTUButtonPosOffset;
		VECTOR2 mItemButtonInitOffset;
		VECTOR2 mChangeItemButtonOffset;
		VECTOR2 mLvPlusButtonOffset;
		VECTOR2 mLvMinusButtonOffset;
		VECTOR2 mGenerateButtonDim;
		VECTOR2 mGenerateItemButtonDim;
		VECTOR mDropUnitPositionOffset;
	};
private:
	DATA Data;
	GenerateActor_Id mId;
	VECTOR mGenePos;
	UIPlayerHome* mOwner;
	float mMouseXPerWidth;
	float mMouseYPerHeight;
	int mGenerateUsingPoints;
	class CharacterActor* mGenerateActor;
	class Button* mChangeButton;
	class Button* mCancellButton;
	class Button* mGenerateActorLvPlusButton;
	class Button* mGenerateActorLvMinusButton;
	class Button* mLvMaxButton;
	class Button* mLvResetButton;
	class MeshComponent* mMesh;
	static int mGenerateActorLevel;
};

