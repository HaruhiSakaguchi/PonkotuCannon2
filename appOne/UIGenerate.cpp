#include "UIGenerate.h"
#include "PlayerHome.h"
#include "Game.h"
#include "input.h"
#include "Cannon.h"
#include "UIPlayerHome.h"
#include "Barricade.h"
#include "TreeMeshComponent.h"
#include "CannonWheelL.h"
#include "CannonWheelR.h"
#include "UIPopUp.h"
#include "Items.h"
#include "EnemyHome.h"
#include "Map.h"

int UIGenerate::mGenerateActorLevel = 0;

UIGenerate::UIGenerate(class UIPlayerHome* owner, Game* game, GenerateActor_Id id)
	: UIScreen(game)
	, mGenePos(0.0f, 0.0f, -27.0f)
	, mMouseXPerWidth(0.0f)
	, mMouseYPerHeight(0.0f)
	, mOwner(owner)
	, mId(id)
	, mGenerateUsingPoints(0)
	, mGenerateActor(nullptr)
	, mChangeButton(nullptr)
	, mCancellButton(nullptr)
	, mGenerateActorLvPlusButton(nullptr)
	, mGenerateActorLvMinusButton(nullptr)
	, mLvMaxButton(nullptr)
	, mLvResetButton(nullptr)
{
	Data = mGame->GetAllData()->uiGenerateData;

	mCancellButton = AddRectButton(Data.mCancellText,
		[this]()
		{
			mGame->GetActorManager()->GetPHome()->SetGenerateFlag(false);
			CloseMe();
			mOwner->SetGenerate(nullptr);
			mGame->GetCameraManager()->ChangeCamera("NormalCamera");

			for (auto button : mOwner->GetButtons())
			{
				button->SetState(Button::ButtonState::EEnable);
			}
			for (auto uiStatus : mGame->GetUIManager()->GetUIPSideStatus())
			{
				for (auto button : uiStatus->GetButtons())
				{
					button->SetState(Button::ButtonState::EEnable);
				}
			}
		}
	);

	mCancellButton->SetPosition(mCancellButton->GetPosition() + Data.mCancellButtonOffset);
	mCancellButton->ChangeCancellSound();

	if ((int)mId <= (int)GenerateActor_Id::EBarricade)
	{
		mChangeButton = AddRectButton(Data.mChangeUnitTexts[(int)mId],
			[this]()
			{
				int id = ((int)mId + 1) % 2;
				auto ui = new UIGenerate(mOwner, mGame, static_cast<UIGenerate::GenerateActor_Id>(id));
				CloseMe();
				mOwner->SetGenerate(ui);
			}
			,
				nullptr, Data.mGenerateButtonDim
		);

		mChangeButton->SetPosition(mCancellButton->GetPosition() + Data.mUnitChangeButtonOffset);
	}

	for (auto button : mOwner->GetButtons())
	{
		button->SetState(Button::ButtonState::EDisable);
	}

	for (auto uiStatus : mGame->GetUIManager()->GetUIPSideStatus())
	{
		for (auto button : uiStatus->GetButtons())
		{
			button->SetState(Button::ButtonState::EDraw_Enable);
		}
	}

	mGenerateActor = new CharacterActor(mGame);
	mMesh = new TreeMeshComponent(mGenerateActor);

	auto tree = static_cast<class TreeMeshComponent*>(mMesh);

	if (mId == GenerateActor_Id::ECannon)
	{
		tree->SetTree("CannonBarrel");
		new CannonWheelL(static_cast<class Cannon*>(mGenerateActor));
		new CannonWheelR(static_cast<class Cannon*>(mGenerateActor));
		mGenerateActor->SetRotationY(3.1415926f);
		CreateChangeItemGenerateButtons();
		CreateGenerateActorLvUpandDownButtons();

	}
	else if (mId == GenerateActor_Id::EBarricade)
	{
		tree->SetTree("Barricade");
		CreateChangeItemGenerateButtons();
		CreateGenerateActorLvUpandDownButtons();
	}
	else if ((int)GenerateActor_Id::EBarricade < (int)mId && (int)mId < (int)GenerateActor_Id::EEmpty)
	{
		CreateItemButtons();

		tree->SetTree(Data.mItemNames[(int)mId - 2]);
		mGenerateActor->SetCategory(CharacterActor::ActorsCategory::EItem);
		auto ChangeItemButton = AddRectButton(Data.mChangeCharacterText,
			[this]()
			{
				auto ui = new UIGenerate(mOwner, mGame, UIGenerate::GenerateActor_Id::ECannon);
				CloseMe();
				mOwner->SetGenerate(ui);
			}
			,
				nullptr, Data.mGenerateButtonDim);
		ChangeItemButton->SetPosition(mCancellButton->GetPosition() + Data.mChangeItemButtonOffset);
	}
	else
	{
		mGenerateActor->SetState(CharacterActor::State::EDead);
	}

	mOwner->SetGenerate(this);

	mGame->GetCameraManager()->ChangeCamera("LookCenterCamera");

	if (mGame->GetActorManager()->GetPHome() && mGame->GetActorManager()->GetPHome()->GetLevel() < mGenerateActorLevel)
	{
		mGenerateActorLevel = 0;
	}
}


