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
#include <algorithm>

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

	void update();
	void render();
	void pauseGame();

private:
	int topScore;
	int gameState;
	int level;
	int borderOffset;
	int invadersPerRow;
	int rowsOfInvaders;
	const char* invaderSheetPath = "res\\InvadersSheet.png";
	const char* playerSheetPath = "res\\PlayerSheet.png";
	const char* deadInvaderSoundPath = "res\\sound_Effects\\invaderkilled.wav";
	const char* explosionSoundPath = "res\\sound_Effects\\explosion.wav";
	const char* shootSoundPath = "res\\sound_Effects\\shoot.wav";
	const char* pixelFontPath = "res\\fonts\\invader.ttf";
	std::vector<Invader*> invaderList;
	sf::Clock clock;
	float fixedDeltaTime;
	Menu* menu;
	Player* player;
	MusicPlayer* musicPlayer;
	Ufo* ufo;
	bool isUfoAlive;
	sf::Clock ufoSpawnClock;
	sf::Text pauseText;
	sf::Font pixelFont;
	int mostLeftInvaderIndex;
	int mostRightInvaderIndex;
	sf::RenderWindow* gameWindow;
	sf::Clock invaderClock;
	std::vector<int> bottomInvaderList;
	std::vector<Bullet*> invaderBullets;
	sf::Text gameOverText;
	sf::Text scoreText;

	void initInvaders(int invaderAmount, int rowsOfInvaders);
	void checkCollision();
	void spawnUfo(int speed);
	void findMostLeftandRightInvader();
	void findMostBottomInvaders();
	void invaderShoot();
	void gameOver();
};