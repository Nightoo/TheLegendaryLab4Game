#pragma once

#include <SFML/Graphics.hpp>
#include "Game/Component/Button.hpp"

class Menu
{
public:
    Button easy;
    Button medium;
    Button hard;

    Menu()
    {
        easy = Button("EASY", sf::Color(0, 100, 255));
        medium = Button("MEDIUM", sf::Color(0, 100, 255), sf::Vector2f(100, 200));
        hard = Button("HARD", sf::Color(0, 100, 255), sf::Vector2f(100, 350));
    }
};
