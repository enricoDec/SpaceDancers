/////////////////////////////////////
/// 
/// Source File: Menu.cpp
/// 
/// AUTHOR: Enrico Gamil Toros de Chadarevian
/// MATRNR: 567011
/// CREATE DATE: 9/22/2020 3:30:00 PM
///
/////////////////////////////////////

#include "Menu.h" 
#include <iostream>

Menu::Menu(float width, float height) :selectedItemIndex(0), startGame(false) {
	//load font
	if (!font.loadFromFile("C:\\Users\\Enrico\\Desktop\\SpaceDancers\\SpaceDancers\\bin\\Debug\\x64\\res\\fonts\\arial.ttf"))
	{
		//handle error
		std::cout << "Font could not be loaded" << std::endl;
	}

	//menu background
	this->background.loadFromFile("C:\\Users\\Enrico\\Desktop\\SpaceDancers\\SpaceDancers\\bin\\Debug\\x64\\res\\background.jpg");
	this->backgroundSprite = sf::Sprite(this->background);

	//Help Text
	helpText.setFont(font);
	helpText.setString("Use Up & Down Arrows to Navigate and Enter to confirm");
	helpText.setFillColor(sf::Color::White);
	helpText.setPosition(sf::Vector2f(0, height - 50));

	menuText[0].setCharacterSize(menuText[0].getCharacterSize() + 10);
	menuText[0].setOutlineColor(sf::Color::Yellow);
	menuText[0].setOutlineThickness(0.8f);
	menuText[0].setString("Play");

	initMenuText(0, width, height);
	initMenuText(1, width, height);
	initMenuText(2, width, height);

	menuText[1].setString("Options");
	menuText[2].setString("Exit");
}

Menu::~Menu() {
}

void Menu::initMenuText(int menuTextIndex, float width, float height) {
	menuText[menuTextIndex].setFont(font);
	menuText[menuTextIndex].setFillColor(sf::Color::White);
	menuText[menuTextIndex].setPosition(sf::Vector2f(width / 3, (height / 5) + 50 * (menuTextIndex + 1)));
}

void Menu::draw(sf::RenderWindow* gameWindow) {
	gameWindow->draw(this->backgroundSprite);
	gameWindow->draw(this->helpText);
	for (int i = 0; i < MAX_NUMBER_OF_ITEMS; i++)
	{
		gameWindow->draw(menuText[i]);
	}
}

void Menu::update(sf::RenderWindow* gameWindow) {

	if (InputHandler::isKeyPressed(sf::Keyboard::Up))
	{
		moveUp();
	}
	if (InputHandler::isKeyPressed(sf::Keyboard::Down))
	{
		moveDown();
	}
	if (InputHandler::isKeyPressed(sf::Keyboard::Return))
	{
		switch (getPressedItem())
		{
		case 0:
			std::cout << "Play button has been pressed" << std::endl;
			startGame = true;
			break;
		case 1:
			std::cout << "Option button has been pressed" << std::endl;
			break;
		case 2:
			gameWindow->close();
			break;
		}
	}
}

void Menu::moveUp() {
	if (selectedItemIndex - 1 >= 0)
	{
		menuText[selectedItemIndex].setCharacterSize(menuText[selectedItemIndex].getCharacterSize() - 10);
		menuText[selectedItemIndex].setOutlineThickness(0.0f);
		selectedItemIndex--;
		menuText[selectedItemIndex].setCharacterSize(menuText[selectedItemIndex].getCharacterSize() + 10);
		menuText[selectedItemIndex].setOutlineColor(sf::Color::Yellow);
		menuText[selectedItemIndex].setOutlineThickness(0.8f);
	}
}

void Menu::moveDown() {
	if (selectedItemIndex + 1 < MAX_NUMBER_OF_ITEMS)
	{
		menuText[selectedItemIndex].setCharacterSize(menuText[selectedItemIndex].getCharacterSize() - 10);
		menuText[selectedItemIndex].setOutlineThickness(0.0f);
		selectedItemIndex++;
		menuText[selectedItemIndex].setCharacterSize(menuText[selectedItemIndex].getCharacterSize() + 10);
		menuText[selectedItemIndex].setOutlineColor(sf::Color::Yellow);
		menuText[selectedItemIndex].setOutlineThickness(0.8f);
	}
}