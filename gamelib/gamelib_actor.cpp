#include "pch.h"
#include "gamelib_actor.hpp"

namespace GameLib {
    Actor::Actor()
        : transform(1.0f)
        , addlTransform(1.0f) {}

    Actor::~Actor() {}

    void Actor::beginPlay() {}

    void Actor::update(float deltaTime) {}

    void Actor::startOverlap(const_weak_ptr otherObject) {}

    void Actor::endOverlap(const_weak_ptr otherObject) {}
}
