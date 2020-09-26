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
#include "Collision.h"
#include <iostream>
#include "Bullet.h"

class Invader
{
public:
	int rowHeigth;
	int rowNumber;
	sf::Sprite invaderSprite;

	Invader(const char* spritePath, int rowNumber, int invaderType, int speed);
	~Invader();

	void move(float deltaTime, sf::RenderWindow* gameWindow, std::vector<Invader*> invaderList, 
		int borderOffset, int mostLeftInvaderIndex, int mostRightInvaderIndex);
	void draw(sf::RenderWindow* gameWindow);
	void setPosition(sf::Vector2f position);
	void spriteAnimation();

private:
	int speed;
	int invadersPerRow;
	int animationState;
	int invaderType;
	sf::Texture invaderTexture;

	void moveRow(std::vector<Invader*> invaderList);
};
