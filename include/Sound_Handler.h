#include <iostream>
#include <SDL2/SDL.h>
#include <SDL2/SDL_mixer.h>

class Sound_Handler
{
    private:
        
    public:
        static Mix_Chunk* player_shoot;

    
        Sound_Handler();
        ~Sound_Handler();

        void load_sounds();
        static void play_player_shoot();
        void free_sounds();
};