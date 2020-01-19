#include "pch.h"
#include <filesystem>
#include <gamelib.hpp>

namespace GameLib
{
	Context::Context(int width, int height, int windowFlags) {
		if (!_init()) return;
		if (!_initScreen(width, height, windowFlags)) return;
		initialized_ = true;
	}

	Context::~Context() {
		_kill();
	}

	bool Context::hadError() const {
		bool retError = hadError_;
		hadError_ = false;
		return retError;
	}

	void Context::_setError(std::string&& errorString) {
		errorString_ = std::move(errorString);
		HFLOGWARN("Error detected: %s", errorString.c_str());
		hadError_ = true;
	}

	bool Context::_init() {
		if (SDL_Init(SDL_INIT_EVERYTHING) < 0) {
			HFLOGERROR("SDL not initialized");
			return false;
		}

		if (!_initSubsystems()) {
			_setError("one or more subsystems not initialized");
		}

		keyboard.scancodes.resize(SDL_NUM_SCANCODES);

		_openGameControllers();

		return true;
	}

	bool Context::_initSubsystems() {
		bool result = true;
		int flags = IMG_INIT_JPG | IMG_INIT_PNG;
		int initFlags = IMG_Init(flags);
		if (initFlags != flags) {
			if (~initFlags & IMG_INIT_JPG) _setError("JPEG not supported");
			if (~initFlags & IMG_INIT_PNG) _setError("PNG not supported");
			result = false;
		}

		if (TTF_Init() < 0) {
			_setError("TTF support not available");
			result = false;
		}

		flags = MIX_INIT_MP3 | MIX_INIT_OGG;
		initFlags = Mix_Init(flags);
		if (initFlags != flags) {
			if (~initFlags & MIX_INIT_MP3) _setError("MP3 not supported");
			if (~initFlags & MIX_INIT_OGG) _setError("OGG not supported");
			result = false;
		}

		return result;
	}

	bool Context::_initScreen(int width, int height, int windowFlags) {
		return SDL_CreateWindowAndRenderer(width, height, windowFlags, &window_, &renderer_) == 0;
	}

	void Context::_kill() {
		_closeGameControllers();
		SDL_Quit();
	}

	void Context::_openGameControllers() {
		joystickCount = std::min<int>(MaxJoysticks, SDL_NumJoysticks());

		for (int i = 0; i < MaxJoysticks; i++) {
			JOYSTICKSTATE& j = joysticks[i];
			if (SDL_IsGameController(i)) {
				// do not open controllers already opened
				if (j.controller) continue;
				j.controller = SDL_GameControllerOpen(i);
				// reset this joystick if it wasn't opened
				if (!j.controller) {
					j = JOYSTICKSTATE();
				}
				else {
					j.name = SDL_GameControllerNameForIndex(i);
					HFLOGINFO("Joystick %i '%s' connected", i, j.name.c_str());
				}
				j.enabled = j.controller != nullptr;
			}
			else if (j.enabled) {
				HFLOGINFO("Joystick %i '%s' disconnected", i, j.name.c_str());
				SDL_GameControllerClose(j.controller);
				j = JOYSTICKSTATE();
			}
		}
	}

	void Context::_closeGameControllers() {
		for (int i = 0; i < MaxJoysticks; i++) {
			JOYSTICKSTATE& j = joysticks[i];
			if (!j.controller) continue;
			HFLOGINFO("Joystick %i '%s' closed", i, j.name.c_str());
			SDL_GameControllerClose(j.controller);
			j = JOYSTICKSTATE();
		}
	}

	void Context::_updateGameControllers() {
		for (unsigned i = 0; i < joystickCount; i++) {
			JOYSTICKSTATE& j = joysticks[i];
			if (!j.enabled) continue;
		}
	}

	int Context::getEvents() {
		static int checkForGameControllers = 100;

		if (--checkForGameControllers <= 0) {
			checkForGameControllers = 100;
			_openGameControllers();
		}

		int eventCount{ 0 };
		SDL_Event e;
		while (SDL_PollEvent(&e)) {
			switch (e.type) {
			case SDL_APP_TERMINATING:
			case SDL_QUIT:
				quitRequested = 1;
				break;
			case SDL_KEYDOWN:
				keyboard.keys[e.key.keysym.sym] = 1;
				keyboard.scancodes[e.key.keysym.scancode] = 1;
				keyboard.mod = e.key.keysym.mod;
				break;
			case SDL_KEYUP:
				keyboard.keys[e.key.keysym.sym] = 0;
				keyboard.scancodes[e.key.keysym.scancode] = 0;
				keyboard.mod = e.key.keysym.mod;
				break;
			default:
				break;
			}
			++eventCount;
		}
		return eventCount;
	}

	void Context::clearScreen(glm::u8vec4 color) {
		SDL_SetRenderDrawColor(renderer_, color.r, color.g, color.b, color.a);
		SDL_RenderClear(renderer_);
	}

	void Context::swapBuffers() { SDL_RenderPresent(renderer_); }

	void Context::addSearchPath(const std::string& path) {
		if (path.empty()) {
			searchPaths_.push_back("./");
			return;
		}

		// normalize path to use '/' characters
		std::string search_path{ path };
		for (auto& c : search_path) {
			if (c == '\\') c = '/';
		}
		if (search_path.back() != '/') search_path.push_back('/');
		// add path if it exists and is a folder?
		if (std::filesystem::is_directory(search_path)) {
			searchPaths_.push_back(search_path);
		}
		else {
			HFLOGERROR("'%s' is not a directory", search_path.c_str());
		}
	}

	void Context::clearSearchPaths() {
		searchPaths_.clear();
	}

	std::string Context::findSearchPath(const std::string& filename) const {
		std::string path;
		if (std::filesystem::is_regular_file(filename)) {
			path = filename;
		}
		else for (auto& dir : searchPaths_) {
			std::string p{ dir + filename };
			if (std::filesystem::is_regular_file(p)) {
				path = p;
				break;
			}
		}
		return path;
	}

	SDL_Surface* Context::loadImage(const std::string& filename) {
		std::filesystem::path p = findSearchPath(filename);
		if (p.empty()) return nullptr;
		std::string resourceName = std::move(p.filename().string());
		if (images_.count(resourceName)) {
			SDL_FreeSurface(images_[resourceName]);
		}
		SDL_Surface* img = IMG_Load(resourceName.c_str());
		if (!img) return nullptr;
		images_[resourceName] = img;
		return img;
	}

	void Context::freeImages() {
		for (auto& [k, v] : images_) {
			SDL_FreeSurface(v);
			v = nullptr;
		}
		images_.clear();
	}

	bool Context::imageLoaded(const std::string& resourceName) const {
		return images_.count(resourceName);
	}

	SDL_Surface* Context::getImage(const std::string& resourceName) const {
		if (images_.count(resourceName)) {
			return images_.at(resourceName);
		}
		return nullptr;
	}
}
