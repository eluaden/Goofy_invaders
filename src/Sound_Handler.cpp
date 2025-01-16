#include "Sound_Handler.h"

Mix_Chunk* Sound_Handler::player_shoot = nullptr;
Mix_Music* Sound_Handler::music = nullptr;

Sound_Handler::Sound_Handler()
{
    if(Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048) < 0)
    {
        std::cerr << "Failed to initialize SDL_mixer! SDL_Error: " << Mix_GetError() << std::endl;
    }

    load_sounds();
}

Sound_Handler::~Sound_Handler()
{
    free_sounds();
    Mix_Quit();
}

void Sound_Handler::load_sounds()
{
    player_shoot = Mix_LoadWAV("assets/sounds/player_shoot.wav");
    if(player_shoot == nullptr)
    {
        std::cerr << "Failed to load sound! SDL_Error: " << Mix_GetError() << std::endl;
    }

    music = Mix_LoadMUS("assets/music/main_music.wav");
    if(music == nullptr)
    {
        std::cerr << "Failed to load music! SDL_Error: " << Mix_GetError() << std::endl;
    }
}

void Sound_Handler::play_player_shoot()
{
    if(Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048) < 0)
    {
        std::cerr << "Failed to initialize SDL_mixer! SDL_Error: " << Mix_GetError() << std::endl;
    }

    player_shoot = Mix_LoadWAV("assets/sounds/player_shoot.wav");
    if(player_shoot == nullptr)
    {
        std::cerr << "Sound not loaded! SDL_Error: " << Mix_GetError() << std::endl;
    }


    Mix_PlayChannel(-1, player_shoot, 0);
}

void Sound_Handler::play_music()
{
    if(Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048) < 0)
    {
        std::cerr << "Failed to initialize SDL_mixer! SDL_Error: " << Mix_GetError() << std::endl;
    }

    music = Mix_LoadMUS("assets/music/main_music.wav");
    if(music == nullptr)
    {
        std::cerr << "Failed to load music! SDL_Error: " << Mix_GetError() << std::endl;
    }

    Mix_PlayMusic(music, -1);
}

void Sound_Handler::free_sounds()
{
    Mix_FreeChunk(player_shoot);
    player_shoot = nullptr;

    Mix_FreeMusic(music);
    music = nullptr;

}

