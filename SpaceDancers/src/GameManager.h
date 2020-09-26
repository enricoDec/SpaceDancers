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

	int gameState;
	Player* player;

private:
	void initInvaders(int invaderAmount, int rowsOfInvaders, int speed);
	void checkCollision();
	void spawnUfo(int speed);
	void findMostLeftandRightInvader();
	void findMostBottomInvaders();
	void invaderShoot();
	void nextLevel();

	int level;
	int borderOffset;
	int invadersPerRow;
	int rowsOfInvaders;
	int mostLeftInvaderIndex;
	int mostRightInvaderIndex;
	int invaderInitialSpeed;

	const char* invaderSheetPath = "res\\InvadersSheet.png";
	const char* playerSheetPath = "res\\PlayerSheet.png";
	const char* deadInvaderSoundPath = "res\\sound_Effects\\invaderkilled.wav";
	const char* explosionSoundPath = "res\\sound_Effects\\explosion.wav";
	const char* laserSoundPath = "res\\sound_Effects\\laser.wav";
	const char* shootSoundPath = "res\\sound_Effects\\shoot.wav";
	const char* pixelFontPath = "res\\fonts\\invader.ttf";

	float fixedDeltaTime;
	float invaderShootingFrequency;
	float pauseTime;

	Menu* menu;
	MusicPlayer* invaderMusicPlayer;
	MusicPlayer* playerMusicPlayer;
	MusicPlayer* ufoMusicPlayer;


	sf::Clock ufoSpawnClock;
	sf::Clock clock;
	sf::Clock invaderClock;
	sf::Clock pauseClock;

	sf::RenderWindow* gameWindow;

	std::vector<int> bottomInvaderList;
	std::vector<Bullet*> invaderBullets;
	std::vector<Invader*> invaderList;
	std::vector<Ufo*> ufoList;

	sf::Font pixelFont;
	sf::Text pauseText;
	sf::Text levelText;
};