void UIGenerate::draw()
{
	textSize(mGame->GetAllData()->uiPHomeData.mPopUpTextSize);
	fill(0, 0, 0);
	if (mGame->GetActorManager()->GetPHome())
	{
		text((let)mGame->GetActorManager()->GetPHome()->GetBattlePoints() + " / " + (let)mGame->GetActorManager()->GetPHome()->GetMaxBattlePoints(), Data.mBPTextPos.x, Data.mBPTextPos.y);
	}

	if (mId != GenerateActor_Id::EEmpty)
	{
		text((let)Data.mReconfirmTexts[(int)(mId)] + (let)mGenerateUsingPoints + "ポイント消費", Data.mGenerateReconfirmTextPos.x, Data.mGenerateReconfirmTextPos.y);
	}
	if (mGenerateActorLvPlusButton && mGenerateActorLvMinusButton)
	{
		text(mGenerateActorLevel, mGenerateActorLvPlusButton->GetPosition().x + (mGenerateActorLvMinusButton->GetPosition().x - mGenerateActorLvPlusButton->GetPosition().x) / 2.0f - mGame->GetAllData()->uiPHomeData.mPopUpTextSize / 4.0f, mGenerateActorLvPlusButton->GetPosition().y + mGame->GetAllData()->uiPHomeData.mPopUpTextSize / 2.0f);
	}
}

