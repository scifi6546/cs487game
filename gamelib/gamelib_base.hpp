#ifndef GAMELIB_BASE_HPP
#define GAMELIB_BASE_HPP

#define SDL_MAIN_HANDLED
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_mixer.h>
#include <SDL2/SDL_ttf.h>
#include <czmq.h>
#include <glm/glm.hpp>
#include <hatchetfish.hpp>

#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <map>
#include <string>
#include <algorithm>
#include <cmath>
#include <memory>

struct SPRITEINFO {
    glm::vec2 position;
    float angle;
    glm::vec2 center;
    int flipFlags;
};

struct TILEIMAGE {
    SDL_Texture* texture{ nullptr };
    int tileId{ 0 };
    int tilesetId{ 0 };
    int w{ 0 };
    int h{ 0 };
};

#endif