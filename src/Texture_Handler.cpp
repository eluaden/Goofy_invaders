#include "Texture_Handler.h"

Texture_Handler::Texture_Handler(SDL_Renderer* renderer)
{

    if(TTF_Init() == -1)
    {
        std::cerr << "Failed to initialize TTF! SDL_Error: " << SDL_GetError() << std::endl;
    }

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

    // fontes
    kills_font = TTF_OpenFont("assets/fonts/jersey_15.ttf", 24);
    if(kills_font == nullptr)
    {
        std::cerr << "Failed to load font! SDL_Error: " << SDL_GetError() << std::endl;
    }

    //texturas de kills e loading screen
    SDL_Color color = {0, 255, 0};

    //texto de loading...
    SDL_Surface* surface_loading = TTF_RenderText_Solid(kills_font, "Loading...", color);
    if (!surface_loading)
    {
        std::cerr << "Failed to create text surface! TTF_Error: " << TTF_GetError() << std::endl;
    }
    SDL_Texture* texture_loading = SDL_CreateTextureFromSurface(renderer, surface_loading);
    

    for (int i = 0; i < 100; i++)
    {
        // Limpar tela
        SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255); // Preto
        SDL_RenderClear(renderer);

        // Criar texto de kills
        std::string text = "kills: " + std::to_string(i);
        SDL_Surface* surface = TTF_RenderText_Solid(kills_font, text.c_str(), color);
        if (!surface)
        {
            std::cerr << "Failed to create text surface! TTF_Error: " << TTF_GetError() << std::endl;
            continue;
        }
        SDL_Texture* texture = SDL_CreateTextureFromSurface(renderer, surface);
        SDL_FreeSurface(surface); // Liberar o surface após criar a textura
        if (!texture)
        {
            std::cerr << "Failed to create texture from surface! SDL_Error: " << SDL_GetError() << std::endl;
            continue;
        }

        text_textures.push_back(texture);

        // Desenhar texto de loading
        SDL_Rect text_rect = {SCREEN_WIDTH / 2 - surface_loading->w / 2, SCREEN_HEIGHT / 2 - 50, surface_loading->w, surface_loading->h};
        SDL_RenderCopy(renderer, texture_loading, NULL, &text_rect);


        // Desenhar barra de carregamento
        SDL_Rect loading_rect = {SCREEN_WIDTH / 2 - 250, SCREEN_HEIGHT / 2 - 25, 50 * (i) / 10, 50};
        SDL_SetRenderDrawColor(renderer, 0, 255, 0, 255); // Verde
        SDL_RenderFillRect(renderer, &loading_rect);

        // Atualizar a tela
        SDL_RenderPresent(renderer);

        
    }

    //liberar textura de loading
    SDL_DestroyTexture(texture_loading);
    SDL_FreeSurface(surface_loading);

}
    


Texture_Handler::~Texture_Handler()
{
    free_texture(player_texture);
    free_texture(player_bullets_texture);
    free_texture(enemy_bullets_texture);
    free_texture(life_texture);
    for(int i = 0; i < text_textures.size(); i++)
    {
        free_texture(text_textures[i]);
    }
    TTF_CloseFont(kills_font);
    TTF_Quit();

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

void Texture_Handler::draw_textures(SDL_Renderer* renderer, SDL_Rect* player_rect, std::vector<SDL_Rect>* player_bullets_rects, 
std::vector<SDL_Rect>* enemy_bullets_rects, std::vector<SDL_Rect>* life_rects, std::vector<SDL_Rect>* enemy_rects, int* kills, int bomb)
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

    //draw life
    for(int i = 0; i < life_rects->size(); i++)
    {
        SDL_RenderCopy(renderer, life_texture, NULL, &life_rects->at(i));
    }

    //draw enemies
    for (size_t i = 0; i < enemy_rects->size(); i++)
    {
        SDL_RenderCopy(renderer, enemy_texture, NULL, &enemy_rects->at(i));
    }

    //retangulo de % da bomba
    SDL_Rect bomb_rect = {15, 50, static_cast<int>(bomb), 20};
    SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255);
    SDL_RenderFillRect(renderer, &bomb_rect);
    

    //draw kills
    SDL_Texture* text_texture = text_textures[*kills];
    SDL_RenderCopy(renderer, text_texture, NULL, new SDL_Rect{450, 0, 100, 50});

    
}



void Texture_Handler::free_texture(SDL_Texture* texture)
{
    SDL_DestroyTexture(texture);
}

