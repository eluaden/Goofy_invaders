#pragma once

#include <iostream>
#include <SDL2/SDL.h>
#include <vector>


class enemies
{
    private:
        //horde infos
        int spawn_cd_max;
        int spawn_cd;
        int spawn_chance;
        int horde_max_size;
        const int shoot_cd_max = 100;
        

        //enemy bullet infos
        
        

        //screen infos
        int SCREEN_WIDTH = 600;
        int SCREEN_HEIGHT = 800;

    public:
    
        std::vector<SDL_Rect> horde;
        std::vector<int> speed;
        std::vector<int> shoot_cd;
        std::vector<SDL_Rect> enemy_bullets;
        std::vector<float> enemy_bullets_y;
        std::vector<float> bullets_speed;
        std::vector<int> bullets_size;

        enemies(int size, int cd, int chance);
        ~enemies();
    


        //actions
        void spawn();
        void update(std::vector<SDL_Rect>& bullets, std::vector<float>& bullets_y, int*  kills);	
};