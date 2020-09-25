/////////////////////////////////////
/// 
/// Source File: Bullet.cpp
/// 
/// AUTHOR: Enrico Gamil Toros de Chadarevian
/// MATRNR: 567011
/// CREATE DATE: 9/23/2020 5:30:00 PM
///
/////////////////////////////////////

#include "Bullet.h"
/// <summary>
/// Bullet shot by a player
/// </summary>
/// <param name="bulletTexturePath"></param>
/// <param name="xPos">starting x position of the bullet</param>
/// <param name="yPos">starting y position of the bullet</param>
Bullet::Bullet(const char* bulletTexturePath, int xPos, int yPos, int direction, bool isInvaderBullet):bulletSpeed(500)
{
	this->direction = direction;
	//Bullet Texture
	this->bulletTexture = sf::Texture();
	Collision::CreateTextureAndBitmask(bulletTexture, bulletTexturePath);

	//Bullet Sprite
	this->bulletSprite = sf::Sprite(this->bulletTexture);
	this->bulletSprite.setScale(sf::Vector2f(3.0f, 3.0f));
	if (!isInvaderBullet)
		this->bulletSprite.setTextureRect(sf::IntRect(44, 0, 11, 8));
	else
		this->bulletSprite.setTextureRect(sf::IntRect(34, 0, 11, 8));

	this->bulletSprite.setOrigin(sf::Vector2f(bulletSprite.getLocalBounds().width / 2, bulletSprite.getLocalBounds().height / 2));
	this->bulletSprite.setPosition(sf::Vector2f(xPos, yPos));
}

Bullet::~Bullet()
{
}

/// <summary>
/// Updates the Bullet position
/// </summary>
/// <param name="deltaTime"></param>
/// <param name="gameWindow"></param>
/// <returns>True if bullet is outside of Window</returns>
bool Bullet::update(float deltaTime, sf::RenderWindow* gameWindow)
{
	if (this->bulletSprite.getPosition().y > 0)
	{
		this->bulletSprite.setPosition(sf::Vector2f(this->bulletSprite.getPosition().x,
			this->bulletSprite.getPosition().y - (this->bulletSpeed * deltaTime) * this->direction));
		return false;
	}
	else
	{
		return true;
	}
}

/// <summary>
/// Draw Method of Bullet
/// </summary>
/// <param name="gameWindow"></param>
void Bullet::draw(sf::RenderWindow* gameWindow)
{
	gameWindow->draw(this->bulletSprite);
}

/// <summary>
/// Returns the Position of the bullet as a Vector2f
/// </summary>
/// <returns></returns>
sf::Vector2f Bullet::getPosition()
{
	return this->bulletSprite.getPosition();
}
