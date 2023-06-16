#pragma once

#include <SFML/Graphics.hpp>
#include <string>
#include <iostream>
#include "Game/State/IState.hpp"
#include "Game/State/ExitState.hpp"
#include "Game/Component/IWindowKeeper.hpp"
#include "Game/Object/Room.hpp"
#include "Game/Object/Player.hpp"
#include "Game/Object/Enemy.hpp"
#include "Game/Object/Chest.hpp"
#include "Definitions.hpp"
#include <unistd.h>

class GameState : public IState, public IWindowKeeper
{
public:
    Application *app;
    Room *room;
    Player *player;
    Enemy* enemies[10];
    Chest* chest;
    sf::Texture heart_t;
    sf::Texture bomb_t;
    sf::Texture key_t;
    sf::Sprite hearts[LIVES];
    sf::Sprite bombs[BOMBS];
    sf::Sprite key;
    int ENEMY_NUMBER;
    bool win;

    GameState(
        Application *app_,
        std::string mode_ = "mode",
        std::string title_ = "title")
        : IWindowKeeper(mode_, title_)
        {
        this->app = app_;
        this->window = new sf::RenderWindow(sf::VideoMode(GAME_WIDTH, GAME_HEIGHT), "Game");
        this->room = new Room();
        this->player = new Player(room);
        this->chest = new Chest(room);
        this->win = false;

        heart_t.loadFromFile("heart.png");
        bomb_t.loadFromFile("bomb.png");
        key_t.loadFromFile("key.png");
        key.setTexture(key_t);

        for(int i = 0; i < LIVES; i++){
            hearts[i].setTexture(heart_t);
            hearts[i].setPosition(sf::Vector2f(GAME_WIDTH - INDICATOR_SIZE, i * INDICATOR_SIZE));
            window->draw(hearts[i]);
        }

        for(int i = 0; i < BOMBS; i++){
            bombs[i].setTexture(bomb_t);
            bombs[i].setPosition(sf::Vector2f(GAME_WIDTH - INDICATOR_SIZE, GAME_HEIGHT - (i + 1) * INDICATOR_SIZE));
            window->draw(bombs[i]);
        }

        key.setPosition(sf::Vector2f(GAME_WIDTH - INDICATOR_SIZE, GAME_HEIGHT / 2 - INDICATOR_SIZE / 2));

        mode = mode_;

        if (mode == "easy"){
            ENEMY_NUMBER = 0;
        }
        if (mode == "medium"){
            ENEMY_NUMBER = 4;
        }
        if (mode == "hard"){
            ENEMY_NUMBER = 10;
        }
        for (int i = 0; i < ENEMY_NUMBER; i++){
            enemies[i] = new Enemy(room);
        }
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

    void indicators(){
        for(int i = 0; i < player->ammo; i++){
            bombs[i].setTexture(bomb_t);
            bombs[i].setPosition(sf::Vector2f(GAME_WIDTH - INDICATOR_SIZE, GAME_HEIGHT - (i + 1) * INDICATOR_SIZE));
            window->draw(bombs[i]);
        }
        for(int i = 0; i < player->lives; i++){
            hearts[i].setTexture(heart_t);
            hearts[i].setPosition(sf::Vector2f(GAME_WIDTH - INDICATOR_SIZE, i * INDICATOR_SIZE));
            window->draw(hearts[i]);
        }
        if (player->have_key){
            window->draw(key);
        }
    }

    void shooting(){
        if (player->ammo >= 1) {
            player->shoot();
            for (int i = 0; i < ENEMY_NUMBER; i++) {
                if (abs(enemies[i]->position_x - player->position_x) <= 2 &&
                    abs(enemies[i]->position_y - player->position_y) <= 2) {
                    delete enemies[i];
                }
            }
            sf::Texture boom_t;
            sf::Sprite boom;
            boom_t.loadFromFile("boom.png");
            boom.setTexture(boom_t);
            boom.setPosition(sf::Vector2f((player->position_x - 2) * TEXTURE_SIZE, (player->position_y - 2) * TEXTURE_SIZE));
            window->draw(boom);
            indicators();
            window->display();
            sleep(1);
        }
    }

    bool update() override {
        sf::Event event;
        while (window->pollEvent(event)) {
            window->clear();
            render();
            if (event.type == sf::Event::KeyPressed) {
                for (int i = 0; i < ENEMY_NUMBER; i++){
                    enemies[i]->move(player);
                }

                if (event.key.code == sf::Keyboard::W) { player->move_up(); }
                if (event.key.code == sf::Keyboard::A) { player->move_left(); }
                if (event.key.code == sf::Keyboard::S) { player->move_down(); }
                if (event.key.code == sf::Keyboard::D) { player->move_right(); }
                if (event.key.code == sf::Keyboard::Space) {shooting();}
                if (event.key.code == sf::Keyboard::Escape) {return false;}

            }
            if (player->lives < 1){
                return false;
            }
            if (player->win){
                win = true;
                return false;
            }
            indicators();
            window->display();
        }
        return true;
    }

    void go_next() override
    {
        std::cout << "Game -> Exit" << std::endl;
        app->set_next_state(new ExitState(app, win));
    }

    bool is_on() override
    {
        return true;
    }
};
