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

Menu::Menu(float width, float height, sf::Font* font) :selectedItemIndex(0), startGame(false), isInMenu(true) {
	this->font = font;

	//menu background
	if (!this->background.loadFromFile(pathToBackground))
	{
		//texture could not be loaded / found
		std::cout << "Menu Background Texture could not be loaded" << std::endl;
	}
	this->backgroundSprite = sf::Sprite(this->background);
	this->backgroundSprite.setScale(sf::Vector2f(width / background.getSize().x, height / background.getSize().y));

	//Help Text
	helpText.setFont(*this->font);
	helpText.setCharacterSize(helpText.getCharacterSize() - 6);
	helpText.setString("Use Up & Down Arrows to Navigate and Enter to confirm");
	helpText.setFillColor(sf::Color::White);
	helpText.setPosition(sf::Vector2f(10, height - 50));

	//Menu Text
	menuText[0].setOutlineColor(sf::Color::Yellow);
	menuText[0].setOutlineThickness(0.8f);
	menuText[0].setString("Play");
	menuText[0].setCharacterSize(menuText[0].getCharacterSize() + 10);

	menuText[1].setString("Options");
	menuText[2].setString("Controls");
	menuText[3].setString("Exit");

	initMenuText(0, width, height);
	initMenuText(1, width, height);
	initMenuText(2, width, height);
	initMenuText(3, width, height);

	//Controlls
	controlsText.setString("Right Arrow -> Move Rigth \nLeft Arrow -> Move Left \nSpacebar -> Shoot \nP -> Pause \n\nPress Spacebar to go back");
	controlsText.setFont(*font);
	controlsText.setOutlineColor(sf::Color::Black);
	controlsText.setOutlineThickness(4.0f);
	controlsText.setCharacterSize(controlsText.getCharacterSize() + 10);
	controlsText.setFillColor(sf::Color::White);
	controlsText.setOrigin(sf::Vector2f(controlsText.getLocalBounds().width / 2, controlsText.getLocalBounds().height / 2));
	controlsText.setPosition(sf::Vector2f(width / 2, height / 2));

	//Background Music
	this->musicPlayer = new MusicPlayer();

	musicPlayer->openMusic(this->pathToMenuMusic, true);
	musicPlayer->playMusic();
}

Menu::~Menu() {
	delete musicPlayer;
}

//helper method
void Menu::initMenuText(int menuTextIndex, float width, float height) {
	menuText[menuTextIndex].setFont(*font);
	menuText[menuTextIndex].setFillColor(sf::Color::White);
	menuText[menuTextIndex].setCharacterSize(menuText[menuTextIndex].getCharacterSize() + 10);
	menuText[menuTextIndex].setPosition(sf::Vector2f(width / 3, height / 3 + menuTextIndex * 80));
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
				std::cout << "Play button has been pressed" << std::endl;
				startGame = true;
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