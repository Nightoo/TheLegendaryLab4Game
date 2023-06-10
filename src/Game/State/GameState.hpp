#pragma once

#include <SFML/Graphics.hpp>
#include <string>
#include <iostream>
#include "Game/State/IState.hpp"
#include "Game/State/ExitState.hpp"
#include "Game/Component/IWindowKeeper.hpp"
#include "Game/Object/Room.hpp"

class GameState : public IState, public IWindowKeeper
{
public:
    Application *app;
    Room *room;

    GameState(
        Application *app_,
        std::string mode_ = "mode",
        std::string title_ = "title")
        : IWindowKeeper(mode_, title_)
    {
        this->app = app_;
        this->window = new sf::RenderWindow(sf::VideoMode(600, 600), "Game");
        this->room = new Room();
        this->render();
    }

    ~GameState()
    {
        delete window;
        delete room;
    }

    void render() override
    {
        window->draw(room->polygon);
    }

    bool update() override
    {
        window->clear();
        window->draw(room->polygon);
        window->display();
        return true;
    }

    void go_next() override
    {
        std::cout << "Game -> Exit" << std::endl;
        app->set_next_state(new ExitState(app));
    }

    bool is_on() override
    {
        std::cout << "Game" << std::endl;
        return true;
    }
};
