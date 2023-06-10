#include <iostream>
#include <string>
#include <cstdlib>
#include <algorithm>
#include "Objects.hpp"
#define DOORS_NUMBER 4

class Map{
public:
    int size;
    int key_pos_x;
    int key_pos_y;
    int doors;
    int *Doors;
    int walls;
    Map();
    void make_row();
    void make_row_with_key();
    void make_horizontal_wall();
    std::vector<std::string> make_map();
};