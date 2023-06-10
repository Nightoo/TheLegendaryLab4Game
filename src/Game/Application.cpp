#include "Game/Application.hpp"

Application::Application(IState *state_)
{
    set_next_state(state_);
}

Application::~Application()
{
    delete state;
}

void Application::set_next_state(IState *st)
{
    if (state != nullptr)
        delete state;
    state = st;
    state->set_app(this);
}

void Application::change()
{
    state->go_next();
}

bool Application::active()
{
    return state->is_on();
}

void Application::run()
{
    while (active())
    {
        if (!state->update())
        {
            state->go_next();
        }
    }
}
