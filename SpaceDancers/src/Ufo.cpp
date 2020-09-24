/////////////////////////////////////
/// 
/// Source File: Ufo.cpp
/// 
/// AUTHOR: Enrico Gamil Toros de Chadarevian
/// MATRNR: 567011
/// CREATE DATE: 9/22/2020 2:30:00 AM
///
/////////////////////////////////////
#include "Ufo.h"

Ufo::Ufo(int speed, const char* ufoTexturePath, sf::RenderWindow* gameWindow)
{
	this->ufoTexture = sf::Texture();
	if (!this->ufoTexture.loadFromFile(ufoTexturePath))
	{
		// Texture could not be found
		std::cout << "Invader Texture could not be loaded" << std::endl;
	}

	this->speed = speed;
	Collision::CreateTextureAndBitmask(ufoTexture, ufoTexturePath);
	this->ufoSprite = sf::Sprite(this->ufoTexture);
	this->ufoSprite.setTextureRect(sf::IntRect(60, 0, 16, 8));
	this->ufoSprite.setScale(sf::Vector2f(3.5f, 3.5f));
	this->ufoSprite.setOrigin(sf::Vector2f(this->ufoSprite.getLocalBounds().width / 2,
		this->ufoSprite.getLocalBounds().height / 2));
	this->ufoSprite.setPosition(sf::Vector2f(gameWindow->getSize().x, this->ufoSprite.getGlobalBounds().height + 50));

	//Ufo sound
	this->musicPlayer = new MusicPlayer();
	musicPlayer->openMusic(ufoSoundPath, false);
	musicPlayer->playMusic();
}

Ufo::~Ufo()
{
	delete musicPlayer;
}

/// <summary>
/// Update ufo position
/// </summary>
/// <param name="gameWindow"></param>
/// <param name="deltaTime"></param>
void Ufo::update(sf::RenderWindow* gameWindow, float deltaTime)
{
	this->ufoSprite.setPosition(sf::Vector2f(this->ufoSprite.getPosition().x - speed * deltaTime, 
		this->ufoSprite.getPosition().y));
}

/// <summary>
/// Draw ufo on screen
/// Call on render
/// </summary>
/// <param name="gameWindow"></param>
void Ufo::draw(sf::RenderWindow* gameWindow)
{
	gameWindow->draw(this->ufoSprite);
} 
