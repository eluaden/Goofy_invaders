#pragma once

#include <iostream>
#include <SDL2/SDL.h>
#include <SDL2/SDL_mixer.h>

class Sound_Handler
{
    private:
        
    public:
        static Mix_Chunk* player_shoot;
        static Mix_Music* music;

    
        Sound_Handler();
        ~Sound_Handler();

        void load_sounds();
        static void play_player_shoot();
        static void play_music();

        void free_sounds();
};