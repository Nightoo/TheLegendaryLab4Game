#include <iostream>
//#include <string>
#include <cstdlib>
#include <algorithm>
#include <vector>
#include "Objects.hpp"
#define DOORS_NUMBER 4

using namespace std;

class Map{
public:
    int size;
    int key_pos_x;
    int key_pos_y;
    int doors;
    int *Doors;
    int walls;
    vector<string> str_map;
    int counter = 0;
    Map(int _size = 10){
        size = _size;
        key_pos_x = rand()%(_size - 2) + 1;
        key_pos_y = rand()%(_size - 2);
        doors = (rand()%DOORS_NUMBER) + 1;
        Doors = new int[doors];
        for (int i = 0; i < doors; i++){
            int a = rand()%((_size - 1)*4);
            if (a == 0 || a == _size - 1|| a == _size + (_size - 2) * 2 || a == (_size - 1) * 4 - 1){
                if (a == 0){
                    Doors[i] = a + 1;
                }
                else {
                    Doors[i] = a - 1;
                }
            }
            else {
                Doors[i] = a;
            }
        }
        walls = 0;
    }

    void add_to_string_map(Object* obj){
        str_map[counter] = obj->set_object();
        counter++;
    }

    void make_row(){
        int r;
        for (int i = 0; i < size; i++){
            if (i == 0 || i == size - 1){
                auto *check = find(Doors, Doors + doors, walls);
                if (check != Doors + doors){
                    Object *obj = new Door();
                    add_to_string_map(obj);
                    walls++;
                }
                else {
                    Object *obj = new Wall();
                    add_to_string_map(obj);
                    walls++;
                }
            }
            else{
                r = rand()%20;
                if (r == 0){
                    Object *obj = new Rock();
                    add_to_string_map(obj);
                }
                else{
                    Object *obj = new Empty();
                    add_to_string_map(obj);
                }
            }
        }
        cout << endl;
    }

    void make_row_with_key(){
        int r;
        for (int i = 0; i < size; i++){
            if (i == key_pos_x){
                Object *obj = new Key();
                add_to_string_map(obj);
            }
            else {
                if (i == 0 || i == size - 1) {
                    auto *check = find(Doors, Doors + doors, walls);
                    if (check != Doors + doors){
                        Object *obj = new Door();
                        add_to_string_map(obj);
                        walls++;
                    }
                    else {
                        Object *obj = new Wall();
                        add_to_string_map(obj);
                        walls++;
                    }
                } else {
                    r = rand() % 20;
                    if (r == 0) {
                        Object *obj = new Rock();
                        add_to_string_map(obj);
                    } else {
                        Object *obj = new Empty();
                        add_to_string_map(obj);
                    }
                }
            }
        }
        cout << endl;
    }

    void make_horizontal_wall() {
        for (int i = 0; i < size; i++) {
            auto *check = find(Doors, Doors + doors, walls);
            if (check != Doors + doors){
                Object *obj = new Door();
                add_to_string_map(obj);
                walls++;
            }
            else {
                Object *obj = new Wall();
                add_to_string_map(obj);
                walls++;
            }
        }
        cout<< endl;
    }

    vector<string> make_map(){
        this->make_horizontal_wall();
        for (int i = 0; i < size - 2;i++){
            if (i == key_pos_y){
                this->make_row_with_key();
            }
            else {
                this->make_row();
            }
        }
        this->make_horizontal_wall();
        return str_map;
    }
};