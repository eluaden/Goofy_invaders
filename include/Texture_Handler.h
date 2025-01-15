#pragma once

#include <iostream>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <vector>



class Texture_Handler
{
private:   
public:
    //textures
    SDL_Texture* player_texture;
    SDL_Texture* player_bullets_texture;
    SDL_Texture* enemy_bullets_texture;
    SDL_Texture* life_texture;
    SDL_Texture* enemy_texture;

    Texture_Handler(SDL_Renderer* renderer);
    ~Texture_Handler();

    static bool load_texture(SDL_Renderer* renderer, const char* path, SDL_Texture** texture);
    void draw_textures(SDL_Renderer* renderer, SDL_Rect* player_rect, std::vector<SDL_Rect>* player_bullets_rects, std::vector<SDL_Rect>* enemy_bullets_rects, std::vector<SDL_Rect>* life_rects, std::vector<SDL_Rect>* enemy_rects);
    static void free_texture(SDL_Texture* texture);


};




