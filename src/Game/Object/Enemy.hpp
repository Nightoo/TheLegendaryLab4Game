#pragma once
#include <SFML/Graphics.hpp>
#include "Game/Object/Room.hpp"
#include "Definitions.hpp"
#include "Game/Object/Player.hpp"
#include <cstdlib>

class Enemy{
public:
    Room* room;
    int position_x = rand()%(MAP_SIZE - 2) + 1;
    int position_y = rand()%(MAP_SIZE - 2) + 1;

    Enemy(Room *room_){
        room = room_;
        room->TileMap[position_x][position_y] = 'E';
    }

    ~Enemy(){
        room->TileMap[position_x][position_y] = ' ';
    };

    void move(Player* player){
        int x = player->position_x;
        int y = player->position_y;
        room->TileMap[position_x][position_y] = ' ';
        if (abs(x - position_x) < abs(y - position_y) && x == position_x){
            position_y += (y - position_y) / abs(y - position_y);
        }
        if (abs(x - position_x) > abs(y - position_y) && y == position_y){
            position_x += (x - position_x) / abs(x - position_x);
        }
        if (abs(x - position_x) < abs(y - position_y) && x != position_x){
            position_x += (x - position_x) / abs(x - position_x);
        }
        if (abs(x - position_x) > abs(y - position_y) && y != position_y){
            position_y += (y - position_y) / abs(y - position_y);
        }
        if (abs(x - position_x) == abs(y - position_y)){
            int r = rand()%2;
            if (r == 0) {
                position_x += (x - position_x) / abs(x - position_x);
            }
            else{
                position_y += (y - position_y) / abs(y - position_y);
            }
        }
        if (x == position_x && y == position_y){
            player->lives -= 1;
            cout << player->lives << endl;
        }
        room->TileMap[position_x][position_y] = 'E';
    }
};