/////////////////////////////////////
/// 
/// Header File: MusicPlayer.h
/// 
/// AUTHOR: Enrico Gamil Toros de Chadarevian
/// MATRNR: 567011
/// CREATE DATE: 9/23/2020 3:30:00 PM
///
/////////////////////////////////////

#pragma once

#include <SFML/Audio.hpp>
#include <iostream>

class MusicPlayer
{
public:
	MusicPlayer(float volume);
	~MusicPlayer();

	void openMusic(const char* pathToSong, bool loop);
	void playMusic();
	void pauseMusic();
	void stopMusic();

private:
	sf::Music* music;
};