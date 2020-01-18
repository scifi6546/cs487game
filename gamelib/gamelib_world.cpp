#include "pch.h"
#include "gamelib_world.hpp"

namespace GameLib
{
	World::World():
		tiles(WorldSizeX * WorldSizeY) {}

	World::~World() {
		tiles.clear();
		actors.clear();
	}

	void World::setTile(unsigned x, unsigned y, Actor::shared_ptr ptr) {
		if (x >= WorldSizeX || y >= WorldSizeY) return;
		tiles[y * WorldSizeX + x] = std::move(ptr);
	}

	Actor::shared_ptr World::getTile(unsigned x, unsigned y) {
		if (x >= WorldSizeX || y >= WorldSizeY) return Actor::shared_ptr();
		return tiles[y * WorldSizeX + x];
	}

	std::istream& World::readCharStream(std::istream& s) {
		std::string cmd;
		s >> cmd;
		if (cmd == "row") {
			// TODO: row should be followed by characters representing background tiles
		}
		return s;
	}

	std::ostream& World::writeCharStream(std::ostream& s) const {
		// TODO: rows should be written out with characters representing background tiles
		// Main Idea is to use a command with parameters
		// Example:
		// # tile is used to remap a character to a sprite index
		// tile # 34
		// tile A 35
		// # actor define type char NAME
		// # actor text TEXT
		// actor define NPC a "Justine Shellock"
		// actor state BossAlive
		// actor text "Howdy, how are you?"
		// actor text "Have you heard about the monolith?"
		// actor state BossDead
		// actor text "Oh thank you! Now I can go back to carpentry!"
		// actor define NPC b "Samson Hallock"
		// actor state BossAlive
		// actor text "It arrived at midnight the day before"
		// actor text "It makes us sad, can you destroy it?"
		// actor state BossDead
		// actor text "The Monolith is dead. We can not be at peace."
		// actor state BossDead
		// actor define BOSS B "Monolith"
		// actor state BossAlive
		// actor text "What? You think you can destroy me?!"
		// actor text "Ha! Ha! Ha! Do your worst!"
		// actor state BossDead
		// actor text "Oh no! What a world!"
		// # world N ... is the information for row N
		// # the space character is the value 0, or no tile
		// # the < character is the player start position
		// # the > character is the player end position
		// world 0 #######################
		// world 1 #      a              #
		// world 2 #  AAAAA     b        #
		// world 3 #<     #  AAAA     B >#
		// world 4 #######################
		return s;
	}
}