void UIGenerate::Update()
{
	if (mGame->GetActorManager()->GetPHome())
	{
		mMouseXPerWidth = (width / 2.0f - mouseX) / -Data.mGenerateMouseCenterDistX / 2.0f;
		mMouseYPerHeight = (height / 2.0f - mouseY) / -height / 2;

		mGenePos.x = mMouseXPerWidth * 4.0f * mGame->GetActorManager()->GetStage()->GetStageMaxX();
		mGenePos.z = mMouseYPerHeight * 4.0f * -((mGame->GetActorManager()->GetStage()->GetStageMinZ() + 3.0f) + -(mGame->GetActorManager()->GetStage()->GetStageMaxZ() - 3.0f)) / 2.0f + mGame->GetActorManager()->GetStage()->GetCenterPos().z;

		VECTOR2 mousePos = VECTOR2(mouseX, mouseY);

		bool inMapArea = true;

		if (width / 2.0f - Data.mGenerateMouseCenterDistX / 2.0f <= mousePos.x && mousePos.x <= width / 2.0f + Data.mGenerateMouseCenterDistX / 2.0f)
		{
			mMesh->SetDrawFlag(true);
			mGenerateActor->SetDamageInterval(0.0f);
		}
		else
		{
			mMesh->SetDrawFlag(false);
			mGenerateActor->SetDamageInterval(1.0f);
			inMapArea = false;
		}

		if (mId != GenerateActor_Id::EEmpty)
		{
			if (mId == GenerateActor_Id::ECannon)
			{
				mGenerateUsingPoints = mGenerateActorLevel * Data.mLvEveryUpCannonPoint + Data.mCannonGenerateBasePoint;
			}
			else if (mId == GenerateActor_Id::EBarricade)
			{
				mGenerateUsingPoints = mGenerateActorLevel * Data.mLvEveryUpBarricadePoint + Data.mBarricadeGenerateBasePoint;
			}
			else if (mId != GenerateActor_Id::EEmpty)
			{
				mGenerateUsingPoints = Data.mItemGeneratePoint;
			}
		}

		if (mGenerateActor)
		{
			mGenerateActor->SetPosition(mGenePos);
		}

		bool contains = false;

		for (auto button : GetButtons())
		{
			if (button->ContainsPoint(mousePos))
			{
				contains = true;
				break;
			}
		}

		if (isTrigger(MOUSE_LBUTTON) && !contains)
		{
			if (inMapArea)
			{
				if (!mGame->GetActorManager()->GetEHome() || (mGame->GetActorManager()->GetEHome() && !mGame->GetActorManager()->GetEHome()->InEnemyArea(mGenePos)))
				{
					if (mGenerateUsingPoints <= mGame->GetActorManager()->GetPHome()->GetBattlePoints())
					{
						if (mId != GenerateActor_Id::EEmpty)
						{
							CharacterActor* c = nullptr;
							if (mId == GenerateActor_Id::ECannon && ((int)(mGame->GetActorManager()->GetPSide().size()) - 1) <= mGame->GetActorManager()->GetPHome()->GetLevel())
							{
								c = new class Cannon(mGame);
								if (mGame->GetActorManager()->GetPHome()->GetFirstGenerateCannonFlag() == 0)
								{
									mGame->GetActorManager()->GetPHome()->SetFirstGenerateCannonFlag(1);
									static_cast<Cannon*>(c)->SetCNum(0);
								}
								c->SetLevel(mGenerateActorLevel);
								c->SetUp();
								c->SetPosition(mGame->GetActorManager()->GetPHome()->GetPosition());
								c->GetGame()->GetActorManager()->GetPHome()->GetDore()->Open();
							}
							else if (mId == GenerateActor_Id::EBarricade && ((int)(mGame->GetActorManager()->GetPSide().size()) - 1) <= mGame->GetActorManager()->GetPHome()->GetLevel())
							{
								c = new class Barricade(mGame);
								if (mGame->GetActorManager()->GetPHome()->GetFirstGenerateBarricadeFlag() == 0)
								{
									mGame->GetActorManager()->GetPHome()->SetFirstGenerateBarricadeFlag(1);
									static_cast<Barricade*>(c)->SetBNum(0);
								}
								c->SetLevel(mGenerateActorLevel);
								c->SetUp();
								c->SetPosition(mGenePos + Data.mDropUnitPositionOffset);
							}
							else if (GenerateActor_Id::EBarricade < mId)
							{
								switch (mId)
								{
								case GenerateActor_Id::EBarrier:
									c = new class Barrier(mGame);
									break;
								case GenerateActor_Id::EPower:
									c = new class PowerUp(mGame);
									break;
								case GenerateActor_Id::ESpeed:
									c = new class SpeedUp(mGame);
									break;
								case GenerateActor_Id::ERapid:
									c = new class RapidFire(mGame);
									break;
								case GenerateActor_Id::ERecover:
									c = new class Recovery(mGame);
									break;
								default:
									CloseMe();
									break;
								}
								c->SetPosition(mGenePos + Data.mDropUnitPositionOffset);
								std::ostringstream oss;
								oss << c->GetName().c_str() << "アイテムを設置。";
								mGame->GetActorManager()->GetStage()->GetLog()->AddText(oss.str());
								mGame->GetActorManager()->GetPHome()->SetGenerateFlag(false);
							}

							c->SetInitPosition(mGenePos);
							c->SetMaxHp((int)(c->GetInitMaxHp() * ((c->GetLevel() + c->GetMaxLevel()) / 10.0f)));
							c->SetHp(c->GetMaxHp());
							mGame->GetActorManager()->GetPHome()->SetBattlePoints(mGame->GetActorManager()->GetPHome()->GetBattlePoints() - mGenerateUsingPoints);

						}

						if (mId == GenerateActor_Id::ECannon)
						{
							mGame->GetCameraManager()->ChangeCamera("PHomeCamera");
						}
						else
						{
							mGame->GetActorManager()->GetPHome()->SetGenerateFlag(0);
							mGame->GetCameraManager()->ChangeCamera("NormalCamera");
						}

						for (auto button : mOwner->GetButtons())
						{
							button->SetState(Button::ButtonState::EEnable);
						}

						for (auto uiStatus : mGame->GetUIManager()->GetUIPSideStatus())
						{
							for (auto button : uiStatus->GetButtons())
							{
								button->SetState(Button::ButtonState::EEnable);
							}
						}

						CloseMe();
						mOwner->SetGenerate(nullptr);
						auto pop = new UIPopUp(mGame, Data.mPopUpSuccessText, mousePos, 1, VECTOR2(0.0f, -1.0f));
						pop->SetTextSize(mGame->GetAllData()->uiPHomeData.mPopUpTextSize);
						pop->SetTextColor(mGame->GetAllData()->uiPHomeData.mPopUpPositiveColor);
						pop->NoStrokeRect();
					}
					else
					{
						auto pop = new UIPopUp(mGame, mGame->GetAllData()->uiPHomeData.mPopUpNotEnoughPointText, mousePos, 1, VECTOR2(0.0f, -1.0f));
						pop->SetTextSize(mGame->GetAllData()->uiPHomeData.mPopUpTextSize);
						pop->SetTextColor(mGame->GetAllData()->uiPHomeData.mPopUpNegativeColor);
						pop->NoStrokeRect();
					}
				}
				else
				{
					auto pop = new UIPopUp(mGame, Data.mPopUpInEnemyAreaText, mousePos, 1, VECTOR2(0.0f, -1.0f));
					pop->SetTextSize(mGame->GetAllData()->uiPHomeData.mPopUpTextSize);
					pop->SetTextColor(mGame->GetAllData()->uiPHomeData.mPopUpNegativeColor);
					pop->NoStrokeRect();
				}
			}
			else
			{
				auto pop = new UIPopUp(mGame, Data.mPopUpAreaOutText, mousePos, 1, VECTOR2(0.0f, -1.0f));
				pop->SetTextSize(mGame->GetAllData()->uiPHomeData.mPopUpTextSize);
				pop->SetTextColor(mGame->GetAllData()->uiPHomeData.mPopUpNegativeColor);
				pop->NoStrokeRect();
			}
		}

	}
	else
	{
		CloseMe();
		mOwner->SetGenerate(nullptr);
	}
}

