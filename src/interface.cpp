#include "interface.h"  

void Interface_Handler::update(int life)
{
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
void Interface_Handler::level_up(SDL_Renderer* renderer, int level)
{
    //TODO
}

void Interface_Handler::Game_Over(SDL_Renderer* renderer, enemies* horde, player* player_1, bool* running)
{
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);  // Fundo preto
    SDL_RenderClear(renderer);
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
                    player_1->bullets.clear();
                    player_1->bullets_y.clear();
                    player_1->life = 5;
                    player_1->position = std::make_pair(SCREEN_WIDTH/3 * 2, SCREEN_HEIGHT/3 * 2);
                    player_1->ultimate_bombs = 100;
                    horde->horde.clear();
                    horde->speed.clear();
                    horde->shoot_cd.clear();
                    horde->enemy_bullets.clear();
                    horde->enemy_bullets_y.clear();
                    horde->bullets_speed.clear();
                    horde->bullets_size.clear();                  
                    gameOver = false;
                }
                else if (event.key.keysym.sym == SDLK_q) {  // Pressione Q para sair
                    gameOver = false;
                    *running = false;
                }
            }
        }
    }
}

Interface_Handler::Interface_Handler(int life)
{
    for(int i = 0; i<life; i++)
    {
        SDL_Rect temp;
        temp.x = 10 + i*20;
        temp.y = 10;
        temp.w = 30;
        temp.h = 30;
        life_rects.push_back(temp);
    }
}

Interface_Handler::~Interface_Handler()
{
    
}