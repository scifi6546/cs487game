#ifndef GAMELIB_WORLD_HPP
#define GAMELIB_WORLD_HPP

#include <gamelib_actor.hpp>

namespace GameLib
{
	// World represents a composite of Objects that live in a 2D grid world
	class World :
		public Object {
	public:
		World();
		virtual ~World();
	};
}

#endif