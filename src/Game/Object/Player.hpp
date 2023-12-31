#pragma once
#include <SFML/Graphics.hpp>
#include "Game/Object/Room.hpp"
#include "Definitions.hpp"

class Player{
public:
    Room* room;
    int position_x = PLAYER_START_X;
    int position_y = PLAYER_START_Y;
    bool have_key;
    bool win;
    int lives;
    int ammo;

    Player(Room *room_){
        room = room_;
        room->TileMap[position_x][position_y] = 'P';
        have_key = false;
        win = false;
        lives = LIVES;
        ammo = BOMBS;
    }

    void move_up(){
        room->TileMap[position_x][position_y - 1] = pick_up_key(room->TileMap[position_x][position_y - 1]);
        if (can_move(room->TileMap[position_x][position_y - 1])) {
            if (room->TileMap[position_x][position_y - 1] == 'E'){
                room->TileMap[position_x][position_y] = ' ';
            }
            else {
                room->TileMap[position_x][position_y] = room->TileMap[position_x][position_y - 1];
            }
            room->TileMap[position_x][position_y - 1] = 'P';
            position_y -= 1;
        }
    }

    void move_down(){
        room->TileMap[position_x][position_y+1] = pick_up_key(room->TileMap[position_x][position_y+1]);
        if (can_move(room->TileMap[position_x][position_y+1])) {
            if (room->TileMap[position_x][position_y + 1] == 'E'){
                room->TileMap[position_x][position_y] = ' ';
            }
            else {
                room->TileMap[position_x][position_y] = room->TileMap[position_x][position_y + 1];
            }
            room->TileMap[position_x][position_y + 1] = 'P';
            position_y += 1;
        }
    }

    void move_left(){
        room->TileMap[position_x - 1][position_y] = pick_up_key(room->TileMap[position_x - 1][position_y]);
        if (can_move(room->TileMap[position_x - 1][position_y])) {
            if (room->TileMap[position_x - 1][position_y] == 'E'){
                room->TileMap[position_x][position_y] = ' ';
            }
            else {
                room->TileMap[position_x][position_y] = room->TileMap[position_x - 1][position_y];
            }
            room->TileMap[position_x - 1][position_y] = 'P';
            position_x -= 1;
        }
    }

    void move_right(){
        room->TileMap[position_x + 1][position_y] = pick_up_key(room->TileMap[position_x + 1][position_y]);
        if (can_move(room->TileMap[position_x + 1][position_y])) {
            if (room->TileMap[position_x + 1][position_y] == 'E'){
                room->TileMap[position_x][position_y] = ' ';
            }
            else {
                room->TileMap[position_x][position_y] = room->TileMap[position_x + 1][position_y];
            }
            room->TileMap[position_x + 1][position_y] = 'P';
            position_x += 1;
        }
    }

    char pick_up_key(char s){
        if (s == 'K'){
            have_key = true;
            return ' ';
        }
        return s;
    }

    void shoot(){
        ammo -= 1;
    }

    bool can_move(char s){
        if (s == '*' || s == '#'){
            return false;
        }
        if (s == 'C' && have_key){
            win = true;
            return true;
        }
        if (s == 'C' && !have_key){
            return false;
        }
        return true;
    }

};
