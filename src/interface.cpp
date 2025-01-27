#include "interface.h"  

void Interface_Handler::update(int life)
{
    //RETANGULOS DE VIDA
    while(life_rects.size() > life)
    {
        life_rects.pop_back();
    } 
    while(life_rects.size() < life)
    {
        SDL_Rect temp;
        temp.x = 10 + life_rects.size()*20;
        temp.y = 10;
        temp.w = 30;
        temp.h = 30;
        life_rects.push_back(temp);
    }

}

void Interface_Handler::level_up_aux(player* player_1, enemies* horde)
{
    // Atualiza as informações do nível

    player_1->life = level_info.lifes;
    player_1->ultimate_bombs = level_info.ultimate_bombs;
    player_1->position = std::make_pair(SCREEN_WIDTH/3 * 2, SCREEN_HEIGHT/3 * 2);
    player_1->kills = 0;
    player_1->bullets.clear();
    player_1->bullets_y.clear();
    horde->horde.clear();
    horde->speed.clear();
    horde->shoot_cd.clear();
    horde->enemy_bullets.clear();
    horde->enemy_bullets_y.clear();
    horde->bullets_speed.clear();
    horde->bullets_size.clear();
}

void Interface_Handler::level_up(SDL_Renderer* renderer, enemies* horde, player* player_1, bool* running)
{
    // Mostra a mensagem de Level Up
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);  // Fundo preto
    SDL_RenderClear(renderer);
    SDL_RenderPresent(renderer);

    SDL_Color color = {0, 255, 0};
    TTF_Font* font = TTF_OpenFont("assets/fonts/jersey_15.ttf", 52);
    std::string text = level_info.name + " complete!!";
    SDL_Surface* surface = TTF_RenderText_Solid(font, text.c_str(), color);
    SDL_Texture* texture = SDL_CreateTextureFromSurface(renderer, surface);
    SDL_Rect text_rect = {SCREEN_WIDTH/2 - surface->w/2, SCREEN_HEIGHT/2 - surface->h/2 -100, surface->w, surface->h};

    SDL_RenderCopy(renderer, texture, NULL, &text_rect);

    //mensagem que escreve o proximo nivel e instruções de tecla
    color = {255,255,255};
    font = TTF_OpenFont("assets/fonts/jersey_15.ttf", 20);
    text = "Aperte Q para sair, R para reiniciar ou N para ir pro proximo nivel";
    SDL_Surface* surface2 = TTF_RenderText_Solid(font, text.c_str(), color);
    SDL_Texture* texture2 = SDL_CreateTextureFromSurface(renderer, surface2);
    SDL_Rect text_rect2 = {SCREEN_WIDTH/2 - surface2->w/2, SCREEN_HEIGHT/2 + surface->h - 100, surface2->w, surface2->h};

    SDL_RenderCopy(renderer, texture2, NULL, &text_rect2);

    SDL_RenderPresent(renderer);

    // Aguarda o jogador pressionar uma tecla para sair, reiniciar ou ir para o próximo nível
    bool levelUp = true;
    SDL_Event event;
    while (levelUp) {
        while (SDL_PollEvent(&event) != 0) {
            if (event.type == SDL_QUIT) {
                levelUp = false;
                *running = false;
            }
            if (event.type == SDL_KEYDOWN) {
                if (event.key.keysym.sym == SDLK_r) {  // Pressione R para reiniciar
                    // Resetar o estado do jogo para reiniciar
                    level = 1;
                    level_info = levels_data[level];
                    restart(renderer, horde, player_1);             
                    levelUp = false;
                }
                else if (event.key.keysym.sym == SDLK_q) {  // Pressione Q para sair
                    levelUp = false;
                    *running = false;
                }
                else if (event.key.keysym.sym == SDLK_n) {  // Pressione N para ir para o próximo nível
                    level++;
                    level_info = levels_data[level];
                    level_up_aux(player_1, horde);
                    levelUp = false;
                }
            }
        }
    }    


    // libera as texturas
    SDL_DestroyTexture(texture);
    SDL_FreeSurface(surface);
    TTF_CloseFont(font);

}

