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

Invader::Invader(const char* spritePath) {
	this->invaderTexture = sf::Texture();
	this->invaderTexture.loadFromFile(spritePath);
	this->invaderSprite = sf::Sprite(this->invaderTexture);
}

Invader::~Invader() {

}

void Invader::shoot() {

}

void Invader::move() {
	this->invaderSprite.setPosition(sf::Vector2f(this->invaderSprite.getPosition().x + 0.1, this->invaderSprite.getPosition().y));
}

void Invader::draw(sf::RenderWindow* gameWindow) {
	gameWindow->draw(this->invaderSprite);
}

void Invader::setPosition(sf::Vector2f position) {
	invaderSprite.setPosition(position);