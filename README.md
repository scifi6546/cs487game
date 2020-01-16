# CS 487/687 Game Engine and Game Project

## VCPKG commandline

We want to use the OpenGL Mathematics Library (GLM), SDL2, SDL2 (with JPEG support), SDL2_ttf, SDL2_mixer (with MP3 and OGG support), and CZMQ (with cURL, HTTPD, and UUID support). First install VCPKG by cloning the repository `https://github.com/Microsoft/vcpkg`. Follow the build instructions. We want to install the libraries for x64 Windows, so make sure to use the `--triplet` command. The `--recurse` option is to ensure that we update any existing packages.

     Z:\github\vcpkg> .\vcpkg install --recurse --triplet x64-windows glm sdl2 sdl2-image[libjpeg-turbo] sdl2-ttf sdl2-mixer[mpg123,libvorbis] czmq[curl,httpd,uuid]

## GameLib

## GameProject

## SimpleGame

