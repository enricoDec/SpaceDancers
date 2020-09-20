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

class Player
{
public:
	Player();
	~Player();
	void move();
	void shoot();

private:
	int lives;
	int score;
};