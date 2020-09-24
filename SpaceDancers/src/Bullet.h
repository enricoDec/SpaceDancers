/////////////////////////////////////
/// 
/// Header File: Bullet.h
/// 
/// AUTHOR: Enrico Gamil Toros de Chadarevian
/// MATRNR: 567011
/// CREATE DATE: 9/23/2020 5:30:00 PM
///
/////////////////////////////////////
#pragma once

#include <SFML/Graphics.hpp>
#include "Collision.h"

class Bullet
{
public:
	Bullet(const char* bulletTexturePath, int xPos, int yPos);
	~Bullet();

	bool update(float deltaTime, sf::RenderWindow* gameWindow);
	void draw(sf::RenderWindow* gameWindow);
	sf::Vector2f getPosition();
	sf::Sprite getSprite();


private:
	sf::Sprite bulletSprite;
	sf::Texture bulletTexture;
	int bulletSpeed;
};