#include "pch.h"
#include "gamelib_actor.hpp"

namespace GameLib
{
	Actor::Actor() {}

	Actor::~Actor() {}

	void Actor::beginPlay() {}

	void Actor::tick(float deltaTime) {}

	void Actor::startOverlap(Object::const_weak_ptr otherObject) {}
	
	void Actor::endOverlap(Object::const_weak_ptr otherObject) {}
}