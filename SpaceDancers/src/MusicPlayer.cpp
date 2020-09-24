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

MusicPlayer::MusicPlayer()
{
	this->music = new sf::Music();
}

MusicPlayer::~MusicPlayer()
{
	delete music;
}

/// <summary>
/// open sound file
/// </summary>
/// <param name="pathToSong"></param>
/// <param name="loop">true if sound should loop</param>
void MusicPlayer::openMusic(const char* pathToSong, bool loop)
{
	if (!music->openFromFile(pathToSong))
	{
		std::cout << "Song could not be loaded!" << std::endl;
		std::cout << pathToSong << std::endl;
	}
	this->music->setLoop(loop);
}

//play sound
void MusicPlayer::playMusic()
{
	music->play();
}

//pause or resume sound
void MusicPlayer::pauseMusic()
{
	music->pause();
}

//stop sound
void MusicPlayer::stopMusic()
{
	music->stop();
}
