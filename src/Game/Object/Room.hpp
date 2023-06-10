#pragma once
#include "Map.hpp"
#include <SFML/Graphics.hpp>
#include <vector>

class Room
{
public:
    Map map;
    std::vector<std::string> map_s;

    Room()
    {
        map_s = map.make_map();
    }
};
