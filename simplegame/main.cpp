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
	while (!context.quitRequested) {
		context.getEvents();
		if (context.keyboard.scancodes[SDL_SCANCODE_ESCAPE]) {
			context.quitRequested = true;
		}

		context.clearScreen({ 255, 0, 255, 255 });
		context.drawTexture({ 50, 0 }, { 100, 100 }, testPNG);
		context.drawTexture({ 250, 250 }, { 100, 100 }, testJPG);
		context.swapBuffers();
	}

	return 0;
}
