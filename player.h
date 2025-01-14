#include <iostream>
#include <SDL2/SDL.h>
#include <vector>

class player
{
    private:
    
    SDL_Rect rect;
    int speed;
    

    //bullets
    const int shoot_cd = 100;
    int temp_shoot_cd = 1;
    float bullet_speed = 0.8;
    int bullet_size = 5;
    
    

    
    //screen infos
    int SCREEN_WIDTH = 600;
    int SCREEN_HEIGHT = 800;

    public:
        std::pair<int,int> position;
        int life;
        int ultimate_bombs = 100;
        std::vector<SDL_Rect> bullets;
        std::vector<float> bullets_y;


        player(int player_life,int x, int y);
        ~player();
    
        //sdl functions
        void draw(SDL_Renderer* renderer);

        //actions
        void shoot();
        void ultimate_bomb(std::vector<SDL_Rect>& enemy_bullets, std::vector<float>& enemy_bullets_y);
        void update(std::vector<SDL_Rect>& enemy_bullets, std::vector<float>& enemy_bullets_y);
};