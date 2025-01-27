#pragma once

#include <iostream>
#include <vector>
#include <unordered_map>


typedef struct LevelInfo
{
    std::string name;
    int lifes;
    int shoot_cd;
    int ultimate_bombs;
    int enemy_speed;
    int enemy_bullets_speed;
    int level_limit;
}LevelInfo;


extern std::unordered_map<int, LevelInfo> levels_data;
