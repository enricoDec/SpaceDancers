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
#include <iostream>

Invader::Invader(const char* spritePath, int rowNumber, int invaderType) :animationState(0), speed(60),
rowHeigth(60) {

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

void Invader::shoot() {
}

void Invader::move(float deltaTime, sf::RenderWindow* gameWindow, std::vector<Invader*> invaderList, int borderOffset, int mostLeftInvaderIndex, int mostRightInvaderIndex) {
	//std::cout << "(" << gameWindow->getSize().x << ")" << " (" << invaderSprite.getPosition().x << ")" << std::endl;
	//std::cout << "(" << this->invaderSprite.getPosition().x << ")" << "(" << this->invaderSprite.getPosition().y << ")" << std::endl;
	//std::cout << deltaTime << std::endl;

	if ((invaderList.at(mostRightInvaderIndex)->invaderSprite.getPosition().x + borderOffset >= gameWindow->getSize().x)
		|| (invaderList.at(mostLeftInvaderIndex)->invaderSprite.getPosition().x - borderOffset <= 0))
	{
		moveRow(invaderList);
	}

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

void Invader::moveRow(std::vector<Invader*> invaderList)
{
	for (int i = 0; i < invaderList.size(); i++) {
		invaderList.at(i)->speed = invaderList.at(i)->speed * -1;
		invaderList.at(i)->setPosition(sf::Vector2f(invaderList.at(i)->invaderSprite.getPosition().x,
			invaderList.at(i)->invaderSprite.getPosition().y + this->rowHeigth));
	}
}

void Invader::draw(sf::RenderWindow* gameWindow) {
	gameWindow->draw(this->invaderSprite);
}

void Invader::setPosition(sf::Vector2f position) {
	this->invaderSprite.setPosition(position);
}

void Invader::spriteAnimation() {
	this->animationState = !this->animationState;
	this->invaderSprite.setTextureRect(sf::IntRect(10 * animationState + invaderType * 20, 0, 10, 8));
}
