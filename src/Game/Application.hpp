#pragma once

#include "State/IState.hpp"

class Application
{
public:
    IState *state = nullptr;

    Application(IState *state_ = nullptr);
    ~Application();

    void set_next_state(IState *st);
    void change();
    bool active();
    void run();
};
