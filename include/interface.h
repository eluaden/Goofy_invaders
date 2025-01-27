#pragma once

#include <iostream>
#include <vector>
#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include "enemies.h"
#include "player.h"
#include "level_info.h"


class Interface_Handler
{
    private:
        int SCREEN_WIDTH = 600;
        int SCREEN_HEIGHT = 800;
        int level;
    public:
        LevelInfo level_info;
        //infos tela
        std::vector<SDL_Rect> life_rects;

        Interface_Handler(int life);
        ~Interface_Handler();

        void update(int life);
        void level_up(SDL_Renderer* renderer, enemies* horde, player* player_1, bool* running);
        void level_up_aux(player* player_1, enemies* horde);
        void Game_Over(SDL_Renderer* renderer, enemies* horde, player* player_1, bool* running);
        void restart(SDL_Renderer* renderer, enemies* horde, player* player_1);
        void loading_screen(SDL_Renderer* renderer);

};

