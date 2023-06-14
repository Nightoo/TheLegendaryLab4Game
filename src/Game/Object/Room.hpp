#pragma once
#include "Game/Object/Map.hpp"
#include <SFML/Graphics.hpp>
#include <vector>

class Room
{
public:
    Map map;
    std::vector<std::string> map_s;
    sf::Texture texture;
    sf::Sprite sprite;
    int counter;

    Room()
    {
        map_s  = map.make_map();
        texture.loadFromFile("texture.png");
        sprite.setTexture(texture);
        counter = 0;
    }

    void show(sf::RenderWindow *window){
        counter = 0;
        for (auto it = map_s.begin(); it != map_s.end(); it++){
            if (*it == " ") {sprite.setTextureRect(sf::IntRect(0,0,20,20));};
            if (*it == "0") {sprite.setTextureRect(sf::IntRect(20,0,20,20));};
            if (*it == "*") {sprite.setTextureRect(sf::IntRect(40,0,20,20));};
            if (*it == "K") {sprite.setTextureRect(sf::IntRect(60,0,20,20));};
            if (*it == "#") {sprite.setTextureRect(sf::IntRect(80,0,20,20));};
            sprite.setPosition(sf::Vector2f((counter % 40 ) * 20, (counter / 40) * 20));
            window->draw(sprite);
            counter++;
        }
    }
};
