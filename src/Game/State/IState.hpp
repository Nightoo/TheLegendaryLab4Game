#pragma once

class Application;

class IState
{
public:
    Application *app;

    IState(Application *app_ = nullptr);

    virtual ~IState() = default;

    void set_app(Application *app_);
    virtual void go_next() = 0;
    virtual bool is_on() = 0;
    virtual bool update();
};
