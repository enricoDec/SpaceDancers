/////////////////////////////////////
/// 
/// Source File: Invader.cpp
/// 
/// AUTHOR: Enrico Gamil Toros de Chadarevian
/// MATRNR: 567011
/// CREATE DATE: 9/17/2020 6:34:16 PM
///
/////////////////////////////////////
#include "Invader.h"

Invader::Invader(const char* spritePath, int rowNumber, int invaderType, int speed): animationState(0),
rowHeigth(60) {
	this->speed = speed;
	this->rowNumber = rowNumber;
	this->invaderType = invaderType;
	this->invaderTexture = sf::Texture();
	if (!this->invaderTexture.loadFromFile(spritePath))
	{
		// Texture could not be found
		std::cout << "Invader Texture could not be loaded" << std::endl;
	}

	Collision::CreateTextureAndBitmask(invaderTexture, spritePath);
	this->invaderSprite = sf::Sprite(this->invaderTexture);
	this->invaderSprite.setTextureRect(sf::IntRect(invaderType * 20, 0, 10, 8));
	this->invaderSprite.setScale(sf::Vector2f(3.5f, 3.5f));
	this->invaderSprite.setOrigin(sf::Vector2f(this->invaderSprite.getLocalBounds().width / 2,
		this->invaderSprite.getLocalBounds().height / 2));
}

Invader::~Invader() {
}

/// <summary>
/// Moves an invader to the right and left and down if the window border has been reached
/// Should be called each frame update
/// </summary>
/// <param name="deltaTime">time difference since last frame</param>
/// <param name="gameWindow"></param>
/// <param name="invaderList">list of all the invaders</param>
/// <param name="borderOffset">window border offset</param>
/// <param name="mostLeftInvaderIndex">index of the most left invader in all rows</param>
/// <param name="mostRightInvaderIndex">index of the most right invader in all rows</param>
void Invader::move(float deltaTime, sf::RenderWindow* gameWindow, std::vector<Invader*> invaderList, 
	int borderOffset, int mostLeftInvaderIndex, int mostRightInvaderIndex) {

	//if most right or left invader reached the border of the window move all the rows down
	if ((invaderList.at(mostRightInvaderIndex)->invaderSprite.getPosition().x + borderOffset >= gameWindow->getSize().x)
		|| (invaderList.at(mostLeftInvaderIndex)->invaderSprite.getPosition().x - borderOffset <= 0))
	{
		moveRow(invaderList);
	}

	//move all the invaders left or right
	for (int i = 0; i < invaderList.size(); i++)
	{
		// Prevent invaders getting "stuck" between border and permanently falling down
		float x = invaderList.at(i)->invaderSprite.getPosition().x + speed * deltaTime;

		if (x - borderOffset <= 0)
			invaderList.at(i)->invaderSprite.setPosition(sf::Vector2f(borderOffset,
				invaderList.at(i)->invaderSprite.getPosition().y));
		else if (x + borderOffset >= gameWindow->getSize().x)
			invaderList.at(i)->invaderSprite.setPosition(sf::Vector2f(gameWindow->getSize().x - borderOffset,
				invaderList.at(i)->invaderSprite.getPosition().y));
		else
			invaderList.at(i)->invaderSprite.setPosition(sf::Vector2f(x, invaderList.at(i)->invaderSprite.getPosition().y));
	}
}

/// <summary>
/// Moves all invaders one row down
/// </summary>
/// <param name="invaderList"></param>
void Invader::moveRow(std::vector<Invader*> invaderList)
{
	for (int i = 0; i < invaderList.size(); i++) {
		invaderList.at(i)->speed = invaderList.at(i)->speed * -1;
		invaderList.at(i)->setPosition(sf::Vector2f(invaderList.at(i)->invaderSprite.getPosition().x,
			invaderList.at(i)->invaderSprite.getPosition().y + this->rowHeigth));
	}
}

/// <summary>
/// Draws the invaders in the given window
/// </summary>
/// <param name="gameWindow"></param>
void Invader::draw(sf::RenderWindow* gameWindow) {
	gameWindow->draw(this->invaderSprite);

	 
}

/// <summary>
/// Sets the position of the invaders
/// </summary>
/// <param name="position"></param>
void Invader::setPosition(sf::Vector2f position) {
	this->invaderSprite.setPosition(position);
}

/// <summary>
/// Changes the invader sprite to make an animation
/// </summary>
void Invader::spriteAnimation() {
	this->animationState = !this->animationState;
	this->invaderSprite.setTextureRect(sf::IntRect(10 * animationState + invaderType * 20, 0, 10, 8));
}
