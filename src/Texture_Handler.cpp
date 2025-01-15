#include "Texture_Handler.h"

Texture_Handler::Texture_Handler(SDL_Renderer* renderer)
{
    player_texture = nullptr;
    if(!load_texture(renderer, "assets/images/nave_player.png", &player_texture)) std::cerr << "Failed to load player texture!" << std::endl;

    player_bullets_texture = nullptr;
    if(!load_texture(renderer, "assets/images/player_bullets.png", &player_bullets_texture)) std::cerr << "Failed to load player bullet texture!" << std::endl;

    enemy_bullets_texture = nullptr;
    if(!load_texture(renderer, "assets/images/enemy_bullets.png", &enemy_bullets_texture)) std::cerr << "Failed to load enemy bullet texture!" << std::endl;

    life_texture = nullptr;
    if(!load_texture(renderer, "assets/images/life_hearts.png", &life_texture)) std::cerr << "Failed to load life texture!" << std::endl;

    enemy_texture = nullptr;
    if(!load_texture(renderer, "assets/images/enemies_ships.png", &enemy_texture)) std::cerr << "Failed to load enemy texture!" << std::endl;
    
}

Texture_Handler::~Texture_Handler()
{
    free_texture(player_texture);
    free_texture(player_bullets_texture);
    free_texture(enemy_bullets_texture);
    free_texture(life_texture);
}

bool Texture_Handler::load_texture(SDL_Renderer* renderer, const char* path, SDL_Texture** texture)
{
    *texture = IMG_LoadTexture(renderer, path);
    if(texture == nullptr)
    {
        std::cerr << "Failed to load texture! SDL_Error: " << SDL_GetError() << std::endl;
        return false;
    }
    return true;
}

void Texture_Handler::draw_textures(SDL_Renderer* renderer, SDL_Rect* player_rect, std::vector<SDL_Rect>* player_bullets_rects, std::vector<SDL_Rect>* enemy_bullets_rects, std::vector<SDL_Rect>* life_rects, std::vector<SDL_Rect>* enemy_rects)
{
    SDL_RenderCopy(renderer, player_texture, NULL, player_rect);

    //draw bullets
    for(int i = 0; i < player_bullets_rects->size(); i++)
    {
        SDL_RenderCopy(renderer, player_bullets_texture, NULL, &player_bullets_rects->at(i));
    }

    for(int i = 0; i < enemy_bullets_rects->size(); i++)
    {
        SDL_RenderCopy(renderer, enemy_bullets_texture, NULL, &enemy_bullets_rects->at(i));
    }

    for(int i = 0; i < life_rects->size(); i++)
    {
        SDL_RenderCopy(renderer, life_texture, NULL, &life_rects->at(i));
    }

    for (size_t i = 0; i < enemy_rects->size(); i++)
    {
        SDL_RenderCopy(renderer, enemy_texture, NULL, &enemy_rects->at(i));
    }
    


}



void Texture_Handler::free_texture(SDL_Texture* texture)
{
    SDL_DestroyTexture(texture);
}

