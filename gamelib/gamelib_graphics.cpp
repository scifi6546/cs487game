#include "pch.h"
#include <gamelib_locator.hpp>
#include <gamelib_graphics.hpp>

namespace GameLib {

    Graphics::Graphics() { context = Locator::getContext(); }

    Graphics::~Graphics() {}

    void Graphics::draw(int tileSetId, int tileId, int x, int y) {
        auto tileImage = context->getTileFast(tileSetId, tileId);
        if (!tileImage)
            return;
        context->drawTexture({ x, y },
							 { tileImage->w, tileImage->h },
							 tileImage->texture);
    }
}
