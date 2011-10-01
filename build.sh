#!/bin/bash
g++ -Wall `sdl-config --cflags` -ggdb -c -o engine.o engine_lauch.cpp -Icore/include -Ilogging/include

gcc `sdl-config --libs` -ggdb -lSDL -lGL -lstdc++ -ltinyxml -llua   -o engine_lauch  engine.o core/gamemanager.o core/scriptmanager.o logging/log_provider_file.o logging/log_system.o logging/log_provider_stdout.o