#pragma once

#include <SFML/Graphics.hpp>
#include <string>
#include <iostream>
#include "Game/State/IState.hpp"
#include "Game/State/ExitState.hpp"
#include "Game/Component/IWindowKeeper.hpp"
#include "Game/Object/Room.hpp"
#include "Game/Object/Player.hpp"

class GameState : public IState, public IWindowKeeper
{
public:
    Application *app;
    Room *room;
    Player *player;

    GameState(
        Application *app_,
        std::string mode_ = "mode",
        std::string title_ = "title")
        : IWindowKeeper(mode_, title_)
    {
        this->app = app_;
        this->window = new sf::RenderWindow(sf::VideoMode(800, 800), "Game");
        this->room = new Room();
        this->player = new Player(room);
        this->render();
    }

    ~GameState()
    {
        delete window;
        delete room;
    }

    void render() override
    {
        room->show(window);
    }

    bool update() override {
        sf::Event event;
        while (window->pollEvent(event)) {
            window->clear();
            render();
            if (event.type == sf::Event::KeyPressed) {
                if (event.key.code == sf::Keyboard::W) { player->move_up(); }
                if (event.key.code == sf::Keyboard::A) { player->move_left(); }
                if (event.key.code == sf::Keyboard::S) { player->move_down(); }
                if (event.key.code == sf::Keyboard::D) { player->move_right(); }
            }
            window->display();
        }
        return true;
    }

    void go_next() override
    {
        std::cout << "Game -> Exit" << std::endl;
        app->set_next_state(new ExitState(app));
    }

    bool is_on() override
    {
        //std::cout << "Game" << std::endl;
        return true;
    }
};
