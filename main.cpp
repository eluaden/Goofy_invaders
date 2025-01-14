#include <SDL2/SDL.h>
#include <iostream>
#include <vector>
#include "player.h"
#include "enemies.h"

const int SCREEN_WIDTH = 600;
const int SCREEN_HEIGHT = 800;

void Game_Over(SDL_Renderer* renderer);

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
        SDL_RENDERER_ACCELERATED
    );
    if(renderer == nullptr) 
    {
        std::cerr << "Renderer could not be created! SDL_Error: " << SDL_GetError() << std::endl;
        return 1;
    }

    //objects
    player player_1(5,(SCREEN_WIDTH/3 * 2), (SCREEN_HEIGHT/3 * 2));
    enemies horde(10, 100, 100);
    std::vector<SDL_Rect> life_rects = {SDL_Rect{0,0,20,20}, SDL_Rect{25,0,20,20}, SDL_Rect{50,0,20,20}, SDL_Rect{75,0,20,20}, SDL_Rect{100,0,20,20}};
    int dead_enemies = 0;
    

    //loop principal
    bool running = true;
    SDL_Event event;

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

        player_1.update(horde.enemy_bullets, horde.enemy_bullets_y);
        player_1.draw(renderer);
        

        if (player_1.life <= 0)
        {
            Game_Over(renderer);  // Exibe a tela de Game Over
            
            // Aguarda o jogador pressionar uma tecla para sair ou reiniciar
            bool gameOver = true;
            while (gameOver) {
                while (SDL_PollEvent(&event) != 0) {
                    if (event.type == SDL_QUIT) {
                        running = false;
                        gameOver = false;
                    }
                    if (event.type == SDL_KEYDOWN) {
                        if (event.key.keysym.sym == SDLK_q) {  // Pressione Q para sair
                            running = false;
                            gameOver = false;
                        } else if (event.key.keysym.sym == SDLK_r) {  // Pressione R para reiniciar
                            // Resetar o estado do jogo para reiniciar
                            player_1.bullets.clear();
                            player_1.bullets_y.clear();
                            player_1.life = 5;
                            player_1.position = std::make_pair(SCREEN_WIDTH/3 * 2, SCREEN_HEIGHT/3 * 2);
                            player_1.ultimate_bombs = 100;
                            horde.horde.clear();
                            horde.speed.clear();
                            horde.shoot_cd.clear();
                            horde.enemy_bullets.clear();
                            horde.enemy_bullets_y.clear();
                            gameOver = false;
                        
                        }
                    }
                }
            }
        }
                

        horde.update(player_1.bullets, player_1.bullets_y);
        horde.draw(renderer);

        //retangulos de vida
        while(player_1.life < life_rects.size())
        {
            life_rects.pop_back();
        }
        for(int i = 0; i<life_rects.size(); i++)
        {
            SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255);
            SDL_RenderFillRect(renderer, &life_rects[i]);
        }

        
        SDL_RenderPresent(renderer);
    }


    // Clean up
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();

}


void Game_Over(SDL_Renderer* renderer) {
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);  // Fundo preto
    SDL_RenderClear(renderer);

    // Defina a cor do texto, fundo, etc.
    SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255);  // Cor vermelha para o texto

    // Aqui você pode usar SDL_ttf para desenhar um texto ou desenhar uma caixa de mensagem
    // Caso queira usar uma caixa de mensagem simples:
    SDL_Rect game_over_rect = { SCREEN_WIDTH / 4, SCREEN_HEIGHT / 3, SCREEN_WIDTH / 2, 100 };  // Caixa do Game Over
    SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255); // Vermelho
    SDL_RenderFillRect(renderer, &game_over_rect);  // Desenha o retângulo

    // Aqui poderia ser o código para renderizar texto
    // Como você não está usando SDL_ttf, você pode adicionar alguma imagem ou um retângulo simples como abaixo.

    // Exemplo de renderização simples de texto:
    // SDL_RenderText(renderer, "GAME OVER", x, y);

    SDL_RenderPresent(renderer);
}
