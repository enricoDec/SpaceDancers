///////////////////////////////////
/// 
/// Source File: GameManager.cpp
/// 
/// AUTHOR: Enrico Gamil Toros de Chadarevian
/// MATRNR: 567011
/// CREATE DATE: 9/17/2020 6:58:20 PM
///
/////////////////////////////////////

#include "GameManager.h"

GameManager::GameManager(sf::RenderWindow* gameWindow) :fixedDeltaTime(0.0f), borderOffset(50),
invadersPerRow(12), rowsOfInvaders(3), level(0), topScore(0) {
	this->gameState = GAME_STATE_MENU;

	menu = new Menu(gameWindow->getSize().x, gameWindow->getSize().y);
	this->musicPlayer = new MusicPlayer();
}

GameManager::~GameManager() {
	if (!invaderList.empty())
	{
		for (int i = 0; i < invaderList.size(); i++)
		{
			delete invaderList.at(i);
		}
	}
	delete menu;
	delete player;
	delete spritePath;
	delete spritePath;
}

void GameManager::update(sf::RenderWindow* gameWindow) {

	float deltaTime = clock.restart().asSeconds();
	fixedDeltaTime += deltaTime;

	//Menu
	if (this->gameState == GAME_STATE_MENU)
	{
		menu->update(gameWindow);
		if (menu->startGame == true)
		{
			this->gameState = GAME_STATE_INIT;
		}
	}

	//Init Game
	if (this->gameState == GAME_STATE_INIT)
	{
		initInvaders(invadersPerRow, rowsOfInvaders);
		this->player = new Player(this->spritePath2, gameWindow);

		this->gameState = GAME_STATE_RUNNING;
	}

	//Game Running
	if (this->gameState == GAME_STATE_RUNNING) {

		//Update Player
		this->player->update(deltaTime, gameWindow);

		//Update Invaders
		for (int i = 0; i < invaderList.size(); i++)
		{
			// move entire row at once
			invaderList.at(i)->move(deltaTime, gameWindow, invaderList, borderOffset);

			// Sprite Animation 2 times a sec
			if (fixedDeltaTime > 1 / 2.0f)
			{
				invaderList.at(i)->spriteAnimation();
			}
		}
		if (fixedDeltaTime > 1 / 2.0f) {
			fixedDeltaTime -= 1 / 5.0f;
		}

		//Check for Collisions between Invaders and Bullets
		checkCollision();
	}
}

void GameManager::initInvaders(int invaderAmountPerRow, int rowsOfInvaders) {
	int rowY = 50;

	for (int j = 0; j < rowsOfInvaders; j++) {
		for (int i = 0; i < invaderAmountPerRow; i++)
		{
			Invader* invader = new Invader(this->spritePath, j, (int)(MAX_INVADER_TYPES / (float)rowsOfInvaders * j));
			invader->setPosition(sf::Vector2f((i * 50) + borderOffset, rowY));
			invaderList.push_back(invader);
		}
		rowY += 40;
	}
}

/// <summary>
/// Checks for collisions between Bullets and Invaders
/// Removes Invader and Bullet from list
/// </summary>
void GameManager::checkCollision()
{
	for (int i = 0; i < this->player->bulletList.size(); i++)
	{
		for (int j = 0; j < this->invaderList.size(); j++)
		{
			if (Collision::PixelPerfectTest(this->player->bulletList[i]->getSprite(), this->invaderList[j]->getSprite()))
			{
				//delete invader from list
				this->invaderList.erase(this->invaderList.begin() + j);

				//Invader die sound
				this->musicPlayer->openMusic(this->deadInvaderSoundPath, false);
				this->musicPlayer->playMusic();

				this->player->bulletList.erase(this->player->bulletList.begin() + i);

				//increase score of player
				this->player->score += 20;
				break;
			}
		}
	}
}


void GameManager::startGame() {
}

void GameManager::render(sf::RenderWindow* gameWindow) {
	switch (gameState)
	{
	case GAME_STATE_MENU:
		menu->draw(gameWindow);
		break;
	case GAME_STATE_RUNNING:
		for (int i = 0; i < invaderList.size(); i++)
		{
			invaderList.at(i)->draw(gameWindow);
		}

		this->player->draw(gameWindow);
		break;
	}
}