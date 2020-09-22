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

#define MAX_NUMBER_OF_ITEMS 3

class Menu
{
public:
	Menu(float width, float height);
	~Menu();

	bool startGame;

	void draw(sf::RenderWindow* gameWindow);
	void moveUp();
	void moveDown();
	void update(sf::RenderWindow* gameWindow);
	int getPressedItem() { return selectedItemIndex; }

private:
	int selectedItemIndex;
	sf::Font font;
	sf::Text menuText[MAX_NUMBER_OF_ITEMS];
	sf::Text helpText;
	sf::Texture background;
	sf::Sprite backgroundSprite;


	void initMenuText(int menuTextIndex, float width, float heigth);
};
