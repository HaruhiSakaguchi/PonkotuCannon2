#include "CharacterActor.h"
#include "Game.h"
#include "Map.h"
#include "Container.h"
#include "rand.h"
#include "MeshComponent.h"

CharacterActor::CharacterActor(Game* game)
	: Actor(game)
	, mCapsulOffset(0.0f, 0.0f, 0.0f)
	, mRadius(0.0f)
	, mHeight(0.0f)
	, mJumpFlag(0)
	, mJumpVel(0.0f)
	, mGravity(0.0f)
	, mAdvSpeed(0.0f)
	, mHp(1)
	, mMaxHp(1)
	, mSlant(44.0f)//åXéŒ
	, mDamageInterval(0.0f)
	, mOnMapFlag(true)
	, mImageColor(255, 255, 255)
	, mDamageColor(255, 0, 0, 128)
	, mLevel(0)
	, mName("Chara")
	, mTag(CharactersTag::EOthers)
	, mMaxLevel(10)
	, mInitMaxHp(1)
	, mDamage(1)
	, mOffsetY(0.5f)
	, mCapsule(nullptr)
{
	SetCategory(ActorsCategory::ECharacter);
	GetGame()->GetActorManager()->AddCharacter(this);
}

CharacterActor::~CharacterActor()
{
	GetGame()->GetActorManager()->RemoveCharacter(this);
}

void CharacterActor::Update()
{
	Actor::Update();

	if (GetState() == State::EActive)
	{
		if (GetPosition().y < mMinPosY)
		{
			SetState(State::EDead);
			FallOption();
		}

		if (GetDamageInterval() > 0.0f)
		{
			if (mNormalMesh)
			{
				mNormalMesh->SetDrawFlag(false);
			}
			if (mDamageMesh)
			{
				mDamageMesh->SetDrawFlag(true);
			}
		}
		else
		{
			if (mNormalMesh)
			{
				mNormalMesh->SetDrawFlag(true);
			}
			if (mDamageMesh)
			{
				mDamageMesh->SetDrawFlag(false);
			}
		}

		//ç°ÅAÉ}ÉbÉvÉGÉäÉAì‡Ç…Ç¢ÇÈÇ©
		mOnMapFlag = PositionOnMap(GetPosition(), GetRadius());
	}

}

int CharacterActor::rotate(VECTOR* angle, const VECTOR& dir, float rotSpeed, bool xyComplete)
{
	VECTOR b = dir;
	float angleBetweenX = -(acosf(-b.y) - 1.57f) - angle->x;
	angle->x += angleBetweenX * rotSpeed;

	//Çxé≤âÒì]Ç≥ÇπÇÈangleÇãÅÇﬂÇÈ
	VECTOR a(sinf(angle->y), 0, cosf(angle->y));
	float dotProduct = a.x * b.x + a.z * b.z;
	float crossProduct = a.x * b.z - a.z * b.x;
	float angleBetweenY = atan2f(-crossProduct, dotProduct);
	angle->y += angleBetweenY * rotSpeed;

	bool isComplete = true;

	if (xyComplete && (-0.017f >= angleBetweenX || angleBetweenX >= 0.017f))
	{
		isComplete = false;
	}

	//âÒì]èIóπ
	if ((-0.017f < angleBetweenY && angleBetweenY < 0.017f) && isComplete)
	{
		return 1;
	}
	return 0;
}

void CharacterActor::PlayDeadSound()
{
	setVolume(GetGame()->GetAllData()->mDeadSound, GetGame()->GetSoundVolumeManager()->GetEffectVolume() + GetGame()->GetAllData()->mDeadSoundVolumeOffset);
	playSound(GetGame()->GetAllData()->mDeadSound);
}

void CharacterActor::PlayFallSound()
{
	setVolume(GetGame()->GetAllData()->mFallSound, GetGame()->GetSoundVolumeManager()->GetEffectVolume());
	playSound(GetGame()->GetAllData()->mFallSound);
}

void CharacterActor::PlayDamageSound()
{
	setVolume(GetGame()->GetAllData()->mDamageSound, GetGame()->GetSoundVolumeManager()->GetEffectVolume() + GetGame()->GetAllData()->mDamageSoundVolumeOffset);
	playSound(GetGame()->GetAllData()->mDamageSound);
}

void CharacterActor::PlayGurdSound()
{
	setVolume(GetGame()->GetAllData()->mGurdSound, GetGame()->GetSoundVolumeManager()->GetEffectVolume() + GetGame()->GetAllData()->mGurdSoundVolumeOffset);
	playSound(GetGame()->GetAllData()->mGurdSound);
}

void CharacterActor::SpawnParticle(class Game* game, const VECTOR& pos, const char* name, int num, float maxLifeSpan, Particle::MeshType type, float spawnRadius)
{
	for (int i = 0; i < num; i++)
	{
		VECTOR Pos = pos;
		if (spawnRadius == 0.0f)
		{
			spawnRadius = GetRadius();
		}

		float offsetX = random(-spawnRadius * 2.0f, spawnRadius * 2.0f);
		float offsetY = random(-1.0f, 1.0f);
		float offsetZ = random(-spawnRadius * 2.0f, spawnRadius * 2.0f);

		Pos.x += offsetX;
		Pos.y += offsetY;
		Pos.z += offsetZ;

		float advSpeed = random(0.1f, 10.0f);
		float lifeSpan = random(0.1f, maxLifeSpan);
		auto particle = new Particle(game, Pos, lifeSpan);
		particle->SetMeshType(type);
		particle->SetMesh(name);
		particle->SetAdvSpeed(advSpeed);
		particle->SetRotation(VECTOR(0.17f * (int)random(0.0f, 20.0f), 0.17f * (int)random(0.0f, 20.0f), 0.17f * (int)random(0.0f, 20.0f)));
	}
}
