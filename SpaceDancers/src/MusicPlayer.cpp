/////////////////////////////////////
/// 
/// Source File: MusicPlayer.cpp
/// 
/// AUTHOR: Enrico Gamil Toros de Chadarevian
/// MATRNR: 567011
/// CREATE DATE: 9/23/2020 3:30:00 PM
///
/////////////////////////////////////

#include "MusicPlayer.h"

MusicPlayer::MusicPlayer(bool loop)
{
	this->music = new sf::Music();
	this->music->setLoop(loop);
}

MusicPlayer::~MusicPlayer()
{
	delete music;
}

void MusicPlayer::openMusic(const char* pathToSong)
{
	if (!music->openFromFile(pathToSong))
	{
		std::cout << "Song could not be loaded!" << std::endl;
		std::cout << pathToSong << std::endl;
	}
}

void MusicPlayer::playMusic()
{
	music->play();
}

void MusicPlayer::pauseMusic()
{
	music->pause();
}

void MusicPlayer::stopMusic()
{
	music->stop();
}
