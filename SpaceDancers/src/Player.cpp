/////////////////////////////////////
/// 
/// Source File: Player.cpp
/// 
/// AUTHOR: Enrico Gamil Toros de Chadarevian
/// MATRNR: 567011
/// CREATE DATE: 9/23/2020 6:46:01 PM
///
/////////////////////////////////////

#include "Player.h"

Player::Player(sf::Font* pixelFont, const char* spriteSheetPath, sf::RenderWindow* gameWindow) :lives(3), score(0),
exploded(false), minPlayerMovementSpeed(400), bulletCoolDown(0.4f)
{
	this->gameWindow = gameWindow;
	this->pixelFont = pixelFont;
	this->playerSpritePath = spriteSheetPath;
	this->playerTexture = sf::Texture();
	if (!this->playerTexture.loadFromFile(this->playerSpritePath))
	{
		// Texture could not be found
		std::cout << "Player Texture could not be loaded" << std::endl;
	}

	//Init player Sprite
	this->playerSprite = sf::Sprite(this->playerTexture);
	this->playerSprite.setScale(sf::Vector2f(5.0f, 5.0f));
	this->playerSprite.setTextureRect(sf::IntRect(0, 0, 11, 8));
	this->playerSprite.setOrigin(sf::Vector2f(this->playerSprite.getLocalBounds().width / 2,
		this->playerSprite.getLocalBounds().height / 2));
	this->playerSprite.setPosition(sf::Vector2f(this->gameWindow->getSize().x / 2,
		this->gameWindow->getSize().y - this->playerSprite.getGlobalBounds().height / 2));

	//clock that handles cooldown between shots
	clock.restart();

	//Obejct to handle sound
	this->musicPlayer = new MusicPlayer(20.0f);

	//init player score and lives
	playerGui();
}

Player::~Player()
{
	if (!bulletList.empty())
	{
		for (int i = 0; i < bulletList.size(); i++)
		{
			delete bulletList.at(i);
		}
	}
	delete this->musicPlayer;
}

/// <summary>
/// Move player 
/// </summary>
/// <param name="deltaTime"></param>
/// <param name="direction"></param>
/// <param name="gameWindow"></param>
void Player::move(float deltaTime, int direction)
{
	if (!this->exploded)
	{
		if (this->playerSprite.getPosition().x + (minPlayerMovementSpeed * direction) * deltaTime <
			gameWindow->getSize().x - this->playerSprite.getTextureRect().width - 10
			&& this->playerSprite.getPosition().x + (minPlayerMovementSpeed * direction) * deltaTime >
			0 + this->playerSprite.getTextureRect().width + 10)
		{
			this->playerSprite.setPosition(sf::Vector2f(this->playerSprite.getPosition().x +
				(minPlayerMovementSpeed * direction) * deltaTime,
				this->playerSprite.getPosition().y));
		}
	}
}

/// <summary>
/// Shots a bullet from player position
/// </summary>
void Player::shoot()
{
	if (!this->exploded)
	{
		Bullet* bullet = new Bullet(this->playerSpritePath, this->playerSprite.getPosition().x,
			this->playerSprite.getPosition().y - this->playerSprite.getTextureRect().height - 11, 1, false);

		this->bulletList.push_back(bullet);

		musicPlayer->openMusic(this->shootSoundPath, false);
		musicPlayer->playMusic();
	}
}

/// <summary>
/// Draw player and player bullets
/// </summary>
/// <param name="gameWindow"></param>
void Player::draw()
{
	//draw Player
	gameWindow->draw(this->playerSprite);

	//draw Player Bullets
	for (int i = 0; i < bulletList.size(); i++)
	{
		bulletList.at(i)->draw(gameWindow);
	}

	//draw player lives and score
	gameWindow->draw(this->scoreText);

	//gameWindow->draw(playerLivesSprite);
	for (int i = 0; i < this->livesList.size(); i++)
	{
		gameWindow->draw(this->livesList.at(i));
	}
}

