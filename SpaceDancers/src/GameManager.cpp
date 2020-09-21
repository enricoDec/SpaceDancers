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

GameManager::GameManager():fixedDeltaTime(0.0f) {
	this->gameState = GAME_STATE_MENU;
	//Play Button etc... init
}

GameManager::~GameManager() {
	for (int i = 0; i < invaderList.size(); i++)
	{
		delete invaderList.at(i);
	}
}

void GameManager::startGame() {
}

void GameManager::update() {
	
	float deltaTime = clock.restart().asSeconds();
	fixedDeltaTime += deltaTime;



	// && click on menu
	if (this->gameState == GAME_STATE_MENU)
	{
		initInvaders(10);
		this->gameState = GAME_STATE_RUNNING;
	}
	if (this->gameState == GAME_STATE_RUNNING) {
		for (int i = 0; i < invaderList.size(); i++)
		{
			invaderList.at(i)->move(deltaTime);

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

void GameManager::initInvaders(int invaderAmount) {
	for (int i = 0; i < invaderAmount; i++)
	{
		Invader* invader = new Invader(this->spritePath);
		invader->setPosition(sf::Vector2f(i * 50, 100));
		invaderList.push_back(invader);
	}
}

void GameManager::render(sf::RenderWindow* renderWindow) {
	for (int i = 0; i < invaderList.size(); i++)
	{
		invaderList.at(i)->draw(renderWindow);
	}
}