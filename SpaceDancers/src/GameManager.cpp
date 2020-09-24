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
	delete invaderSheetPath;
	delete invaderSheetPath;
	delete musicPlayer;
	delete ufo;
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
		this->player = new Player(this->playerSheetPath, gameWindow);

		//TEMPPPPPPP
		this->ufo = new Ufo(this->invaderSheetPath, gameWindow);

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

		//Randomly Spawn an Ufo
		this->ufo->update(gameWindow, deltaTime);

		//Check for Collisions between Invaders and Bullets
		checkCollision();
	}
}

void GameManager::initInvaders(int invaderAmountPerRow, int rowsOfInvaders) {
	int rowY = 50;

	for (int j = 0; j < rowsOfInvaders; j++) {
		for (int i = 0; i < invaderAmountPerRow; i++)
		{
			Invader* invader = new Invader(this->invaderSheetPath, j, (int)(MAX_INVADER_TYPES / (float)rowsOfInvaders * j));
			invader->setPosition(sf::Vector2f((i * invader->rowHeigth) + borderOffset, rowY));
			invaderList.push_back(invader);
		}
		rowY += 50;
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

				//delete bullet from list
				this->player->bulletList.erase(this->player->bulletList.begin() + i);

				//increase score of player
				this->player->score += 20;
				break;
			}
			else if (Collision::PixelPerfectTest(this->player->bulletList[i]->getSprite(), this->ufo->ufoSprite))
			{
				//Don't draw the ufo anymore
				delete this->ufo;

				//Ufo explosion sound
				this->musicPlayer->openMusic(this->explosionSoundPath, false);
				this->musicPlayer->playMusic();

				//increase score of player
				this->player->score += 150;
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
		this->ufo->draw(gameWindow);
		break;
	}
}