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
	std::vector<Bullet*> bulletList;
	int score;
	sf::Sprite playerSprite;
	bool exploded;
	int lives;

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

private:
	int minPlayerMovementSpeed;
	sf::Texture playerTexture;
	sf::Clock clock;
	const char* playerSpritePath;
	float bulletCoolDown;
	const char* shootSoundPath = "res\\sound_Effects\\shoot.wav";
	const char* deadSoundPath = "res\\sound_Effects\\explosion.wav";
	MusicPlayer* musicPlayer;
	sf::Text scoreText;
	sf::Font* pixelFont;
	sf::Sprite playerLivesSprite;
	std::vector<sf::Sprite> livesList;
	sf::Clock deathTime;
	sf::RenderWindow* gameWindow;

	void playerGui();
};