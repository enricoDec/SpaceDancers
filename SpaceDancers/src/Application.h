/////////////////////////////////////
/// 
/// Header File: Application.h
/// 
/// AUTHOR: Enrico Gamil Toros de Chadarevian
/// MATRNR: 567011
/// CREATE DATE: 9/17/2020 1:58:20 PM
///
/////////////////////////////////////

#pragma once
#include <SFML/Graphics.hpp>

class Application {
public:
	Application(unsigned int windowWidth, unsigned int windowHeight, bool isFullScreen);
	~Application();
	
	void initGame();
	void startGame();
private:
	sf::RenderWindow gameWindow;
};