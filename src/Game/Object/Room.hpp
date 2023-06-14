#pragma once
#include "Game/Object/Map.hpp"
#include <SFML/Graphics.hpp>
#include <vector>

class Room
{
public:
    Map map;
    std::vector<std::string> map_s;
    std::string TileMap[40];
    sf::Texture texture;
    sf::Sprite sprite;

    Room()
    {
        map_s  = map.make_map();
        int counter = 1;
        std::string str = "";
        for (auto it = map_s.begin(); it != map_s.end(); it++){
            str += *it;
            if (counter % 40 == 0){
                TileMap[counter / 40 - 1] = str;
                str = "";
            }
            counter++;
        }
        texture.loadFromFile("texture.png");
        sprite.setTexture(texture);
    }

    void show(sf::RenderWindow *window){
            for(int i = 0; i < 40; i++){
                for (int j = 0; j < 40; j++){
                    if (TileMap[i][j] == ' ') {sprite.setTextureRect(sf::IntRect(0,0,20,20));};
                    if (TileMap[i][j] == '0') {sprite.setTextureRect(sf::IntRect(20,0,20,20));};
                    if (TileMap[i][j] == '*') {sprite.setTextureRect(sf::IntRect(40,0,20,20));};
                    if (TileMap[i][j] == 'K') {sprite.setTextureRect(sf::IntRect(60,0,20,20));};
                    if (TileMap[i][j] == '#') {sprite.setTextureRect(sf::IntRect(80,0,20,20));};
                    if (TileMap[i][j] == 'P') {sprite.setTextureRect(sf::IntRect(100,0,20,20));};
                    sprite.setPosition(sf::Vector2f(i * 20, j * 20));
                    window->draw(sprite);
                }
        }
    }
};
