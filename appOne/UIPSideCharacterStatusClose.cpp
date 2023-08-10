#include "UIPSideCharacterStatusClose.h"
#include "Game.h"
#include "graphic.h"
#include "UIPSideCharacterStatus.h"
#include "PlayerHome.h"

UIPSideCharacterStatusClose::UIPSideCharacterStatusClose(class CharacterActor* owner)
	: UIPSideCharacterStatusBase(static_cast<PSideCharacterActor*>(owner))
	, mOpenButtun(nullptr)
{
	mPosition = VECTOR2(0.0f, (mGame->GetAllData()->itemEffectData.mUIOffsetPosY * 1.5f)) +
		Data.mUIInitPos;

	if (mOwner->GetTag() == CharacterActor::CharactersTag::ECannon)
	{
		mOpenButtun = AddRectButton(Data.mOpenButtonText,
			[this]() {

				CloseMe();
				new UIPSideCharacterStatus(mOwner);
			}
		);
		mOpenButtun->SetTextOffset(VECTOR2(mGame->GetAllData()->itemEffectData.mUIMinPosX - width / 2.0f + 50.0f, mGame->GetAllData()->itemEffectData.mUIOffsetPosY * 1.5f - 10.0f));
	}

	AddLvUpButton();

	mStatusState = StatusUIState::EClose;
}

void UIPSideCharacterStatusClose::draw()
{
	if (mIsDraw)
	{
		rectMode(CORNER);
		if (mOwner->GetState() == Actor::State::EActive)
		{
			float posy = mPosition.y;
			float Height = Data.mHeight / 4.0f;

			if (posy < mUITop)
			{
				Height -= mUITop - posy;
				posy = mUITop;
			}
			else if (mUIBottom < posy + Height)
			{
				Height -= posy + Height - mUIBottom;
			}

			if (mUITop < posy + Height && posy < mUIBottom)
			{
				noStroke();
				fill(Data.mUIWindowColor);
				rect(mPosition.x, posy, Data.mWidth, Height);
				DrawHpGauge(mPosition);
				DrawNameandLevel();
			}
		}
	}

}

void UIPSideCharacterStatusClose::update()
{
	if (mOwner->GetState() == Actor::State::EActive)
	{
		if (mOwner->GetTag() == CharacterActor::CharactersTag::ECannon)
		{
			mOpenButtun->SetPosition(mPosition + Data.mOpenButtonOffset);
		}

		mLvUpButton->SetPosition(mPosition + Data.mCloseLvUpButtonOffset);
	}
}
