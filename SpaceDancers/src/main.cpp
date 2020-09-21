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
    Application* app = new Application(800, 500, false);
    app->initGame();
    app->startGame();

    delete app;
    return 0;
}

// GameState
// Invader
// VUData
// Ufo
// Player
// Projectile
// Collidable
// Explosion
// Bonus