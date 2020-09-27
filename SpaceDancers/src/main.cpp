/////////////////////////////////////
/// 
/// Source File: main.cpp
/// 
/// AUTHOR: Enrico Gamil Toros de Chadarevian
/// MATRNR: 567011
/// CREATE DATE: 9/17/2020 1:58:20 PM
///
/////////////////////////////////////

#include <SFML/Graphics.hpp>
#include "Application.h"

int main()
{
    sf::ContextSettings settings;
    settings.antialiasingLevel = 8;

    Application* app = new Application(1600, 1200, false);
    app->startGame();

    delete app;
    return 0;
}

//TODO
/*
Add Invaders Music Movement
Add Bonuses
Add dificulty in menu?
*/