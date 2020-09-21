/////////////////////////////////////
/// 
/// Header File: Invader.h
/// 
/// AUTHOR: Enrico Gamil Toros de Chadarevian
/// MATRNR: 567011
/// CREATE DATE: 9/17/2020 6:34:16 PM
///
/////////////////////////////////////

#pragma once
#include <SFML/Graphics.hpp>

class Invader
{
public:
	Invader(const char* spritePath, int rowNumber);
	~Invader();

	void move(float deltaTime, sf::RenderWindow* gameWindow, std::vector<Invader*> invaderList, int borderOffset);
	void shoot();
	void draw(sf::RenderWindow* gameWindow);
	void setPosition(sf::Vector2f position);
	void spriteAnimation();

private:
	int speed;
	int rowHeigth;
	int rowNumber;
	int animationState;
	sf::Sprite invaderSprite;
	sf::Texture invaderTexture;

	void moveRow(std::vector<Invader*> invaderList);
};
