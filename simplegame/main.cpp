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

    context.loadAudioClip(0, "starbattle-bad.wav");
    context.loadAudioClip(1, "starbattle-dead.wav");
    context.loadAudioClip(2, "starbattle-endo.wav");
    context.loadAudioClip(3, "starbattle-exo.wav");
    context.loadAudioClip(4, "starbattle-ok.wav");
    context.loadAudioClip(5, "starbattle-pdead.wav");
    context.loadMusicClip(0, "starbattlemusic1.mp3");
    context.loadMusicClip(1, "starbattlemusic2.mp3");
    context.loadMusicClip(2, "distoro2.mid");

    GameLib::World world;
    std::string worldPath = context.findSearchPath("world.txt");
    if (!world.load(worldPath)) {
        HFLOGWARN("world.txt not found");
    }

    Hf::StopWatch stopwatch;
    double spritesDrawn = 0;
    double frames = 0;
    while (!context.quitRequested) {
        context.getEvents();
        if (context.keyboard.scancodes[SDL_SCANCODE_ESCAPE]) {
            context.quitRequested = true;
        }
        if (context.keyboard.scancodes[SDL_SCANCODE_0]) {
            context.keyboard.scancodes[SDL_SCANCODE_0] = 0;
            context.playAudioClip(0);
        }
        if (context.keyboard.scancodes[SDL_SCANCODE_1]) {
            context.keyboard.scancodes[SDL_SCANCODE_1] = 0;
            context.playAudioClip(1);
        }
        if (context.keyboard.scancodes[SDL_SCANCODE_2]) {
            context.keyboard.scancodes[SDL_SCANCODE_2] = 0;
            context.playMusicClip(0, -1, 1000);
        }
        if (context.keyboard.scancodes[SDL_SCANCODE_3]) {
            context.keyboard.scancodes[SDL_SCANCODE_3] = 0;
            context.playMusicClip(1, -1, 5000);
        }
        context.clearScreen({ 255, 0, 255, 255 });

        // An arbitrary number roughly representing 4k at 8 layers, 32x32 sprites
        //constexpr int SpritesToDraw = 128 * 72 * 8;
        // An arbitrary number roughly representing HD at 4 layers, 32x32 sprites
        constexpr int SpritesToDraw = 60 * 34 * 4;
        for (int i = 0; i < SpritesToDraw; i++) {
            GameLib::SPRITEINFO s;
            s.position = { rand() % 1280, rand() % 720 };
            s.center = { 0.0f, 0.0f };
            s.flipFlags = 0;
            s.angle = (float)(rand() % 360);
            // context.drawTexture(0, rand() % spriteCount, s);
            s.position = { rand() % 1280, rand() % 720 };
            context.drawTexture(s.position, 0, rand() % spriteCount);
        }
        spritesDrawn += SpritesToDraw;

        context.drawTexture({ 50, 0 }, { 100, 100 }, testPNG);
        context.drawTexture({ 250, 250 }, { 100, 100 }, testJPG);
        context.swapBuffers();
        frames++;
        std::this_thread::yield();
    }
    double totalTime = stopwatch.Stop_s();
    HFLOGDEBUG("Sprites/sec = %5.1f", spritesDrawn / totalTime);
    HFLOGDEBUG("Frames/sec = %5.1f", frames / totalTime);

    return 0;
}
