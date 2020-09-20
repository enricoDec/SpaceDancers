/////////////////////////////////////
/// 
/// Header File: GameManager.h
/// 
/// AUTHOR: Enrico Gamil Toros de Chadarevian
/// MATRNR: 567011
/// CREATE DATE: 9/17/2020 1:58:20 PM
///
/////////////////////////////////////

#pragma once
#include <vector>
#include "Invader.h"

#define GAME_STATE_MENU		 0
#define GAME_STATE_PAUSE	 1
#define GAME_STATE_RUNNING	 2
#define GAME_STATE_GAME_OVER 3

class GameManager
{
public:
	GameManager();
	~GameManager();
	void startGame();
	void update();
	void render(sf::RenderWindow* renderWindow);

private:
	void initInvaders(int invaderAmount);
	int topScore;
	int gameState;
	int level;
	const char* spritePath = "S:\\code\\HTW\\Computergrafik\\SpaceDancer\\SpaceDancers\\bin\\Debug\\x64\\res\\Invader.PNG";
	std::vector<Invader*> invaderList;
};