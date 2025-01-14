#include <iostream>
#include <SDL2/SDL.h>
#include "enemies.h"
#include <vector>
#include <random>


enemies::enemies(int size, int cd, int chance)
{
    horde_max_size = size;
    spawn_cd_max = cd;
    spawn_chance = chance;
}

enemies::~enemies()
{
}

void enemies::spawn()
{
    if(horde.size() < horde_max_size)
    {
        if(rand() % 100 < spawn_chance)
        {
            SDL_Rect enemy;

            enemy.x = 0;
            enemy.y = 0;
            enemy.w = 50;
            enemy.h = 50;

            //evitar colisoes com outros inimigos
            bool colide = true;
            while(colide)
            {
                colide = false;
                enemy.y = rand() % ((SCREEN_HEIGHT/3 * 2) - 2*enemy.h) + enemy.h;
                enemy.x = rand() % (SCREEN_WIDTH - 2*enemy.w) + enemy.w;
                for(int i = 0; i<horde.size(); i++)
                {
                    if(SDL_HasIntersection(&enemy, &horde[i]))
                    {
                        colide = true;
                        break;
                    }
                }
            }

            
            horde.push_back(enemy);
            int temp_speed = rand() % 2;
            temp_speed == 0 ? speed.push_back(2) : speed.push_back(-2);
            shoot_cd.push_back(rand() % 100);


        }
    } 
}

void enemies::update(std::vector<SDL_Rect>& bullets, std::vector<float>& bullets_y)
{
    //spawn
    if(spawn_cd == 0)
    {
        spawn();
        spawn_cd = spawn_cd_max;
    }
    else
    {
        spawn_cd--;
    }
    
    //movimento horda
    for(int i  = 0; i<horde.size(); i++)
    {
        horde[i].x += speed[i];
        
    }

    //limites da tela
    for(int i = 0; i<horde.size(); i++)
    {
        //se colidir, inverte a direcao
        if(horde[i].x < 0 || horde[i].x + horde[i].w > SCREEN_WIDTH)
        {
            speed[i] = -speed[i];
        }

    }
    
    //shoot
    for(int i = 0; i<horde.size(); i++)
    {
        if(shoot_cd[i] == 0)
        {
            SDL_Rect bullet;
            bullet.x = horde[i].x + horde[i].w/2;
            bullet.y = horde[i].y;
            bullet.w = 5;
            bullet.h = 5;

            enemy_bullets.push_back(bullet);
            enemy_bullets_y.push_back(bullet.y);
            bullets_speed.push_back(0.5);
            bullets_size.push_back(5);

            shoot_cd[i] = shoot_cd_max;
        }
        else
        {
            shoot_cd[i]--;
        }
    }

    //movimento bullets
    for(int i = 0; i<enemy_bullets.size(); i++)
    {
        enemy_bullets_y[i] += bullets_speed[i];
        enemy_bullets[i].y = static_cast<int>(enemy_bullets_y[i]);
    }

    //enemy kill
    for(int i = 0; i<horde.size(); i++)
    {
        for(int j = 0; j<bullets.size(); j++)
        {
            if(SDL_HasIntersection(&horde[i], &bullets[j]))
            {
                horde.erase(horde.begin() + i);
                speed.erase(speed.begin() + i);
                shoot_cd.erase(shoot_cd.begin() + i);
                *bullets.erase(bullets.begin() + j);
                *bullets_y.erase(bullets_y.begin() + j);
            }
        }
    }


}

void enemies::draw(SDL_Renderer* renderer)
{
    for(int i = 0; i<horde.size(); i++)
    {
        SDL_SetRenderDrawColor(renderer, 255, 255, 0, 255);
        SDL_RenderFillRect(renderer, &horde[i]);
    }

    for(int i = 0; i<enemy_bullets.size(); i++)
    {
        SDL_SetRenderDrawColor(renderer, 255, 0, 255, 255);
        SDL_RenderFillRect(renderer, &enemy_bullets[i]);
    }
}

