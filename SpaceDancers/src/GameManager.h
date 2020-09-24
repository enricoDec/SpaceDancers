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
#include "Player.h"
#include "Collision.h"
#include "MusicPlayer.h"
#include "Ufo.h"

#define GAME_STATE_MENU		 0
#define GAME_STATE_INIT		 1
#define GAME_STATE_PAUSE	 2
#define GAME_STATE_RUNNING	 3
#define GAME_STATE_GAME_OVER 4

#define MAX_INVADER_TYPES 3

class GameManager
{
public:
	GameManager(sf::RenderWindow* gameWindow);
	~GameManager();
	void startGame();
	void update(sf::RenderWindow* gameWindow);
	void render(sf::RenderWindow* gameWindow);

private:
	int topScore;
	int gameState;
	int level;
	int borderOffset;
	int invadersPerRow;
	int rowsOfInvaders;
	const char* invaderSheetPath = "C:\\Users\\Enrico\\Desktop\\SpaceDancers\\SpaceDancers\\bin\\Debug\\x64\\res\\InvadersSheet.png";
	const char* playerSheetPath = "C:\\Users\\Enrico\\Desktop\\SpaceDancers\\SpaceDancers\\bin\\Debug\\x64\\res\\PlayerSheet.png";
	const char* deadInvaderSoundPath = "C:\\Users\\Enrico\\Desktop\\SpaceDancers\\SpaceDancers\\bin\\Debug\\x64\\res\\sound_Effects\\invaderkilled.wav";
	const char* explosionSoundPath = "C:\\Users\\Enrico\\Desktop\\SpaceDancers\\SpaceDancers\\bin\\Debug\\x64\\res\\sound_Effects\\explosion.wav";
	std::vector<Invader*> invaderList;
	sf::Clock clock;
	float fixedDeltaTime;
	Menu* menu;
	Player* player;
	MusicPlayer* musicPlayer;
	Ufo* ufo;

	void initInvaders(int invaderAmount, int rowsOfInvaders);
	void checkCollision();
};