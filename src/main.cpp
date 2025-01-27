#include <SDL2/SDL.h>
#include <iostream>
#include <vector>
#include <unistd.h>

#include "player.h"
#include "enemies.h"
#include "interface.h"
#include "Texture_Handler.h"
#include "Sound_Handler.h"

const int SCREEN_WIDTH = 600;
const int SCREEN_HEIGHT = 800;
const int FPS = 60;



int main() 
{
    if(SDL_Init(SDL_INIT_VIDEO) < 0) 
    {
        std::cerr << "SDL could not initialize! SDL_Error: " << SDL_GetError() << std::endl;
        return 1;
    }

    SDL_Window* window = SDL_CreateWindow
    (
        "Goofy Game",
        SDL_WINDOWPOS_CENTERED,
        SDL_WINDOWPOS_CENTERED,
        SCREEN_WIDTH,
        SCREEN_HEIGHT,
        SDL_WINDOW_SHOWN
    );
    if(window == nullptr) 
    {
        std::cerr << "Window could not be created! SDL_Error: " << SDL_GetError() << std::endl;
        return 1;
    }

    SDL_Renderer* renderer = SDL_CreateRenderer
    (
        window,
        -1,
        SDL_RENDERER_ACCELERATED|SDL_RENDERER_PRESENTVSYNC
    );
    if(renderer == nullptr) 
    {
        std::cerr << "Renderer could not be created! SDL_Error: " << SDL_GetError() << std::endl;
        return 1;
    }

    //objects
    Interface_Handler interface(5);
    Texture_Handler textures(renderer);
    player player_1(3,(SCREEN_WIDTH/3 * 2), (SCREEN_HEIGHT/3 * 2));
    enemies horde(8, 100, 100);


    //loop principal
    bool running = true;
    SDL_Event event;
    Sound_Handler:: play_music();

    while(running) 
    {
        while(SDL_PollEvent(&event) != 0) 
        {
            if(event.type == SDL_QUIT) 
            {
                running = false;
            }
        }
        

        SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
        SDL_RenderClear(renderer);

        //interface
        interface.update(player_1.life);

        //objetos
        player_1.update(horde.enemy_bullets, horde.enemy_bullets_y);
        horde.update(player_1.bullets, player_1.bullets_y, &player_1.kills);

        // Desenhar texturas
        textures.draw_textures(renderer, &player_1.rect, &player_1.bullets, &horde.enemy_bullets, &interface.life_rects, &horde.horde, &player_1.kills, player_1.ultimate_bombs);
        SDL_RenderPresent(renderer);


        //finalização de game (game over ou level up)
        if (player_1.life <= 0)
        {
           interface.Game_Over(renderer, &horde, &player_1, &running);
           Sound_Handler::play_music();
        }
        if(player_1.kills >= interface.level_info.level_limit)
        {
            interface.level_up(renderer, &horde, &player_1, &running);
            Sound_Handler::play_music();
        }

        //FPS
        usleep(1000);
        
    }


    // Clean up
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();

    return (0);
}


