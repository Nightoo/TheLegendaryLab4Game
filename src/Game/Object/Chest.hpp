#pragma once
#include <SFML/Graphics.hpp>
#include "Game/Object/Room.hpp"
#include "Definitions.hpp"
#include "Game/Object/Player.hpp"

class Chest{
public:
    int position_x;
    int position_y;
    Room* room;

    Chest(Room* room_){
        room = room_;
        position_x = CHEST_X;
        position_y = CHEST_Y;
        room->TileMap[position_x][position_y] = 'C';
        room->TileMap[position_x - 1][position_y] = ' ';
        room->TileMap[position_x][position_y - 1] = ' ';
        room->TileMap[1][2] = ' ';
        room->TileMap[2][1] = ' ';
        room->TileMap[2][2] = ' ';
    }
};
