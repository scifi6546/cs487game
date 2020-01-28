#ifndef GAMELIB_COMPONENT_HPP
#define GAMELIB_COMPONENT_HPP

#include <gamelib_context.hpp>
#include <gamelib_world.hpp>

namespace GameLib {
    class InputComponent {
    public:
        virtual ~InputComponent() {}
        virtual void update(Actor& actor) = 0;
    };

    class PhysicsComponent {
    public:
        virtual ~PhysicsComponent() {}
        virtual void update(Actor& actor, World& world) = 0;
    };

    class GraphicsComponent {
    public:
        virtual ~GraphicsComponent() {}
        virtual void update(Actor& actor, Context& graphics) = 0;
    };
}

#endif // GAMELIB_COMPONENT_HPP
