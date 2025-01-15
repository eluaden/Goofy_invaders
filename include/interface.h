#pragma once

#include <iostream>
#include <vector>
#include <SDL2/SDL.h>
#include "enemies.h"
#include "player.h"


class Interface_Handler
{
    private:

    

        int SCREEN_WIDTH = 600;
        int SCREEN_HEIGHT = 800;
    public:
        //infos tela
        std::vector<SDL_Rect> life_rects;

        Interface_Handler(int life);
        ~Interface_Handler();

        void update(int life);
        void level_up(SDL_Renderer* renderer, int level);
        void Game_Over(SDL_Renderer* renderer, enemies* horde, player* player_1, bool* running);
};

