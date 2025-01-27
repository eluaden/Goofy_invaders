#pragma once

#include <iostream>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>
#include <vector>



class Texture_Handler
{
private:   
    //screen infos
    int SCREEN_WIDTH = 600;
    int SCREEN_HEIGHT = 800;
public:
    //textures
    SDL_Texture* player_texture;
    SDL_Texture* player_bullets_texture;
    SDL_Texture* enemy_bullets_texture;
    SDL_Texture* life_texture;
    SDL_Texture* enemy_texture;
    TTF_Font* kills_font;
    std::vector<SDL_Texture*> text_textures;


    Texture_Handler(SDL_Renderer* renderer);
    ~Texture_Handler();

    static bool load_texture(SDL_Renderer* renderer, const char* path, SDL_Texture** texture);
    void draw_textures(SDL_Renderer* renderer, SDL_Rect* player_rect, std::vector<SDL_Rect>* player_bullets_rects, std::vector<SDL_Rect>* 
                        enemy_bullets_rects, std::vector<SDL_Rect>* life_rects, std::vector<SDL_Rect>* enemy_rects, int* kills, int bomb);
    static void free_texture(SDL_Texture* texture);


};




