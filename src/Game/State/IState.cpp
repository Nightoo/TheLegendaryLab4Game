#include "Game/State/IState.hpp"

IState::IState(Application *app_)
{
    set_app(app_);
}

void IState::set_app(Application *app_)
{
    app = app_;
}

bool IState::update()
{
    return true;
};