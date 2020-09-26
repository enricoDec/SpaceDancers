/////////////////////////////////////
/// 
/// Header File: GameOver.h
/// 
/// AUTHOR: Enrico Gamil Toros de Chadarevian
/// MATRNR: 567011
/// CREATE DATE: 9/26/2020 2:29:12 PM
///
/////////////////////////////////////

#pragma once

#include <SFML/Graphics.hpp>
#include "InputHandler.h"
#include <iostream>

class GameOver
{
public:
	GameOver(sf::RenderWindow* gameWindow, int score);
	~GameOver();

	void update();
	void render();

	bool restart;

private:
	sf::Font pixelFont;
	sf::Text gameOverText;
	sf::Text scoreText;
	sf::Text helpText;

	const char* pixelFontPath = "res\\fonts\\invader.ttf";

	sf::RenderWindow* gameWindow;
};