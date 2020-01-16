# CS 487/687 Game Engine and Game Project

## VCPKG commandline

We want to use the OpenGL Mathematics Library (GLM), SDL2, SDL2 (with JPEG support), SDL2_ttf, SDL2_mixer (with MP3 and OGG support), and CZMQ (with cURL, HTTPD, and UUID support). First install VCPKG by cloning the repository `https://github.com/Microsoft/vcpkg`. Follow the build instructions. We want to install the libraries for x64 Windows, so make sure to use the `--triplet` command. The `--recurse` option is to ensure that we update any existing packages.

     Z:\github\vcpkg> .\vcpkg install --recurse --triplet x64-windows glm sdl2 sdl2-image[libjpeg-turbo] sdl2-ttf sdl2-mixer[mpg123,libvorbis] czmq[curl,httpd,uuid]

## GameLib

### `namespace GameLib`

Every part of the game library will use the namespace `GameLib` so we can use nice short class names like `Context`.

### `Context`

This class is responsible for managing the initialization/shutdown of external libraries in addition to the screen.

### `Entity`

This class is a base class for managing any kind of game entity used in the engine. We use shallow inheritance via virtual functions to manage all the *"physical"* objects in the game world.

## SimpleGame

This program is designed to test various features of the engine. The primary goal is to make this a simple arcade game to test essential features.

## PlatformAdventure

This program is the class project. Each team member will help carve out their own unique world based on the theme "What is our story?"