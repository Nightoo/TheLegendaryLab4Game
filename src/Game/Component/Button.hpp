#pragma once

#include <string>
#include <iostream>
#include <SFML/Graphics.hpp>

class Button
{
public:
    sf::RectangleShape button;
    sf::Text text;
    sf::Color color;
    sf::RectangleShape select_shape;
    sf::Font font;
    bool selected = false;

    Button(
        std::string txt = "level",
        sf::Color color_ = sf::Color::Red,
        sf::Vector2f pos = sf::Vector2f(100, 50),
        sf::Vector2f size = sf::Vector2f(150, 100))
    {
        button = sf::RectangleShape(size);
        color = color_;
        button.setFillColor(color);
        button.setPosition(pos);
        if (!font.loadFromFile("c:/windows/fonts/arial.ttf"))
        {
            throw "FONT ERROR";
        }
        text.setPosition(sf::Vector2f(pos.x, pos.y+30));
        text.setString(txt);
        select_shape = sf::RectangleShape(sf::Vector2f(size.x + 20, size.y + 20));
        select_shape.setFillColor(sf::Color::Yellow);
        select_shape.setPosition(sf::Vector2f(pos.x - 10, pos.y - 10));
    }

    void show(sf::RenderWindow *window)
    {
        text.setFont(font);
        text.setCharacterSize(30);
        text.setFillColor(sf::Color::Black);
        if (selected)
        {
            window->draw(select_shape);
            text.setFillColor(sf::Color::Yellow);

        }
        window->draw(button);
        window->draw(text);
    }

    void select()
    {
        selected = true;
    }

    void unselect()
    {
        selected = false;
    }
};
