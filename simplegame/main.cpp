// Simple Game
// by Dr. Jonathan Metzgar et al
// UAF CS Game Design and Architecture Course
#include <gamelib.hpp>

#pragma comment(lib, "gamelib.lib")

int main(int argc, char** argv) {
	GameLib::Context context(1000, 600, GameLib::WindowFullscreen);

	while (!context.quitRequested) {
		context.getEvents();
		if (context.keyboard.scancodes[SDL_SCANCODE_ESCAPE]) {
			context.quitRequested = true;
		}

		context.clearScreen({ 255, 0, 255, 255 });
		context.swapBuffers();
	}

	return 0;
}
