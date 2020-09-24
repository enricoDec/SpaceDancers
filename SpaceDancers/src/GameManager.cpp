///////////////////////////////////
/// 
/// Source File: GameManager.cpp
/// 
/// AUTHOR: Enrico Gamil Toros de Chadarevian
/// MATRNR: 567011
/// CREATE DATE: 9/17/2020 6:58:20 PM
///
/////////////////////////////////////

#include "GameManager.h"

GameManager::GameManager(sf::RenderWindow* gameWindow) :fixedDeltaTime(0.0f), borderOffset(50),
invadersPerRow(12), rowsOfInvaders(3), level(0), topScore(0), isUfoAlive(false), player(nullptr), ufo(nullptr) {
	this->gameWindow = gameWindow;

	//init game state
	this->gameState = GAME_STATE_MENU;

	//init menu
	menu = new Menu(this->gameWindow->getSize().x, this->gameWindow->getSize().y);
	
	this->musicPlayer = new MusicPlayer();

	//init font
	this->pixelFont = sf::Font();
	if (!pixelFont.loadFromFile(this->pixelFontPath))
	{
		//Invader Font could not be loaded / found
		std::cout << "Font could not be loaded" << std::endl;
	}

	//Pause Text init
	this->pauseText.setString("Press Enter to unpause");
	this->pauseText.setFont(this->pixelFont);
	this->pauseText.setCharacterSize(this->pauseText.getCharacterSize() + 10);
	this->pauseText.setOrigin(sf::Vector2f(this->pauseText.getGlobalBounds().width / 2,
		this->pauseText.getGlobalBounds().height / 2));
	this->pauseText.setPosition(sf::Vector2f(this->gameWindow->getSize().x / 2, this->gameWindow->getSize().y / 2));
}

GameManager::~GameManager() {
	if (!invaderList.empty())
	{
		for (int i = 0; i < this->invaderList.size(); i++)
		{
			delete this->invaderList.at(i);
		}
	}
	delete menu;
	delete player;
	delete musicPlayer;
	delete ufo;
}

/// <summary>
/// GameManager update main entry point of all game object updates
/// </summary>
/// <param name="gameWindow"></param>
void GameManager::update() {
	// time used to update the game taking into account different render times
	float deltaTime = clock.restart().asSeconds();
	fixedDeltaTime += deltaTime;

	//Menu
	if (this->gameState == GAME_STATE_MENU)
	{
		//update menu state and change if usre clicks on play
		menu->update(this->gameWindow);
		if (menu->startGame == true)
		{
			this->gameState = GAME_STATE_INIT;
		}
	}

	//Init Game
	if (this->gameState == GAME_STATE_INIT)
	{
		//Create invaders, player
		initInvaders(invadersPerRow, rowsOfInvaders);
		this->player = new Player(&this->pixelFont, this->playerSheetPath, this->gameWindow);

		this->gameState = GAME_STATE_RUNNING;
	}

	//Game Running
	if (this->gameState == GAME_STATE_RUNNING)
	{

		//Pause the game if P is pressed
		if (InputHandler::isKeyPressed(sf::Keyboard::P))
		{
			pauseGame();
		}

		//Update Player
		this->player->update(deltaTime, this->gameWindow);

		//Update Invaders Animation
		for (int i = 0; i < this->invaderList.size(); i++)
		{
			// Sprite Animation 2 times a sec
			if (fixedDeltaTime > 1 / 2.0f)
			{
				this->invaderList.at(i)->spriteAnimation();
			}
		}
		if (fixedDeltaTime > 1 / 2.0f) {
			fixedDeltaTime -= 1 / 5.0f;
		}

		//Update Invader Position
		this->invaderList.at(0)->move(deltaTime, this->gameWindow, this->invaderList, borderOffset, mostLeftInvaderIndex, mostRightInvaderIndex);

		//Update Spawn position
		if (this->isUfoAlive)
			this->ufo->update(this->gameWindow, deltaTime);

		//Spawn an Ufo each 30sec
		if (ufoSpawnClock.getElapsedTime().asSeconds() > 30.0f)
		{
			ufoSpawnClock.restart();
			spawnUfo(100);
		}

		//Check for Collisions between Invaders and Bullets
		checkCollision();
	}

	if (this->gameState == GAME_STATE_PAUSE)
	{
		//Unpause the game if Enter is pressed;
		if (InputHandler::isKeyPressed(sf::Keyboard::Enter))
		{
			ufoSpawnClock.restart();
			this->gameState = GAME_STATE_RUNNING;
		}
	}
}

/// <summary>
/// Initializes the invaders
/// </summary>
/// <param name="invaderAmountPerRow"></param>
/// <param name="rowsOfInvaders"></param>
void GameManager::initInvaders(int invaderAmountPerRow, int rowsOfInvaders) {
	//Space between top of Window on first row of invaders
	int rowY = 50;

	for (int j = 0; j < rowsOfInvaders; j++) {
		for (int i = 0; i < invaderAmountPerRow; i++)
		{
			Invader* invader = new Invader(this->invaderSheetPath, j, (int)(MAX_INVADER_TYPES / (float)rowsOfInvaders * j));
			invader->setPosition(sf::Vector2f((i * invader->rowHeigth) + borderOffset + 20, rowY));
			this->invaderList.push_back(invader);
		}
		//Space between each invader row
		rowY += this->invaderList.at(0)->rowHeigth;
	}

	this->mostLeftInvaderIndex = 0;
	this->mostRightInvaderIndex = invadersPerRow - 1;
}

