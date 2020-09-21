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

Invader::Invader(const char* spritePath):animationState(0) {
	this->invaderTexture = sf::Texture();
	this->invaderTexture.loadFromFile(spritePath);
	this->invaderSprite = sf::Sprite(this->invaderTexture);
	this->invaderSprite.setTextureRect(sf::IntRect(0, 0, 11, 8));
	this->invaderSprite.setScale(sf::Vector2f(3.0f,3.0f));
}

Invader::~Invader() {

}

void Invader::shoot() {

}

void Invader::move(float deltaTime) { 
	this->invaderSprite.setPosition(sf::Vector2f(this->invaderSprite.getPosition().x + 15 * deltaTime, this->invaderSprite.getPosition().y));
}

void Invader::draw(sf::RenderWindow* gameWindow) {
	gameWindow->draw(this->invaderSprite);
}

void Invader::setPosition(sf::Vector2f position) {
	this->invaderSprite.setPosition(position);
}

void Invader::spriteAnimation(){
	this->animationState = !this->animationState;
	this->invaderSprite.setTextureRect(sf::IntRect(11 * animationState, 0, 11, 8));
}
