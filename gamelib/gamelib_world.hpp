#ifndef GAMELIB_WORLD_HPP
#define GAMELIB_WORLD_HPP

#include <gamelib_actor.hpp>

namespace GameLib {
    // number of screens in the X direction
    constexpr unsigned WorldPagesX = 4;
    // number of screens in the Y direction
    constexpr unsigned WorldPagesY = 4;

    // number of tiles on one page in the X direction
    constexpr unsigned WorldTilesX = 40;
    // number of tiles on one page in the Y direction
    constexpr unsigned WorldTilesY = 22;

    // number of tiles in the X direction
    constexpr unsigned WorldSizeX = WorldPagesX * WorldTilesX;
    // number of tiles in the Y direction
    constexpr unsigned WorldSizeY = WorldPagesY * WorldTilesY;

    // World represents a composite of Objects that live in a 2D grid world
    class World : public Object {
    public:
        World();
        virtual ~World();

        void setTile(unsigned x, unsigned y, Actor::shared_ptr ptr);
        Actor::shared_ptr getTile(unsigned x, unsigned y);

        std::istream& readCharStream(std::istream& s) override;
        std::ostream& writeCharStream(std::ostream& s) const override;

        std::vector<Actor::shared_ptr> tiles;
        std::vector<Actor::shared_ptr> actors;
    };
}

#endif