/// <summary>
/// Update bullets and delete it if outside of Window
/// </summary>
/// <param name="deltaTime"></param>
/// <param name="gameWindow"></param>
void Player::update(float deltaTime)
{
	//update Bullet Position
	for (int i = 0; i < bulletList.size(); i++)
	{
		//if Bullet out of bounds remove it from list
		if (bulletList.at(i)->update(deltaTime, gameWindow))
		{
			delete bulletList.at(i);
			bulletList.erase(bulletList.begin() + i);
		}
	}

	//move right
	if (InputHandler::isKeyPressed(sf::Keyboard::Right) || InputHandler::isKeyHeld(sf::Keyboard::Right))
		move(deltaTime, 1);

	//move left
	if (InputHandler::isKeyPressed(sf::Keyboard::Left) || InputHandler::isKeyHeld(sf::Keyboard::Left))
		move(deltaTime, -1);

	//shoot
	if (InputHandler::isKeyPressed(sf::Keyboard::Space) || InputHandler::isKeyHeld(sf::Keyboard::Space))
	{
		if (this->clock.getElapsedTime().asSeconds() > this->bulletCoolDown)
		{
			this->clock.restart();
			shoot();
		}
	}

	//update deathAnimation
	if (this->deathTime.getElapsedTime().asSeconds() > 1.0f)
	{
		this->exploded = false;
		explosionAnimation();
	}

	//update score
	this->scoreText.setString(std::to_string(this->score));
}

/// <summary>
/// Removes one life from a player
/// </summary>
void Player::removeLife()
{
	if (this->lives > 0)
	{
		this->lives = this->lives - 1;
		this->livesList.erase(this->livesList.begin());
	}
	else
		std::cout << "Tried to remove life when no lives left" << std::endl;
}

/// <summary>
/// Changes player sprite when exploded
/// </summary>
void Player::explosionAnimation()
{
	if (this->exploded)
		this->playerSprite.setTextureRect(sf::IntRect(11, 0, 11, 8));
	else
		this->playerSprite.setTextureRect(sf::IntRect(0, 0, 11, 8));
}

/// <summary>
/// Call when player hit
/// Plays explosion sound and removes one life from player
/// </summary>
void Player::playerExplode()
{
	this->musicPlayer->openMusic(this->deadSoundPath, false);
	this->musicPlayer->playMusic();
	this->exploded = true;

	this->deathTime.restart();

	removeLife();
	explosionAnimation();
}

/// <summary>
/// Draws player lives and score on screen
/// </summary>
/// <param name="gameWindow"></param>
void Player::playerGui()
{
	//Score Text
	scoreText = sf::Text();
	scoreText.setString(std::to_string(this->score));
	scoreText.setFont(*this->pixelFont);
	scoreText.setOrigin(scoreText.getLocalBounds().height / 2, scoreText.getLocalBounds().width / 2);
	scoreText.setPosition(sf::Vector2f(gameWindow->getSize().x - scoreText.getLocalBounds().width - 140,
		0 + scoreText.getGlobalBounds().height));

	//Lives Display
	for (int i = 0; i < this->lives; i++)
	{
		addLife();
	}
}


/// <summary>
/// Add a live to the player
/// </summary>
void Player::addLife()
{
	this->playerLivesSprite = sf::Sprite(this->playerTexture);
	this->playerLivesSprite.setScale(sf::Vector2f(3.0f, 3.0f));
	this->playerLivesSprite.setTextureRect(sf::IntRect(0, 0, 11, 8));
	this->playerLivesSprite.setOrigin(sf::Vector2f(this->playerLivesSprite.getLocalBounds().width / 2,
		this->playerLivesSprite.getLocalBounds().height / 2));
	this->playerLivesSprite.setPosition(sf::Vector2f(playerLivesSprite.getGlobalBounds().width + 40 * livesList.size(), 20));

	this->livesList.push_back(playerLivesSprite);
}
