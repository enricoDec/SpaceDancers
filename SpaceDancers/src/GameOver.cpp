#include "GameOver.h"

GameOver::GameOver(sf::RenderWindow* gameWindow, int score) : restart(false)
{
	this->gameWindow = gameWindow;

	//init font
	this->pixelFont = sf::Font();
	if (!pixelFont.loadFromFile(this->pixelFontPath))
	{
		//Invader Font could not be loaded / found
		std::cout << "Font could not be loaded" << std::endl;
	}

	//Init game over text
	initText(&this->gameOverText, "Game Over", 100, true, false);
	gameOverText.setPosition(sf::Vector2f(gameWindow->getSize().x / 2, gameWindow->getSize().y / 2 - 40));

	initText(&this->scoreText, std::string("Your Score: " + std::to_string(score)), 40, true, false);
	scoreText.setPosition(sf::Vector2f(gameWindow->getSize().x / 2,
		gameWindow->getSize().y / 2 + gameOverText.getGlobalBounds().height));

	initText(&this->helpText, "Press Enter to play again", 30, true, false);
	helpText.setPosition(sf::Vector2f(gameWindow->getSize().x / 2, gameWindow->getSize().y - helpText.getLocalBounds().height - 20));
}

GameOver::~GameOver()
{
}

void GameOver::update()
{
	if (InputHandler::isKeyPressed(sf::Keyboard::Enter))
	{
		this->restart = true;
	}
}

void GameOver::render()
{
	this->gameWindow->draw(this->gameOverText);
	this->gameWindow->draw(this->scoreText);
	this->gameWindow->draw(this->helpText);
}

void GameOver::initText(sf::Text* text, std::string string, unsigned int size, bool setOriginToCenter, bool setPositionToCenter)
{

	text->setFont(this->pixelFont);
	text->setString(string);
	text->setCharacterSize(size);

	if (setOriginToCenter)
		text->setOrigin(sf::Vector2f(text->getLocalBounds().width / 2, text->getLocalBounds().height / 2));

	if (setPositionToCenter)
		text->setPosition(sf::Vector2f(this->gameWindow->getSize().x / 2, this->gameWindow->getSize().y / 2));
}
