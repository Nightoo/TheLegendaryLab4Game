#pragma once

#include <SFML/Graphics.hpp>

class Room
{
public:
    sf::CircleShape polygon;

    Room()
    {
        polygon = sf::CircleShape(100, 9);
        polygon.setFillColor(sf::Color::Yellow);
        polygon.setPosition(sf::Vector2f(400, 0));
    }
};
