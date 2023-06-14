#pragma once

#include <iostream>
#include <SFML/Graphics.hpp>
#include "Game/State/IState.hpp"
#include "Game/State/GameState.hpp"
#include "Game/Component/IWindowKeeper.hpp"
#include "Game/Component/Menu.hpp"
#include "Definitions.hpp"

class SelectLevelState : public IState, public IWindowKeeper
{
public:
    std::string mode;
    std::string title;
    Menu *menu;

    SelectLevelState(
        Application *app_,
        std::string mode_ = "mode",
        std::string title_ = "title")
        : IWindowKeeper(mode_, title_)
    {
        this->app = app_;
        this->window = new sf::RenderWindow(sf::VideoMode(MENU_WIDTH, MENU_HEIGHT), "Select");
        this->menu = new Menu();
        // this->render();
    }

    ~SelectLevelState()
    {
        delete this->menu;
        delete this->window;
    }

    void go_next() override
    {
        window->clear();
        window->close();
        std::cout << "Select -> Game" << std::endl;
        auto next_state = new GameState(app);
        app->set_next_state(next_state);
    }

    bool is_on() override
    {
        std::cout << "Select" << std::endl;
        return true;
    }

    void render() override
    {
        menu->easy.show(window);
        menu->medium.show(window);
        menu->hard.show(window);
    }

    bool update() override
    {
        window->clear();
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Enter))
        {
            return false;
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::E))
        {
            menu->easy.select();
            menu->medium.unselect();
            menu->hard.unselect();
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::M))
        {
            menu->medium.select();
            menu->easy.unselect();
            menu->hard.unselect();
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::H))
        {
            menu->hard.select();
            menu->easy.unselect();
            menu->medium.unselect();
        }
        render();
        window->display();
        return true;
    }
};
