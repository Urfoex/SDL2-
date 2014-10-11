#!/bin/sh
g++ -std=c++14 `sdl2-config --cflags --libs` -lSDL2 main.cpp
