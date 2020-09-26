#include "GameOver.h"

GameOver::GameOver(sf::RenderWindow* gameWindow, int score): restart(false)
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
	gameOverText = sf::Text();
	gameOverText.setFont(this->pixelFont);
	scoreText = sf::Text();
	scoreText.setFont(this->pixelFont);
	helpText = sf::Text();
	helpText.setFont(this->pixelFont);

	gameOverText.setString(std::string("Game Over"));
	gameOverText.setCharacterSize(100);
	gameOverText.setOrigin(sf::Vector2f(gameOverText.getLocalBounds().width / 2, gameOverText.getLocalBounds().height / 2));
	gameOverText.setPosition(sf::Vector2f(gameWindow->getSize().x / 2, gameWindow->getSize().y / 2 - 40));

	scoreText.setString(std::string("Your Score: " + std::to_string(score)));
	scoreText.setCharacterSize(40);
	scoreText.setOrigin(sf::Vector2f(scoreText.getLocalBounds().width / 2, scoreText.getLocalBounds().height / 2));
	scoreText.setPosition(sf::Vector2f(gameWindow->getSize().x / 2,
		gameWindow->getSize().y / 2 + gameOverText.getGlobalBounds().height));

	helpText.setString(std::string("Press Enter to Play again"));
	helpText.setCharacterSize(30);
	helpText.setOrigin(sf::Vector2f(helpText.getLocalBounds().width / 2, helpText.getLocalBounds().height / 2));
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
