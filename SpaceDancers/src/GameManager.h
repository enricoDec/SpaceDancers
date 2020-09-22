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
#include "Menu.h"
#include "InputHandler.h"

#define GAME_STATE_MENU		 0
#define GAME_STATE_INIT		 1
#define GAME_STATE_PAUSE	 2
#define GAME_STATE_RUNNING	 3
#define GAME_STATE_GAME_OVER 4

class GameManager
{
public:
	GameManager(sf::RenderWindow* gameWindow);
	~GameManager();
	void startGame();
	void update(sf::RenderWindow* gameWindow);
	void render(sf::RenderWindow* gameWindow);

private:
	void initInvaders(int invaderAmount, int rowsOfInvaders);
	int topScore;
	int gameState;
	int level;
	int borderOffset;
	int invadersPerRow;
	int rowsOfInvaders;
	const char* spritePath = "C:\\Users\\Enrico\\Desktop\\SpaceDancers\\SpaceDancers\\bin\\Debug\\x64\\res\\InvadersSheet.png";
	std::vector<Invader*> invaderList;
	sf::Clock clock;
	float fixedDeltaTime;
	Menu* menu;
};