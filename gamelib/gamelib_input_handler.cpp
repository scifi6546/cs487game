#include "pch.h"
#include <gamelib_locator.hpp>
#include <gamelib_input_handler.hpp>

#define CHECKPOINTER(button)                                                                                                                                   \
    if (!button)                                                                                                                                               \
        button = &nullCommand;
#define CHECKSCANCODE(x, command)                                                                                                                              \
    if (context->keyboard.scancodes[SDL_SCANCODE_##x]) {                                                                                                       \
        command;                                                                                                                                               \
    }
#define HANDLESCANCODE(x, command)                                                                                                                             \
    if (context->keyboard.scancodes[SDL_SCANCODE_##x]) {                                                                                                       \
        bool result = command;                                                                                                                                 \
        if (result)                                                                                                                                            \
            context->keyboard.scancodes[SDL_SCANCODE_##x] = 0;                                                                                                 \
    }

namespace GameLib {
    void InputHandler::handle() {
        Context* context = Locator::getContext();
        _checkPointers();
        const float ONE = 1.0f;
        HANDLESCANCODE(W, dpadPosY->execute(ONE));
        HANDLESCANCODE(S, dpadNegY->execute(ONE));
        HANDLESCANCODE(A, dpadNegX->execute(ONE));
        HANDLESCANCODE(D, dpadPosX->execute(ONE));
        HANDLESCANCODE(ESCAPE, back->execute(ONE));
        HANDLESCANCODE(RETURN, start->execute(ONE));
        HANDLESCANCODE(SPACE, buttonA->execute(ONE));
        glm::vec3 axis1{ 0.0f, 0.0f, 0.0f };
        HANDLESCANCODE(LEFT, axis1.x -= 1);
        HANDLESCANCODE(RIGHT, axis1.x += 1);
        HANDLESCANCODE(UP, axis1.y -= 1);
        HANDLESCANCODE(DOWN, axis1.y += 1);
        axis1X->execute(axis1.x);
        axis1Y->execute(axis1.y);

		HANDLESCANCODE(1, key1->execute(ONE));
        HANDLESCANCODE(2, key2->execute(ONE));
        HANDLESCANCODE(3, key3->execute(ONE));
        HANDLESCANCODE(4, key4->execute(ONE));
        HANDLESCANCODE(5, key5->execute(ONE));
        HANDLESCANCODE(6, key6->execute(ONE));
        HANDLESCANCODE(7, key7->execute(ONE));
        HANDLESCANCODE(8, key8->execute(ONE));
        HANDLESCANCODE(9, key9->execute(ONE));
        HANDLESCANCODE(0, key0->execute(ONE));
    }

    void InputHandler::_checkPointers() {
        CHECKPOINTER(axis1X);
        CHECKPOINTER(axis1Y);
        CHECKPOINTER(axis1Z);
        CHECKPOINTER(axis2X);
        CHECKPOINTER(axis2Y);
        CHECKPOINTER(axis2Z);
        CHECKPOINTER(buttonX);
        CHECKPOINTER(buttonY);
        CHECKPOINTER(buttonA);
        CHECKPOINTER(buttonB);
        CHECKPOINTER(dpadNegX);
        CHECKPOINTER(dpadPosX);
        CHECKPOINTER(dpadNegY);
        CHECKPOINTER(dpadPosY);
        CHECKPOINTER(shoulderL1);
        CHECKPOINTER(shoulderL2);
        CHECKPOINTER(shoulderR1);
        CHECKPOINTER(shoulderR2);
        CHECKPOINTER(start);
        CHECKPOINTER(back);
        CHECKPOINTER(home);
    }
}
