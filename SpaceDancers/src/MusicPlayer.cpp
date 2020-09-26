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

MusicPlayer::MusicPlayer(float volume)
{
	this->music = new sf::Music();
	this->music->setVolume(volume);
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
	this->music->setLoop(loop);
	if (!music->openFromFile(pathToSong))
	{
		std::cout << "Song could not be loaded!" << std::endl;
		std::cout << pathToSong << std::endl;
	}
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
