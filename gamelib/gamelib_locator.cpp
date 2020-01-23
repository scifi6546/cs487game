#include "pch.h"
#include <gamelib_locator.hpp>

namespace GameLib {
    Context* Locator::context_{ nullptr };
    IAudio* Locator::audioService_{ nullptr };
}
