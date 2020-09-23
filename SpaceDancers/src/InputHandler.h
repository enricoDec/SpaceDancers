/////////////////////////////////////
/// 
/// Header File: InputHandler.h
/// 
/// AUTHOR: Enrico Gamil Toros de Chadarevian
/// MATRNR: 567011
/// CREATE DATE: 9/22/2020 5:30:00 PM
///
/////////////////////////////////////

#pragma once
#include <vector>
#include <algorithm>

class InputHandler
{
public:
	InputHandler() = delete;

	static bool isKeyPressed(int keyCode);
	static bool isKeyRealeased(int keyCode);
	static bool isKeyHeld(int keyCode);

	static void registerPress(int keyCode);
	static void registerRelease(int keyCode);
	static void clearKeys();

private:
	static std::vector<int> pressedKeyCodesList;
	static std::vector<int> realeasedKeyCodesList;
	static std::vector<int> holdKeyCodesList;
};