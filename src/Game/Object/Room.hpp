#pragma once
#include "Game/Object/Map.hpp"
#include <SFML/Graphics.hpp>
#include <vector>
#include "Definitions.hpp"

class Room
{
public:
    Map map;
    std::vector<std::string> map_s;
    std::string TileMap[MAP_SIZE];
    sf::Texture texture;
    sf::Sprite sprite;

    Room()
    {
        map_s  = map.make_map();
        int counter = 1;
        std::string str = "";
        for (auto it = map_s.begin(); it != map_s.end(); it++){
            str += *it;
            if (counter % MAP_SIZE == 0){
                TileMap[counter / MAP_SIZE - 1] = str;
                str = "";
            }
            counter++;
        }
        texture.loadFromFile("texture.png");
        sprite.setTexture(texture);
    }

    void show(sf::RenderWindow *window){
            for(int i = 0; i < MAP_SIZE; i++){
                for (int j = 0; j < MAP_SIZE; j++){
                    if (TileMap[i][j] == ' ') {sprite.setTextureRect(sf::IntRect(0 * TEXTURE_SIZE,0,TEXTURE_SIZE,TEXTURE_SIZE));};
                    if (TileMap[i][j] == '0') {sprite.setTextureRect(sf::IntRect(1 * TEXTURE_SIZE,0,TEXTURE_SIZE,TEXTURE_SIZE));};
                    if (TileMap[i][j] == '*') {sprite.setTextureRect(sf::IntRect(2 * TEXTURE_SIZE,0,TEXTURE_SIZE,TEXTURE_SIZE));};
                    if (TileMap[i][j] == 'K') {sprite.setTextureRect(sf::IntRect(3 * TEXTURE_SIZE,0,TEXTURE_SIZE,TEXTURE_SIZE));};
                    if (TileMap[i][j] == '#') {sprite.setTextureRect(sf::IntRect(4 * TEXTURE_SIZE,0,TEXTURE_SIZE,TEXTURE_SIZE));};
                    if (TileMap[i][j] == 'E') {sprite.setTextureRect(sf::IntRect(6 * TEXTURE_SIZE,0,TEXTURE_SIZE,TEXTURE_SIZE));};
                    if (TileMap[i][j] == 'P') {sprite.setTextureRect(sf::IntRect(5 * TEXTURE_SIZE,0,TEXTURE_SIZE,TEXTURE_SIZE));};
                    if (TileMap[i][j] == 'B') {sprite.setTextureRect(sf::IntRect(110,0,TEXTURE_SIZE,TEXTURE_SIZE));};
                    if (TileMap[i][j] == 'D') {sprite.setTextureRect(sf::IntRect(0,0,TEXTURE_SIZE,TEXTURE_SIZE));};
                    sprite.setPosition(sf::Vector2f(i * TEXTURE_SIZE, j * TEXTURE_SIZE));
                    window->draw(sprite);
                }
        }
    }
};
