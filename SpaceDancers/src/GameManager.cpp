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

GameManager::GameManager(sf::RenderWindow* gameWindow):fixedDeltaTime(0.0f), borderOffset(50), 
invadersPerRow(12), rowsOfInvaders(3), level(0), topScore(0) {
	this->gameState = GAME_STATE_MENU;

	menu = new Menu(gameWindow->getSize().x, gameWindow->getSize().y);
}

GameManager::~GameManager() {
	for (int i = 0; i < invaderList.size(); i++)
	{
		delete invaderList.at(i);
	}
}

void GameManager::startGame() {
}

void GameManager::update(sf::RenderWindow* gameWindow) {
	
	float deltaTime = clock.restart().asSeconds();
	fixedDeltaTime += deltaTime;

	if (this->gameState == GAME_STATE_MENU)
	{
		menu->update(gameWindow);
		if (menu->startGame == true)
		{
			this->gameState = GAME_STATE_INIT;
		}
	}

	if (this->gameState == GAME_STATE_INIT)
	{
		initInvaders(invadersPerRow, rowsOfInvaders);
		this->gameState = GAME_STATE_RUNNING;
	}

	if (this->gameState == GAME_STATE_RUNNING) {
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
		break;
	}
}