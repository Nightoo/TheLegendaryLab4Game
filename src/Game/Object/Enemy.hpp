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
    int position_y = rand()%(MAP_SIZE / 2) + 1;
    bool is_alive = true;

    Enemy(Room *room_){
        room = room_;
        room->TileMap[position_x][position_y] = 'E';
    }

    ~Enemy(){
        room->TileMap[position_x][position_y] = 'D';
        position_x = -10;
        position_y = -10;
        is_alive = false;
    };

    void move(Player* player){
        int x = player->position_x;
        int y = player->position_y;
        int cur_x = position_x;
        int cur_y = position_y;
        int new_x = cur_x;
        int new_y = cur_y;
        if (abs(x - cur_x) <= 1 && abs(y - cur_y) <= 1){
            delete this;
            player->lives -= 1;
        }
        if(is_alive) {
            //room->TileMap[position_x][position_y] = ' ';
            if ((abs(x - cur_x) < abs(y - cur_y)) && x == cur_x) {
                new_y += ((y - cur_y) / abs(y - cur_y));
            }
            if ((abs(x - cur_x) > abs(y - cur_y)) && y == cur_y) {
                new_x += ((x - cur_x) / abs(x - cur_x));
            }
            if ((abs(x - cur_x) < abs(y - cur_y)) && x != cur_x) {
                new_x += ((x - cur_x) / abs(x - cur_x));
            }
            if ((abs(x - cur_x) > abs(y - cur_y)) && y != cur_y) {
                new_y += ((y - cur_y) / abs(y - cur_y));
            }
            if (abs(x - cur_x) == abs(y - cur_y)) {
                int r = rand() % 2;
                if (r == 0) {
                    new_x += ((x - cur_x) / abs(x - cur_x));
                } else {
                    new_y += ((y - cur_y) / abs(y - cur_y));
                }
            }
            if (can_move(new_x, new_y, player)) {
                room->TileMap[cur_x][cur_y] = room->TileMap[new_x][new_y];
                position_x = new_x;
                position_y = new_y;
                room->TileMap[position_x][position_y] = 'E';
            }
        }
        else{
            position_x = -10;
            position_y = -10;
        }
    }

    bool can_move(int x, int y, Player* pl){
        if (room->TileMap[x][y] == ' '){ return true;}
        if (room->TileMap[x][y] == '*'){ return false;}
        if (room->TileMap[x][y] == '#'){ return false;}
        if (room->TileMap[x][y] == '0'){ return false;}
        if (room->TileMap[x][y] == 'K'){ return false;}
        if (room->TileMap[x][y] == 'D'){ return true;}
        if (room->TileMap[x][y] == 'E'){ return false;}
        if ((room->TileMap[x][y] == 'P') || (abs(x - pl->position_x) <= 1 || abs(y-pl->position_y) <= 1)){
            pl->lives -=1;
            delete this;
            return false;
        }
        return true;
    }
};