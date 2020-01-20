// Simple Game
// by Dr. Jonathan Metzgar et al
// UAF CS Game Design and Architecture Course
#include <gamelib.hpp>

#pragma comment(lib, "gamelib.lib")

int main(int argc, char** argv) {
    GameLib::Context context(1280, 720, GameLib::WindowDefault);

    context.addSearchPath("./assets");
    context.addSearchPath("../assets");
    SDL_Texture* testPNG = context.loadImage("godzilla.png");
    SDL_Texture* testJPG = context.loadImage("parrot.jpg");
    int spriteCount = context.loadTileset(0, 32, 32, "Tiles32x32.png");
    if (!spriteCount) {
        HFLOGWARN("Tileset not found");
    }
    Hf::StopWatch stopwatch;
    double spritesDrawn = 0;
    double frames = 0;
    while (!context.quitRequested) {
        context.getEvents();
        if (context.keyboard.scancodes[SDL_SCANCODE_ESCAPE]) {
            context.quitRequested = true;
        }

        context.clearScreen({ 255, 0, 255, 255 });

        // An arbitrary number roughly representing 4k at 8 layers, 32x32 sprites
        //constexpr int SpritesToDraw = 128 * 72 * 8;
        // An arbitrary number roughly representing HD at 4 layers, 32x32 sprites
        constexpr int SpritesToDraw = 60 * 34 * 4;
        for (int i = 0; i < SpritesToDraw; i++) {
            SPRITEINFO s;
            s.position = { rand() % 1280, rand() % 720 };
            s.center = { 0.0f, 0.0f };
            s.flipFlags = 0;
            s.angle = rand() % 360;
            // context.drawTexture(0, rand() % spriteCount, s);
            s.position = { rand() % 1280, rand() % 720 };
            context.drawTexture(s.position, 0, rand() % spriteCount);
        }
        spritesDrawn += SpritesToDraw;

        context.drawTexture({ 50, 0 }, { 100, 100 }, testPNG);
        context.drawTexture({ 250, 250 }, { 100, 100 }, testJPG);
        context.swapBuffers();
        frames++;
    }
    double totalTime = stopwatch.Stop_s();
    HFLOGDEBUG("Sprites/sec = %5.1f", spritesDrawn / totalTime);
    HFLOGDEBUG("Frames/sec = %5.1f", frames / totalTime);

    return 0;
}
