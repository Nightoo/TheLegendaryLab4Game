#pragma once

#include <string>
#include <SFML/Graphics.hpp>

class IWindowKeeper
{
public:
    std::string mode;
    std::string title;
    sf::RenderWindow *window;

    IWindowKeeper(std::string mode_ = "mode", std::string title_ = "title")
    {
        this->window = nullptr;
        mode = mode_;
        title = title_;
    }

protected:
    virtual void event_handling(){};
    virtual void render(){};
};
