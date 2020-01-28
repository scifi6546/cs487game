#ifndef GAMELIB_GRAPHICS_HPP
#define GAMELIB_GRAPHICS_HPP

namespace GameLib {
    class IGraphics {
    public:
        virtual ~IGraphics() {}

        virtual void draw(int tileSetId, int tileId, int x, int y) {}
    };

    class Graphics : public IGraphics {
    public:
        Graphics();
        virtual ~Graphics();

        void draw(int tileSetId, int tileId, int x, int y) override;

    private:
        Context* context{ nullptr };
    };
}

#endif
