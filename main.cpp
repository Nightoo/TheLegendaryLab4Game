#include <SFML/Graphics.hpp>
#include <iostream>

using namespace std;
using namespace sf;

class Application;
class SelectLevelState;
class GameState;
class ExitState;
class IState;
class IWindowKeeper;

class IState{
public:
    Application* app;

    IState(Application* app_ = nullptr){
        set_app(app_);
    }

    virtual ~IState() {};

    void set_app(Application* app_){
        app = app_;
    }
    virtual void go_next() = 0;
    virtual bool is_on() = 0;
};

class Application{
public:
    IState* state;
    Application(IState* state_ = nullptr){
        set_next_state(state_);
    }

    ~Application() {delete state;}

    void set_next_state(IState* st){
        //if (state){ delete state;};
        state = st;
        state->set_app(this);
    }

    void change(){
        state->go_next();
    }

    bool active() {return state->is_on();}

    void run() {
        while (state->is_on()) {
            int x;
            cin >> x;
            if (x == 1) {
                state->go_next();
            }
        }
    };
};
class GameState;



class GameState: public IState{
public:
    void go_next() override;
    bool is_on() override{
        cout << "Game" << endl;
        return true;
    }
};

class SelectLevelState: public IState{
public:
    void go_next() override{
        cout << "Select -> Game" << endl;
        app->set_next_state(new GameState);
    }
    bool is_on() override{
        cout << "Select" << endl;
        return true;
    }
};

class ExitState: public IState{
    void go_next() override{
        cout << "Exit!" << endl;
    }
    bool is_on() override{
        cout << "Exit" << endl;
        return false;
    };
};

void GameState::go_next() {
    cout << "Game -> Exit" << endl;
    app->set_next_state(new ExitState);
}



int main() {
    Application app(new SelectLevelState);
    app.run();
    return 0;
}

