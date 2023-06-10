#pragma once

#include <iostream>
#include "Game/State/IState.hpp"

class ExitState : public IState
{
public:
    ExitState(Application *app) : IState(app) {}

    void go_next() override
    {
        std::cout << "Exit!" << std::endl;
    }

    bool is_on() override
    {
        std::cout << "Exit" << std::endl;
        return false;
    };
};
