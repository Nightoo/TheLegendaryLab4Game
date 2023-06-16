#pragma once

#include <iostream>
#include "Game/State/IState.hpp"
#include "Game/Component/IWindowKeeper.hpp"
#include "Definitions.hpp"
#include <unistd.h>

class ExitState : public IState, public IWindowKeeper{
public:
    Application* app;
    bool win;
    sf::Texture texture;
    sf::Sprite sprite;

    ExitState(
        Application *app_,
        bool win_,
        std::string mode_ = "mode",
        std::string title_ = "title")
        : IWindowKeeper(mode_, title_)
        {
            this->app = app_;
            this->window = new sf::RenderWindow(sf::VideoMode(EXIT_WIDTH, EXIT_HEIGHT), "EXIT");
            this->win = win_;
            if (win){
                texture.loadFromFile("win.png");
                sprite.setTexture(texture);
            }
            else{
                texture.loadFromFile("lose.png");
                sprite.setTexture(texture);
            }
            sprite.setPosition(sf::Vector2f(0,0));
            window->draw(sprite);
            window->display();
        }

    void go_next() override
    {
        std::cout << "Exit!" << std::endl;
    }

    bool is_on() override
    {
        sleep(3);
        std::cout << "Exit" << std::endl;
        return false;
    };
};
