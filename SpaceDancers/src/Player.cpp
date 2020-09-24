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

Player::Player(const char* spriteSheetPath, sf::RenderWindow* gameWindow) :lives(3), score(0),
exploded(false), minPlayerMovementSpeed(400), bulletCoolDown(0.4f)
{
	this->playerSpritePath = spriteSheetPath;
	this->playerTexture = sf::Texture();
	if (!this->playerTexture.loadFromFile(this->playerSpritePath))
	{
		// Texture could not be found
		std::cout << "Player Texture could not be loaded" << std::endl;
	}

	this->playerSprite = sf::Sprite(this->playerTexture);
	this->playerSprite.setScale(sf::Vector2f(3.0f, 3.0f));
	this->playerSprite.setTextureRect(sf::IntRect(0, 0, 11, 8));
	this->playerSprite.setOrigin(sf::Vector2f(this->playerSprite.getLocalBounds().width / 2,
		this->playerSprite.getLocalBounds().height / 2));
	this->playerSprite.setPosition(sf::Vector2f(gameWindow->getSize().x / 2, gameWindow->getSize().y - 11));

	clock.restart();

	//Obejct to handle sound
	this->musicPlayer = new MusicPlayer();

	//load font
	if (!font.loadFromFile("C:\\Users\\Enrico\\Desktop\\SpaceDancers\\SpaceDancers\\bin\\Debug\\x64\\res\\fonts\\invader.ttf"))
	{
		//handle error
		std::cout << "Font could not be loaded" << std::endl;
	}

	//init player score and lives
	playerGui(gameWindow);
}

Player::~Player()
{
	delete playerSpritePath;

	if (!bulletList.empty())
	{
		for (int i = 0; i < bulletList.size(); i++)
		{
			delete bulletList.at(i);
		}
	}

}

void Player::move(float deltaTime, int direction, sf::RenderWindow* gameWindow)
{
	if (!this->exploded)
	{
		if (this->playerSprite.getPosition().x + (minPlayerMovementSpeed * direction) * deltaTime < gameWindow->getSize().x - this->playerSprite.getTextureRect().width - 10
			&& this->playerSprite.getPosition().x + (minPlayerMovementSpeed * direction) * deltaTime > 0 + this->playerSprite.getTextureRect().width + 10)
		{
			this->playerSprite.setPosition(sf::Vector2f(this->playerSprite.getPosition().x + (minPlayerMovementSpeed * direction) * deltaTime,
				this->playerSprite.getPosition().y));
		}
	}
}

void Player::shoot()
{
	if (!this->exploded)
	{
		Bullet* bullet = new Bullet(this->playerSpritePath, this->playerSprite.getPosition().x,
			this->playerSprite.getPosition().y - this->playerSprite.getTextureRect().height - 11);

		this->bulletList.push_back(bullet);

		musicPlayer->openMusic(this->shootSoundPath, false);
		musicPlayer->playMusic();
	}
}

void Player::draw(sf::RenderWindow* gameWindow)
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

void Player::update(float deltaTime, sf::RenderWindow* gameWindow)
{
	//update Bullet Position
	for (int i = 0; i < bulletList.size(); i++)
	{
		//if Bullet out of bounds remove it from list
		if (bulletList.at(i)->update(deltaTime, gameWindow))
		{
			bulletList.erase(bulletList.begin() + i);
		}
	}


	//move right
	if (InputHandler::isKeyPressed(sf::Keyboard::Right) || InputHandler::isKeyHeld(sf::Keyboard::Right))
		move(deltaTime, 1, gameWindow);

	//move left
	if (InputHandler::isKeyPressed(sf::Keyboard::Left) || InputHandler::isKeyHeld(sf::Keyboard::Left))
		move(deltaTime, -1, gameWindow);

	//shoot
	if (InputHandler::isKeyPressed(sf::Keyboard::Space) || InputHandler::isKeyHeld(sf::Keyboard::Space))
	{	
		if (this->clock.getElapsedTime().asSeconds() > this->bulletCoolDown)
		{
			this->clock.restart();
			shoot();
		}
	}

	spriteAnimation();

	//update score
	this->scoreText.setString(std::to_string(this->score));
}

void Player::removeLife()
{
	this->lives--;
	this->livesList.erase(this->livesList.begin());
}

void Player::spriteAnimation()
{
	if (this->exploded)
	{
		this->playerSprite.setTextureRect(sf::IntRect(22, 0, 11, 8));
	}
}

void Player::playerExplode()
{
	this->musicPlayer->openMusic(this->deadSoundPath, false);
	this->musicPlayer->playMusic();
}

void Player::playerGui(sf::RenderWindow* gameWindow)
{
	//Score Text
	scoreText = sf::Text();
	scoreText.setString(std::to_string(this->score));
	scoreText.setFont(font);
	scoreText.setOrigin(sf::Vector2f(scoreText.getPosition().x, scoreText.getPosition().y));
	scoreText.setPosition(sf::Vector2f(gameWindow->getSize().x - scoreText.getGlobalBounds().width - 160,
		0 + scoreText.getGlobalBounds().height));

	//Lives Display
	for (int i = 0; i < this->lives; i++)
	{
		addLife();
	}
}

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
