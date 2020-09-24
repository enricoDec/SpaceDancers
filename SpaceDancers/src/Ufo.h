/////////////////////////////////////
/// 
/// Header File: Ufo.h
/// 
/// AUTHOR: Enrico Gamil Toros de Chadarevian
/// MATRNR: 567011
/// CREATE DATE: 9/22/2020 2:30:00 AM
///
/////////////////////////////////////
#pragma once
#include <SFML/Graphics.hpp>
#include "MusicPlayer.h"
#include "Collision.h"

class Ufo
{
public:
	sf::Sprite ufoSprite;

	Ufo(int speed, const char* ufoTexturePath, sf::RenderWindow* gameWindow);
	~Ufo();
	
	void update(sf::RenderWindow* gameWindow, float deltaTime);
	void draw(sf::RenderWindow* gameWindow);

private:
	int speed;
	const char* ufoSoundPath = "C:\\Users\\Enrico\\Desktop\\SpaceDancers\\SpaceDancers\\bin\\Debug\\x64\\res\\sound_Effects\\ufo.wav";
	sf::Texture ufoTexture;
	MusicPlayer* musicPlayer;

};