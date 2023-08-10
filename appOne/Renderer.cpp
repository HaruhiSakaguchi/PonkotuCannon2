#include "Renderer.h"
#include "Game.h"
#include "graphic.h"
#include "window.h"
#include "SpriteComponent.h"
#include "Actor.h"
#include "SHADER/LAMBERT.h"
#include "CONTAINER/CONTAINER.h"
#include "TransitionFade.h"
#include "MeshComponent.h"

Renderer::Renderer(class Game* game)
	: mGame(game)
	, mTransition(nullptr)

{
	textSize(30);
	fill(255, 255, 255);
	text("NowLoading...", 1800.0f, 1050.0f);
	Initialize();
}

Renderer::~Renderer()
{
	Shutdown();
}

bool Renderer::Initialize()
{
	Data = mGame->GetAllData()->rendererData;

	mShader = new LAMBERT;
	setRasterizerCullBack();

	mProj.pers(Data.mPerspectiveAngle, Data.mPerspectiveAspect, Data.mPerspectiveNear, Data.mPerspectiveFar);
	mTransition = new TransitionFade(mGame);

	return true;
}

void Renderer::Shutdown()
{
	delete mShader;
	delete mContainer;
	delete mTransition;
}

void Renderer::Draw()
{
	mShader->setProjView(mProj * mView);
	mShader->setLightPosition(Data.mLightPos);
	mShader->setLightAmbient(Data.mAmbient);
	mShader->setDiffuse(Data.mDiffuse);

	for (auto mesh : mMeshes)
	{
		setTextureSamplerWrap();
		if (mesh->GetOwner()->GetState() == Actor::State::EActive)
		{
			mesh->Draw();
		}
	}

	for (auto sprite : mSprites)
	{
		if (sprite->GetOwner()->GetState() == Actor::State::EActive)
		{
			sprite->Draw();
		}
	}

	for (auto ui : mGame->GetUIManager()->GetUIStack())
	{
		if (ui->GetState() == UIScreen::UIState::EActive)
		{
			ui->Draw();
		}
	}

	if (mTransition)
	{
		mTransition->Draw();
	}
}

void Renderer::AddSprite(SpriteComponent* sprite)
{
	// ƒ\[ƒgÏ‚İ”z—ñ‚Ì‘}“üêŠ‚ğ’T‚·
	// (©•ª‚æ‚è‡”Ô‚Ì‘å‚«‚¢Å‰‚Ì—v‘f‚ğ’T‚·)
	int myDrawOrder = sprite->GetDrawOrder();
	auto iter = mSprites.begin();
	for (; iter != mSprites.end(); ++iter)
	{
		if (myDrawOrder < (*iter)->GetDrawOrder())
		{
			break;
		}
	}

	// ’T‚µo‚µ‚½—v‘f‚Ì‘O‚É©•ª‚ğ‘}“ü
	mSprites.insert(iter, sprite);
}

void Renderer::RemoveSprite(SpriteComponent* sprite)
{
	// swap‚µ‚Äpop_back‚Å‚«‚È‚¢Bswap‚µ‚Ä‚µ‚Ü‚¤‚Æ‡”Ô‚ª•ö‚ê‚é‚½‚ß
	auto iter = std::find(mSprites.begin(), mSprites.end(), sprite);
	mSprites.erase(iter);
}

void Renderer::AddMesh(MeshComponent* mesh)
{
	mMeshes.emplace_back(mesh);
}

void Renderer::RemoveMesh(MeshComponent* mesh)
{
	// swap‚µ‚Äpop_back‚Å‚«‚È‚¢Bswap‚µ‚Ä‚µ‚Ü‚¤‚Æ‡”Ô‚ª•ö‚ê‚é‚½‚ß
	auto iter = std::find(mMeshes.begin(), mMeshes.end(), mesh);
	mMeshes.erase(iter);
}

bool Renderer::LoadContainer()
{
	mContainer = new CONTAINER("Assets\\Assets.txt");
	if (mContainer)
	{
		return true;
	}
	else
	{
		return false;
	}
}
