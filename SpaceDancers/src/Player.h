/////////////////////////////////////
/// 
/// Header File: Player.h
/// 
/// AUTHOR: Enrico Gamil Toros de Chadarevian
/// MATRNR: 567011
/// CREATE DATE: 9/17/2020 6:46:01 PM
///
/////////////////////////////////////

#pragma once
#include <SFML/Graphics.hpp>
#include "InputHandler.h"
#include "Bullet.h"
#include <vector>
#include "MusicPlayer.h"

class Player
{
public:
	Player(sf::Font* pixelFont, const char* spriteSheetPath, sf::RenderWindow* gameWindow);
	~Player();
	void move(float deltaTime, int direction);
	void shoot();
	void draw();
	void update(float deltaTime);
	void removeLife();
	void addLife();
	void playerExplode();
	void explosionAnimation();

	std::vector<Bullet*> bulletList;
	sf::Sprite playerSprite;
	int score;
	int lives;
	bool exploded;

private:
	void playerGui();

	int minPlayerMovementSpeed;
	float bulletCoolDown;

	const char* shootSoundPath = "res\\sound_Effects\\shoot.wav";
	const char* deadSoundPath = "res\\sound_Effects\\explosion.wav";
	const char* playerSpritePath;

	std::vector<sf::Sprite> livesList;

	MusicPlayer* musicPlayer;
	sf::RenderWindow* gameWindow;

	sf::Text scoreText;
	sf::Font* pixelFont;
	sf::Sprite playerLivesSprite;
	sf::Texture playerTexture;
	sf::Clock deathTime;
	sf::Clock clock;
};