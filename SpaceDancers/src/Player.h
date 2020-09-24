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

	Player(sf::Font* pixelFont, const char* spriteSheetPath, sf::RenderWindow* gameWindow);
	~Player();
	void move(float deltaTime, int direction, sf::RenderWindow* gameWindow);
	void shoot();
	void draw(sf::RenderWindow* gameWindow);
	void update(float deltaTime, sf::RenderWindow* gameWindow);
	void removeLife();
	void addLife();


private:
	int lives;
	bool exploded;
	int minPlayerMovementSpeed;
	sf::Sprite playerSprite;
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

	void spriteAnimation();
	void playerExplode();
	void playerGui(sf::RenderWindow* gameWindow);
};