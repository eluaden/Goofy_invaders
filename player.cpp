#include <iostream>
#include <SDL2/SDL.h>
#include <vector>
#include "player.h"



player::player(int player_life,int x, int y)
{
    position.first = x;
    position.second = y;
    rect.x = x;
    rect.y = y;
    rect.w = 20;
    rect.h = 20;
    speed = 3;
    life = player_life;
}

player::~player()
{
}

void player::shoot()
{
    SDL_Rect bullet;
    bullet.x = position.first + rect.w/2;
    bullet.y = position.second;
    bullet.w = bullet_size;
    bullet.h = bullet_size;

    bullets.push_back(bullet);
    bullets_y.push_back(bullet.y);

}

void player::ultimate_bomb(std::vector<SDL_Rect>& enemy_bullets, std::vector<float>& enemy_bullets_y)
{
    bullets.clear();
    bullets_y.clear();
    enemy_bullets.clear();
    enemy_bullets_y.clear();
}


void player::update(std::vector<SDL_Rect>& enemy_bullets, std::vector<float>& enemy_bullets_y)
{
    const Uint8* keys = SDL_GetKeyboardState(NULL);

    if(keys[SDL_SCANCODE_W])
    {
        position.second -= speed;
    }
    if(keys[SDL_SCANCODE_S])
    {
        position.second += speed;
    }
    if(keys[SDL_SCANCODE_A])
    {
        position.first -= speed;
    }
    if(keys[SDL_SCANCODE_D])
    {
        position.first += speed;
    }
    if(keys[SDL_SCANCODE_SPACE])
    {
        if(temp_shoot_cd == 0)
        {
            shoot();
            temp_shoot_cd = shoot_cd;
        }
    }
    if(keys[SDL_SCANCODE_LSHIFT] && ultimate_bombs > 0)
    {
        ultimate_bomb(enemy_bullets, enemy_bullets_y);
        ultimate_bombs--;
    }

    //limites da tela
    if(position.first < 0) position.first = 0;
    if(position.first + rect.w > SCREEN_WIDTH) position.first = SCREEN_WIDTH - rect.w;
    if(position.second < SCREEN_HEIGHT/3 * 2) position.second = SCREEN_HEIGHT/3 * 2;
    if(position.second + rect.h > SCREEN_HEIGHT) position.second = SCREEN_HEIGHT - rect.h;

    //atualiza os tiros
    //cooldown do tiro
    if(temp_shoot_cd > 0) temp_shoot_cd--;

    //atualiza a posicao dos tiros
    for(int i = 0; i < bullets.size(); i++)
    {
        bullets_y[i] -= bullet_speed;
        bullets[i].y = static_cast<int>(bullets_y[i]);
    }

    //deleta os tiros que sairam da tela
    for(int i = 0; i < bullets.size(); i++)
    {
        if(bullets[i].y < 0)
        {
            bullets.erase(bullets.begin() + i);
            bullets_y.erase(bullets_y.begin() + i);
        }
    }

    //colisao com os tiros inimigos
    for(int i = 0; i < enemy_bullets.size(); i++)
    {
        if(SDL_HasIntersection(&rect, &enemy_bullets[i]))
        {
            life--;
            enemy_bullets.erase(enemy_bullets.begin() + i);
            enemy_bullets_y.erase(enemy_bullets_y.begin() + i);
        }
    }


    //atualiza a posicao do player
    rect.x = position.first;
    rect.y = position.second;

    
}

void player::draw(SDL_Renderer* renderer)
{
    SDL_SetRenderDrawColor(renderer, 0, 255, 0, 255);
    SDL_RenderFillRect(renderer, &rect);

    //desenha os tiros
    for(int i = 0; i < bullets.size(); i++)
    {
        SDL_SetRenderDrawColor(renderer, 0, 0, 255, 125);
        SDL_RenderFillRect(renderer, &bullets[i]);
    }
}


