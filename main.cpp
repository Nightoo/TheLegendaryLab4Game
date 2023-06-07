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
    virtual bool update() {return true;};
};

class Application{
public:
    IState* state = nullptr;
    Application(IState* state_ = nullptr) {
        set_next_state(state_);
    }

    ~Application() {delete state;}

    void set_next_state(IState* st){
        //if (state) delete state;
        state = st;
        state->set_app(this);
    }

    void change(){
        state->go_next();
    }

    bool active() {return state->is_on();}

    void run() {
        while (active()) {
            if(!state->update()){
                state->go_next();
            };
            }
        }
};

class IWindowKeeper {
public:
    string mode;
    string title;
    RenderWindow* window;
    IWindowKeeper(string mode_ = "mode", string title_ = "title"){
        this->window = nullptr;
        mode = mode_;
        title = title_;
    }
protected:
    virtual void event_handling() {};
    virtual void render() {};
};


class GameState;

class Room{
public:
    CircleShape polygon;
    Room() {
        polygon = CircleShape(100,9);
        polygon.setFillColor(Color::Yellow);
        polygon.setPosition(Vector2f(400, 0));
    }
};


class GameState: public IState, public IWindowKeeper{
public:
    Application* app;
    string mode;
    string title;
    RenderWindow* window;
    Room* room;
    GameState(Application* app_ = nullptr, string mode_ = "mode", string title_ = "title"){
        this->window = new RenderWindow(VideoMode(600, 600), "Game");
        this->room = new Room();
        this->render();
    }

    void render() override{
        window->draw(room->polygon);
    }

    bool update() override{
        window->clear();
        window->draw(room->polygon);
        window->display();
        return true;
    }

    void go_next() override;
    bool is_on() override{
        cout << "Game" << endl;
        return true;
    }
};

class Button{
public:
    RectangleShape button;
    Text text;
    Color color;
    RectangleShape select_shape;
    bool selected = false;
    Button(string txt = "level", Color color_ = Color::Red, Vector2f pos = Vector2f(100, 50), Vector2f size = Vector2f(150, 100)){
        button = RectangleShape(size);
        color = color_;
        button.setFillColor(color);
        button.setPosition(pos);
        Font font;
        if (!font.loadFromFile("c:/windows/fonts/arial.ttf")){
            cout << "___";
        }
        text.setFont(font);
        text.setString("txt");
        text.setCharacterSize(30);
        text.setFillColor(Color::White);
        text.setPosition(pos);
        select_shape = RectangleShape(Vector2f(size.x + 20, size.y + 20));
        select_shape.setFillColor(Color::Yellow);
        select_shape.setPosition(Vector2f(pos.x-10, pos.y-10));

    }
    void show(RenderWindow* window){
        if (selected){
            window->draw(select_shape);
        }
        window->draw(button);
    }

    void select(){
        selected = true;
    }

    void unselect(){
        selected = false;
    }
};

class Menu{
public:
    Button easy;
    Button medium;
    Button hard;
    Menu(){
        easy = Button("EASY", Color(0, 100, 255));
        medium = Button("MEDIUM", Color(0, 100, 255), Vector2f(100, 200));
        hard = Button("HARD",Color(0, 100, 255), Vector2f(100, 350));
    }
};

class SelectLevelState: public IState, public IWindowKeeper{
public:
    Application* app;
    string mode;
    string title;
    RenderWindow* window;
    Menu* menu;
    SelectLevelState(Application* app_ = nullptr, string mode_ = "mode", string title_ = "title"){
        this->window = new RenderWindow(VideoMode(400, 600), "Select");
        this->menu = new Menu();
        //this->render();
    }

    void go_next() override{
        window->clear();
        window->close();
        cout << "Select -> Game" << endl;
        app->set_next_state(new GameState);
    }
    bool is_on() override{
        cout << "Select" << endl;
        return true;
    }

    void render() override{
        menu->easy.show(window);
        menu->medium.show(window);
        menu->hard.show(window);
    }


    bool update() override{
        window->clear();
        /*menu->square.move(0, 0.01);
        if (menu->square.getGlobalBounds().intersects(menu->square2.getGlobalBounds())){
            return false;
        }
        window->draw(menu->square);
        window->draw(menu->square2);
        window->display();*/
        if (Keyboard::isKeyPressed(Keyboard::E)) { menu->easy.select();menu->medium.unselect();menu->hard.unselect(); }
        if (Keyboard::isKeyPressed(Keyboard::M)) { menu->medium.select();menu->easy.unselect();menu->hard.unselect(); }
        if (Keyboard::isKeyPressed(Keyboard::H)) { menu->hard.select();menu->easy.unselect(); menu->medium.unselect(); }
        menu->easy.show(window);
        menu->medium.show(window);
        menu->hard.show(window);
        window->display();
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

