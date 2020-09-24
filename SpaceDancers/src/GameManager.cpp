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
invadersPerRow(12), rowsOfInvaders(3), level(0), topScore(0), isUfoAlive(false) {
	this->gameState = GAME_STATE_MENU;

	menu = new Menu(gameWindow->getSize().x, gameWindow->getSize().y);
	this->musicPlayer = new MusicPlayer();
}

GameManager::~GameManager() {
	if (!invaderList.empty())
	{
		for (int i = 0; i < this->invaderList.size(); i++)
		{
			delete this->invaderList.at(i);
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

		this->gameState = GAME_STATE_RUNNING;
	}

	//Game Running
	if (this->gameState == GAME_STATE_RUNNING) {

		//Update Player
		this->player->update(deltaTime, gameWindow);

		//Update Invaders
		for (int i = 0; i < this->invaderList.size(); i++)
		{
			// move entire row at once
			this->invaderList.at(i)->move(deltaTime, gameWindow, this->invaderList, borderOffset);

			// Sprite Animation 2 times a sec
			if (fixedDeltaTime > 1 / 2.0f)
			{
				this->invaderList.at(i)->spriteAnimation();
			}
		}
		if (fixedDeltaTime > 1 / 2.0f) {
			fixedDeltaTime -= 1 / 5.0f;
		}

		//Update Spawn position
		if (this->isUfoAlive)
			this->ufo->update(gameWindow, deltaTime);

		//Spawn an Ufo each 30sec
		if (ufoSpawnClock.getElapsedTime().asSeconds() > 30.0f)
		{
			ufoSpawnClock.restart();
			spawnUfo(60, gameWindow);
		}

		//Check for Collisions between Invaders and Bullets
		checkCollision();
	}
}

void GameManager::initInvaders(int invaderAmountPerRow, int rowsOfInvaders) {
	//Space between top of Window on first row of invaders
	int rowY = 50;

	for (int j = 0; j < rowsOfInvaders; j++) {
		for (int i = 0; i < invaderAmountPerRow; i++)
		{
			Invader* invader = new Invader(this->invaderSheetPath, j, (int)(MAX_INVADER_TYPES / (float)rowsOfInvaders * j));
			invader->setPosition(sf::Vector2f((i * invader->rowHeigth) + borderOffset, rowY));
			this->invaderList.push_back(invader);
		}
		//Space between each invader row
		rowY += this->invaderList.at(0)->rowHeigth;
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
			else if (this->isUfoAlive && Collision::PixelPerfectTest(this->player->bulletList[i]->getSprite(), this->ufo->ufoSprite))
			{
				//Don't draw the ufo anymore
				delete this->ufo;

				this->isUfoAlive = false;

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

void GameManager::spawnUfo(int speed, sf::RenderWindow* gameWindow)
{
	this->ufo = new Ufo(speed, this->invaderSheetPath, gameWindow);
	this->isUfoAlive = true;
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
		for (int i = 0; i < this->invaderList.size(); i++)
		{
			this->invaderList.at(i)->draw(gameWindow);
		}

		this->player->draw(gameWindow);

		if(this->isUfoAlive)
		this->ufo->draw(gameWindow);
		break;
	}
}