/////////////////////////////////////
/// 
/// Header File: Menu.h
/// 
/// AUTHOR: Enrico Gamil Toros de Chadarevian
/// MATRNR: 567011
/// CREATE DATE: 9/22/2020 3:30:00 PM
///
/////////////////////////////////////

#pragma once
#include <SFML/Graphics.hpp>
#include "InputHandler.h"
#include "MusicPlayer.h"
#include <iostream>

#define MAX_NUMBER_OF_ITEMS 4

class Menu
{
public:
	Menu(sf::RenderWindow* gameWindow, sf::Font* font);
	~Menu();

	void draw(sf::RenderWindow* gameWindow);
	void moveUp();
	void moveDown();
	void update(sf::RenderWindow* gameWindow);
	int getPressedItem() { return selectedItemIndex; 
	}

	bool startGame;

private:
	void initText(sf::Text* text, std::string string, unsigned int size, bool setOriginToCenter, bool setPositionToCenter);

	int selectedItemIndex;
	sf::Font* font;
	sf::Text menuText[MAX_NUMBER_OF_ITEMS];
	sf::Text helpText;
	sf::Text controlsText;
	sf::Texture background;
	sf::Sprite backgroundSprite;
	sf::RenderWindow* gameWindow;

	bool isInMenu;
	const char* pathToMenuMusic = "res\\music\\space_invaders_track_1.wav";
	const char* pathToBackground = "res\\background.jpg";
	MusicPlayer* musicPlayer;
};
