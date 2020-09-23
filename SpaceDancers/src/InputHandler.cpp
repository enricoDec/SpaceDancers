/////////////////////////////////////
/// 
/// Source File: InputHandler.cpp
/// 
/// AUTHOR: Enrico Gamil Toros de Chadarevian
/// MATRNR: 567011
/// CREATE DATE: 9/22/2020 5:30:00 PM
///
/////////////////////////////////////

#include "InputHandler.h"

std::vector<int> InputHandler::pressedKeyCodesList;
std::vector<int> InputHandler::realeasedKeyCodesList;
std::vector<int> InputHandler::holdKeyCodesList;

/// <summary>
/// Returns true if key pressed
/// </summary>
/// <param name="keyCode"></param>
/// <returns></returns>
bool InputHandler::isKeyPressed(int keyCode)
{
	std::vector<int>::iterator position = std::find(pressedKeyCodesList.begin(), pressedKeyCodesList.end(), keyCode);
	if (position != pressedKeyCodesList.end()) // if found
		return true;
	else
		return false;
}

bool InputHandler::isKeyRealeased(int keyCode)
{
	std::vector<int>::iterator position = std::find(realeasedKeyCodesList.begin(), realeasedKeyCodesList.end(), keyCode);
	if (position != realeasedKeyCodesList.end()) //if found
		return true;
	else
		return false;
}

bool InputHandler::isKeyHeld(int keyCode)
{
	std::vector<int>::iterator position = std::find(holdKeyCodesList.begin(), holdKeyCodesList.end(), keyCode);
	if (position != holdKeyCodesList.end()) //if found
		return true;
	else
		return false;
}

void InputHandler::registerPress(int keyCode)
{
	if (std::find(pressedKeyCodesList.begin(), pressedKeyCodesList.end(), keyCode) == pressedKeyCodesList.end())
		pressedKeyCodesList.push_back(keyCode);
	if (std::find(holdKeyCodesList.begin(), holdKeyCodesList.end(), keyCode) == holdKeyCodesList.end())
		holdKeyCodesList.push_back(keyCode);
}

void InputHandler::registerRelease(int keyCode)
{
	if (std::find(realeasedKeyCodesList.begin(), realeasedKeyCodesList.end(), keyCode) == realeasedKeyCodesList.end())
		realeasedKeyCodesList.push_back(keyCode);

	// find key code in holdKeyCodesList and delete it since it has been realeased
	std::vector<int>::iterator position = std::find(holdKeyCodesList.begin(), holdKeyCodesList.end(), keyCode);
	if (position != holdKeyCodesList.end())
		holdKeyCodesList.erase(position);
}

void InputHandler::clearKeys()
{
	realeasedKeyCodesList.clear();
	pressedKeyCodesList.clear();
}
