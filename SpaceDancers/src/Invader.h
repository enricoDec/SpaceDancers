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
	Invader(const char* spritePath);
	~Invader();

	void move();
	void shoot();
	void draw(sf::RenderWindow* gameWindow);
	void setPosition(sf::Vector2f position);

private:
	int speed;
	sf::Sprite invaderSprite;
	sf::Texture invaderTexture;
};