/// <summary>
/// Checks for collisions between Bullets, Invaders and the player
/// Removes Invader and Bullet from list
/// </summary>
void GameManager::checkCollision()
{
	for (int i = 0; i < this->player->bulletList.size(); i++)
	{
		for (int j = 0; j < this->invaderList.size(); j++)
		{
			if (Collision::PixelPerfectTest(this->player->bulletList[i]->bulletSprite, this->invaderList[j]->invaderSprite))
			{
				//delete invader from list
				this->invaderList.erase(this->invaderList.begin() + j);

				//Invader die sound
				this->musicPlayer->openMusic(this->deadInvaderSoundPath, false);
				this->musicPlayer->playMusic();

				//delete bullet from list
				this->player->bulletList.at(i);
				this->player->bulletList.erase(this->player->bulletList.begin() + i);

				//increase score of player
				this->player->score += 20;

				//check most left and most right invader in the list
				findMostLeftandRightInvader();
				break;
			}
			else if (this->isUfoAlive && Collision::PixelPerfectTest(this->player->bulletList[i]->bulletSprite, this->ufo->ufoSprite))
			{
				//Don't draw the ufo anymore
				delete this->ufo;
				this->ufo = nullptr;

				this->isUfoAlive = false;

				//Ufo explosion sound
				this->musicPlayer->openMusic(this->explosionSoundPath, false);
				this->musicPlayer->playMusic();

				//increase score of player
				this->player->score += 150;
				break;
			}
		}
	}
}

/// <summary>
/// Spawn an ufo
/// </summary>
/// <param name="speed"></param>
/// <param name="gameWindow"></param>
void GameManager::spawnUfo(int speed)
{
	if (this->ufo != nullptr)
		delete this->ufo;

	this->ufo = new Ufo(speed, this->invaderSheetPath, this->gameWindow);
	this->isUfoAlive = true;
}

/// <summary>
/// Draws all Sprites on the screen
/// </summary>
/// <param name="gameWindow"></param>
void GameManager::render() {
	switch (gameState)
	{

	//Menu
	case GAME_STATE_MENU:
		menu->draw(this->gameWindow);
		break;

	//Running
	case GAME_STATE_RUNNING:

		//draw invaders
		for (int i = 0; i < this->invaderList.size(); i++)
		{
			this->invaderList.at(i)->draw(this->gameWindow);
		}

		//draw player
		this->player->draw(this->gameWindow);

		//draw ufo
		if (this->isUfoAlive)
			this->ufo->draw(this->gameWindow);
		break;

	//Pause Text
	case GAME_STATE_PAUSE:
		this->gameWindow->draw(this->pauseText);
		break;
	}
}

/// <summary>
/// When called pauses the game if it's runnning
/// </summary>
void GameManager::pauseGame()
{
	if (this->gameState == GAME_STATE_RUNNING)
		this->gameState = GAME_STATE_PAUSE;
}

/// <summary>
/// Searches in an invader list the most left and right invader.
/// This is used in the move invader method since if the most left or right invader "hit"
/// the window border all the rows need to shift down
/// Call only when invader was shot to update most left and right invader in all rows
/// </summary>
void GameManager::findMostLeftandRightInvader()
{
	int invadersLeftInRow = 0;
	float invaderMLXPos = this->gameWindow->getSize().x;
	float invaderMRXPos = 0.0f;

	//row number of first invader in the list
	int rowNumber = invadersPerRow;
	//int indexOfFirstInvader = 0;
	for (int i = 0; i < this->invaderList.size(); i++)
	{
		////If next invader is in the same row as past one add to invaders left
		//if (this->invaderList.at(i)->rowNumber == rowNumber)
		//	invadersLeftInRow++;
		////Else means we are in a new row so reset counters
		//else
		//{
		//	this->mostLeftInvaderIndex = i;
		//	rowNumber = this->invaderList.at(i)->rowNumber;
		//}
		////If all the invaders are left in the row
		////it means this row has to have the ML and MR invader
		//if (this->invadersPerRow == invadersLeftInRow)
		//{
		//	this->mostLeftInvaderIndex = i - invadersPerRow + 1;
		//	this->mostRightInvaderIndex = i;
		//	invadersLeftInRow = 0;
		//	break;
		//}

		if (this->invaderList.at(i)->invaderSprite.getPosition().x > invaderMRXPos)
		{
			invaderMRXPos = this->invaderList.at(i)->invaderSprite.getPosition().x;
			this->mostRightInvaderIndex = i;
		}
		if (this->invaderList.at(i)->invaderSprite.getPosition().x < invaderMLXPos)
		{
			invaderMLXPos = this->invaderList.at(i)->invaderSprite.getPosition().x;
			this->mostLeftInvaderIndex = i;
		}
	}
}