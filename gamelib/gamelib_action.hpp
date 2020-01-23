#ifndef GAMELIB_ACTION_HPP
#define GAMELIB_ACTION_HPP

#include <gamelib_base.hpp>

namespace GameLib {
    class Action {
    public:
        virtual ~Action() {}
    protected:
        virtual void act() = 0;

		// define member variables here
        void move(glm::vec3 position);
	};
}

#endif
