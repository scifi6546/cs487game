#ifndef GAMELIB_CONTEXT_HPP
#define GAMELIB_CONTEXT_HPP

#include <gamelib_base.hpp>

namespace GameLib
{
	constexpr int WindowFullscreen = SDL_WINDOW_FULLSCREEN_DESKTOP;
	constexpr int WindowBorderless = SDL_WINDOW_BORDERLESS;
	constexpr int WindowResizeable = SDL_WINDOW_RESIZABLE;
	constexpr int WindowOpenGL = SDL_WINDOW_OPENGL;

	class Context {
	public:
		Context(int width, int height, int flags = WindowResizeable);
		~Context();

		operator bool() const { return initialized_; }
		bool hadError() const;
		const std::string errorString() const { return errorString_; }

		int getEvents();
		void clearScreen(glm::u8vec4 color);
		void swapBuffers();

		int quitRequested{ 0 };

		struct KEYBOARDSTATE {
			std::vector<int> scancodes;
			std::map<int, int> keys;
			int mod{ 0 };
		} keyboard;
	private:
		bool _init();
		bool _initSubsystems();
		bool _initScreen(int width, int height, int windowFlags);
		void _kill();
		void _setError(std::string&& errorString);
		bool initialized_{ false };
		mutable bool hadError_{ false };
		std::string errorString_;

		SDL_Window* window_{ nullptr };
		SDL_Renderer* renderer_{ nullptr };
	};
}

#endif