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

Menu::Menu(sf::RenderWindow* gameWindow, sf::Font* font) :selectedItemIndex(0), startGame(false), isInMenu(true) {
	this->font = font;
	this->gameWindow = gameWindow;

	//menu background
	if (!this->background.loadFromFile(pathToBackground))
	{
		//texture could not be loaded / found
		std::cout << "Menu Background Texture could not be loaded" << std::endl;
	}
	this->backgroundSprite = sf::Sprite(this->background);
	this->backgroundSprite.setScale(sf::Vector2f((float)this->gameWindow->getSize().x / background.getSize().x, (float)this->gameWindow->getSize().y / background.getSize().y));

	//Help Text
	initText(&this->helpText, "Use Up & Down Arrows to Navigate and Enter to confirm", 24, false, false);
	helpText.setPosition(sf::Vector2f(10, this->gameWindow->getSize().y - 60));

	//Menu Text
	for (int i = 0; i < MAX_NUMBER_OF_ITEMS; i++)
	{
		initText(&this->menuText[i], "init", 40, true, false);
		menuText[i].setPosition(sf::Vector2f(this->gameWindow->getSize().x / 3, this->gameWindow->getSize().y / 3 + i * 80));
	}
	menuText[0].setOutlineColor(sf::Color::Yellow);
	menuText[0].setOutlineThickness(0.8f);
	menuText[0].setString("Play");
	menuText[1].setString("Options");
	menuText[2].setString("Controls");
	menuText[3].setString("Exit");

	//Controlls
	initText(&controlsText, "Right Arrow -> Move Rigth \nLeft Arrow -> Move Left \nSpacebar -> Shoot \nP -> Pause \n\nPress Spacebar to go back",
		40, true, true);
	controlsText.setOutlineColor(sf::Color::Black);
	controlsText.setOutlineThickness(4.0f);
	controlsText.setFillColor(sf::Color::White);

	//Background Music
	this->musicPlayer = new MusicPlayer(90.0f);

	musicPlayer->openMusic(this->pathToMenuMusic, true);
	musicPlayer->playMusic();
}

Menu::~Menu() {
	delete musicPlayer;
}

/// <summary>
/// Draw the menu
/// </summary>
/// <param name="gameWindow"></param>
void Menu::draw(sf::RenderWindow* gameWindow) {
	gameWindow->draw(this->backgroundSprite);
	if (this->isInMenu)
	{
		gameWindow->draw(this->helpText);
		for (int i = 0; i < MAX_NUMBER_OF_ITEMS; i++)
		{
			gameWindow->draw(menuText[i]);
		}
	}
	else
	{
		gameWindow->draw(this->controlsText);
	}
}

/// <summary>
/// Update the menu with user input
/// </summary>
/// <param name="gameWindow"></param>
void Menu::update(sf::RenderWindow* gameWindow) {

	if (this->isInMenu)
	{
		if (InputHandler::isKeyPressed(sf::Keyboard::Up))
		{
			moveUp();
		}
		if (InputHandler::isKeyPressed(sf::Keyboard::Down))
		{
			moveDown();
		}
		if (InputHandler::isKeyPressed(sf::Keyboard::Escape))
		{
			gameWindow->close();
		}
		if (InputHandler::isKeyPressed(sf::Keyboard::Return))
		{
			switch (getPressedItem())
			{
			case 0:
				this->startGame = true;
				this->musicPlayer->stopMusic();
				break;
			case 1:
				std::cout << "Option button has been pressed" << std::endl;
				break;
			case 2:
				std::cout << "Controls button has been pressed" << std::endl;
				this->isInMenu = false;
				break;
			case 3:
				gameWindow->close();
				break;
			}
		}
	}
	else
	{
		if (InputHandler::isKeyPressed(sf::Keyboard::Space))
		{
			isInMenu = true;
		}
	}
}

/// <summary>
/// Move selected menu item up
/// </summary>
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

/// <summary>
/// Move selected menu item down
/// </summary>
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

void Menu::initText(sf::Text* text, std::string string, unsigned int size, bool setOriginToCenter, bool setPositionToCenter)
{
	text->setFont(*this->font);
	text->setString(string);
	text->setCharacterSize(size);

	if (setOriginToCenter)
		text->setOrigin(sf::Vector2f(text->getLocalBounds().width / 2, text->getLocalBounds().height / 2));

	if (setPositionToCenter)
		text->setPosition(sf::Vector2f(this->gameWindow->getSize().x / 2, this->gameWindow->getSize().y / 2));
}