void UIGenerate::CreateItemButtons()
{
	VECTOR2 pos = mCancellButton->GetPosition() + Data.mItemButtonInitOffset;
	int buttonNum = 0;
	for (int i = 2; i < 7; i++)
	{
		buttonNum = i;

		if (mId == static_cast<GenerateActor_Id>(i))
		{
			continue;
		}

		auto button = AddRectButton(Data.mItemNames[i - 2],
			[this, buttonNum]()
			{
				auto ui = new UIGenerate(mOwner, mGame, (static_cast<GenerateActor_Id>(buttonNum)));
				CloseMe();
				mOwner->SetGenerate(ui);
			}
			, Data.mItemTexts[i - 2]
				, Data.mGenerateItemButtonDim
				);

		pos.y += Data.mItemButtonOffsetY;
		button->SetPosition(pos);
	}
}

void UIGenerate::CreateGenerateActorLvUpandDownButtons()
{
	mGenerateActorLvPlusButton = AddRectButton(Data.mPlusLvText,
		[this]()
		{
			if (mGenerateActorLevel < mGame->GetActorManager()->GetPHome()->GetLevel())
			{
				mGenerateActorLevel++;
			}
			else
			{
				auto pop = new UIPopUp(mGame, Data.mPopUpLimitLvText, mGenerateActorLvPlusButton->GetPosition(), 1, VECTOR2(0.0f, -1.0f));
				pop->SetTextSize(mGame->GetAllData()->uiPHomeData.mPopUpTextSize);
				pop->SetTextColor(mGame->GetAllData()->uiPHomeData.mPopUpNegativeColor);
				pop->NoStrokeRect();
			}
		}
	);

	mGenerateActorLvPlusButton->SetPosition(mChangeButton->GetPosition() + Data.mLvPlusButtonOffset);

	mLvMaxButton = AddRectButton(Data.mMaxLvText,
		[this]()
		{
			mGenerateActorLevel = mGame->GetActorManager()->GetPHome()->GetLevel();
		}
	);

	mLvMaxButton->SetPosition(mGenerateActorLvPlusButton->GetPosition() - Data.mLvTUButtonPosOffset);

	mGenerateActorLvMinusButton = AddRectButton(Data.mMinusLvText,
		[this]()
		{
			if (mGenerateActorLevel > 0)
			{
				mGenerateActorLevel--;
			}
			else
			{
				auto pop = new UIPopUp(mGame, Data.mPopUpZeroLvText, mGenerateActorLvMinusButton->GetPosition(), 1, VECTOR2(0.0f, -1.0f));
				pop->SetTextSize(mGame->GetAllData()->uiPHomeData.mPopUpTextSize);
				pop->SetTextColor(mGame->GetAllData()->uiPHomeData.mPopUpNegativeColor);
				pop->NoStrokeRect();
			}
		}

	);

	mGenerateActorLvMinusButton->SetPosition(mChangeButton->GetPosition() + Data.mLvMinusButtonOffset);


	mLvResetButton = AddRectButton(Data.mResetLvText,
		[this]()
		{
			mGenerateActorLevel = 0;
		}
	);

	mLvResetButton->SetPosition(mGenerateActorLvMinusButton->GetPosition() + Data.mLvTUButtonPosOffset);
}

void UIGenerate::CreateChangeItemGenerateButtons()
{
	if (mGame->GetActorManager()->GetPHome()->GetLevel() >= mGame->GetAllData()->uiPHomeData.mCanItemGenerateHomeLv)
	{
		auto ChangeItemButton = AddRectButton(Data.mChangeItemText,
			[this]()
			{
				auto ui = new UIGenerate(mOwner, mGame, UIGenerate::GenerateActor_Id::EBarrier);
				CloseMe();
				mOwner->SetGenerate(ui);
			});
		ChangeItemButton->SetPosition(mCancellButton->GetPosition() + Data.mChangeItemButtonOffset);
	}
}

void UIGenerate::Closed()
{
	mGenerateActor->SetState(Actor::State::EDead);
}
