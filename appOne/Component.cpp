#include "Component.h"
#include "Actor.h"

Component::Component(Actor* owner, int updateOrder)
	: mOwner(owner)
	, mUpdateOrder(updateOrder)
	, mName(nullptr)
{
	//actor‚Ìcomponent”z—ñ‚É’Ç‰Á‚·‚é
	mOwner->AddComponent(this);
}

Component::~Component()
{
	mOwner->RemoveComponent(this);
}
