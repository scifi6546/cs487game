cmake_minimum_required(VERSION 3.13)
project(gamelib)
include_directories(${PROJECT_SOURCE_DIR})

add_library(gamelib STATIC
    gamelib.cpp
    gamelib_context.cpp
    gamelib_object.cpp
    gamelib_actor.cpp
    gamelib_world.cpp
    hatchetfish_log.cpp
    hatchetfish_stopwatch.cpp
    )

install(TARGETS gamelib DESTINATION lib)
#[[install(TARGETS
    ./gamelib.hpp
    ./gamelib_base.hpp
    ./gamelib_object.hpp
    ./gamelib_actor.hpp
    ./gamelib_world.hpp
    DESTINATION include)
]]
