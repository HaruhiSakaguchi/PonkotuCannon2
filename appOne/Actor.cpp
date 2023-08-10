#include "Actor.h"
#include "Game.h"
#include "Component.h"
#include "Map.h"
#include "Items.h"
#include <sstream>

Actor::Actor(Game* game)
	: mGame(game)
	, mPosition(0.0f, 0.0f, 0.0f)
	, mRotation(0.0f, 0.0f, 0.0f)
	, mInitPosition(0.0f, 0.0f, 0.0f)
	, mScale(1.0f, 1.0f, 1.0f)
	, mState(State::EActive)
	, mCategory(Actor::ActorsCategory::EObject)
	, mMinPosY(-45.0f)
	, mMaxPosY(15.0f)
	, mNormalMesh(nullptr)
	, mDamageMesh(nullptr)
{
	mGame->GetActorManager()->AddActor(this);
}

Actor::~Actor()
{
	mGame->GetActorManager()->RemoveActor(this);

	while (!mComponents.empty())
	{
		delete mComponents.back();
	}
}

void Actor::ProcessInput()
{
	if (mState == State::EActive)
	{
		for (auto comp : mComponents)
		{
			comp->ProcessInput();
		}

		ActorInput();
	}
}

void Actor::Update()
{
	if (mState == State::EActive)
	{
		UpdateActor();

		for (auto component : mComponents)
		{
			component->Update();
		}
	}
}

bool Actor::PositionOnMap(const VECTOR& pos, float radius)
{
	int cnt = 0;
	if (GetGame()->GetActorManager()->GetStage())
	{
		for (int i = 0; i < mGame->GetActorManager()->GetStage()->GetAreaNum(); i++)
		{
			if ((pos.x - radius <= mGame->GetActorManager()->GetStage()->GetMaxX()[i] && pos.x + radius >= mGame->GetActorManager()->GetStage()->GetMinX()[i] && pos.z - radius <= mGame->GetActorManager()->GetStage()->GetMaxZ()[i] && pos.z + radius >= mGame->GetActorManager()->GetStage()->GetMinZ()[i]))
			{
				cnt++;
			}
		}
	}

	if (cnt != 0)
	{
		return true;
	}
	else
	{
		return false;
	}
}

void Actor::AddComponent(Component* component)
{
	// ソート済み配列の挿入場所を探す
	// (自分より順番の大きい最初の要素を探す)
	int myOrder = component->GetUpdateOrder();
	auto iter = mComponents.begin();
	for (; iter != mComponents.end(); ++iter)
	{
		if (myOrder < (*iter)->GetUpdateOrder())
		{
			break;
		}
	}

	// 探し出した要素の前に自分を挿入
	mComponents.insert(iter, component);
}

void Actor::RemoveComponent(Component* component)
{
	auto iter = std::find(mComponents.begin(), mComponents.end(), component);
	if (iter != mComponents.end())
	{
		mComponents.erase(iter);
	}
}

//アイテムを指定して、アクターのポイントからドロップ
void Actor::DropItems(int num)
{
	VECTOR pos = GetPosition();
	class ItemObject* i = nullptr;
	switch (num)
	{
	case 1:
		i = new Recovery(GetGame());
		break;
	case 2:
		i = new PowerUp(GetGame());
		break;
	case 3:
		i = new SpeedUp(GetGame());
		break;
	case 4:
		i = new RapidFire(GetGame());
		break;
	case 5:
		i = new Barrier(GetGame());
		break;
	default:
		break;
	}

	if (i != nullptr)
	{
		i->SetPosition(pos);
	}
}

//ポイントを指定してアイテムをドロップ
void Actor::DropItems(const VECTOR& pos)
{
	int num = rand() % 5;
	class ItemObject* i = nullptr;
	switch (num)
	{
	case 0:
		i = new Recovery(GetGame());
		break;
	case 1:
		i = new PowerUp(GetGame());
		break;
	case 2:
		i = new SpeedUp(GetGame());
		break;
	case 3:
		i = new RapidFire(GetGame());
		break;
	case 4:
		i = new Barrier(GetGame());
		break;
	default:
		break;
	}

	if (i != nullptr)
	{
		i->SetPosition(pos);
		std::ostringstream oss;
		oss << i->GetName() << "アイテムがドロップ。";
		GetGame()->GetActorManager()->GetStage()->GetLog()->AddText(oss.str());
	}

}

float Actor::Round(float num)
{
	return float(round(num));
}

void Actor::Sort(float* num, int left, int right)
{
	if (left >= right)
	{
		return;
	}
	float p = num[(left + right) / 2];//ピポット  leftとrightの中間地点これを区切りに配列を分割する
	int l = left, r = right; float tmp;
	while (l <= r)
	{
		while (num[l] < p) { l++; }
		while (num[r] > p) { r--; }
		if (l <= r)
		{
			tmp = num[l]; num[l] = num[r]; num[r] = tmp;
			l++; r--;
		}
	}
	Sort(num, left, r);//ピポットより左側をソート
	Sort(num, l, right);//ピポットより右側をソート
}

bool Actor::CollisionCircle(float radius1, float radius2, const VECTOR& a, const VECTOR& b)
{
	float distx = b.x - a.x;
	float disty = b.y - a.y;
	float distz = b.z - a.z;

	if (radius1 + radius2 > sqrtf(distx * distx + disty * disty + distz * distz))
	{
		return true;
	}

	return false;
}