void Interface_Handler::restart(SDL_Renderer* renderer, enemies* horde, player* player_1)
{
    // Resetar o estado do jogo para reiniciar
    player_1->bullets.clear();
    player_1->bullets_y.clear();
    player_1->position = std::make_pair(SCREEN_WIDTH/3 * 2, SCREEN_HEIGHT/3 * 2);
    player_1->kills = 0;
    horde->horde.clear();
    horde->speed.clear();
    horde->shoot_cd.clear();
    horde->enemy_bullets.clear();
    horde->enemy_bullets_y.clear();
    horde->bullets_speed.clear();
    horde->bullets_size.clear();              
    player_1->life = level_info.lifes;
    player_1->ultimate_bombs = level_info.ultimate_bombs;
}

void Interface_Handler::Game_Over(SDL_Renderer* renderer, enemies* horde, player* player_1, bool* running)
{
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);  // Fundo preto
    SDL_RenderClear(renderer);
    SDL_RenderPresent(renderer);
    

    // Mostra a mensagem de Game Over(e as instruções para reiniciar ou sair)
    SDL_Color color = {255, 0, 0};
    TTF_Font* font = TTF_OpenFont("assets/fonts/jersey_15.ttf", 52);
    SDL_Surface* surface = TTF_RenderText_Solid(font, "Game Over", color);
    SDL_Texture* texture = SDL_CreateTextureFromSurface(renderer, surface);
    SDL_Rect text_rect = {SCREEN_WIDTH/2 - surface->w/2, SCREEN_HEIGHT/2 - surface->h/2 - 100, surface->w, surface->h};
    
    SDL_RenderCopy(renderer, texture, NULL, &text_rect);

    color = {255, 255, 255};
    font = TTF_OpenFont("assets/fonts/jersey_15.ttf", 24);
    SDL_Surface* surface2 = TTF_RenderText_Solid(font, "Press R to restart or Q to quit", color);
    SDL_Texture* texture2 = SDL_CreateTextureFromSurface(renderer, surface2);
    SDL_Rect text_rect2 = {SCREEN_WIDTH/2 - surface2->w/2, SCREEN_HEIGHT/2 + surface->h - 100, surface2->w, surface2->h};

    SDL_RenderCopy(renderer, texture2, NULL, &text_rect2);



    SDL_RenderPresent(renderer);

    // Aguarda o jogador pressionar uma tecla para sair ou reiniciar
    bool gameOver = true;
    SDL_Event event;
    while (gameOver) {
        while (SDL_PollEvent(&event) != 0) {
            if (event.type == SDL_QUIT) {
                gameOver = false;
                *running = false;

            }
            if (event.type == SDL_KEYDOWN) {
                if (event.key.keysym.sym == SDLK_r) {  // Pressione R para reiniciar
                    // Resetar o estado do jogo para reiniciar
                    level = 1;
                    level_info = levels_data[level];
                    restart(renderer, horde, player_1);             
                    gameOver = false;
                }
                else if (event.key.keysym.sym == SDLK_q) {  // Pressione Q para sair
                    gameOver = false;
                    *running = false;
                }
            }
        }
    }


    // libera as texturas
    SDL_DestroyTexture(texture);
    SDL_FreeSurface(surface);
    TTF_CloseFont(font);
}

Interface_Handler::Interface_Handler(int life)
{
    level = 1;
    level_info = levels_data[level];
    
    for(int i = 0; i<life; i++)
    {
        SDL_Rect temp;
        temp.x = 10 + i*20;
        temp.y = 10;
        temp.w = 30;
        temp.h = 30;
        life_rects.push_back(temp);
    }

    if(TTF_Init() == -1)
    {
        std::cerr << "Failed to initialize TTF! SDL_Error: " << SDL_GetError() << std::endl;
    }

}



Interface_Handler::~Interface_Handler()
{
    
}