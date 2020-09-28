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
invadersPerRow(12), rowsOfInvaders(1), level(0), player(nullptr), invaderShootingFrequency(0.1f), pauseTime(0.0f), 
invaderInitialSpeed(60), invaderYStart(120)
{
	this->gameWindow = gameWindow;

	//Game is designed for 1200x and 800y window size if bigger draw a border
	if (this->gameWindow->getSize().x > 1200 || this->gameWindow->getSize().y > 800)
	{
		initEdge();
	}

	if (this->gameWindow->getSize().x > 1200)
	{
		this->borderOffset = (this->gameWindow->getSize().x - 1200) / 2 + 25;
	}
	if (this->gameWindow->getSize().y > 800)
	{
		this->invaderYStart = ((this->gameWindow->getSize().y - 800) / 2 + 25);
	}

	//init game state
	this->gameState = GAME_STATE_MENU;

	this->invaderMusicPlayer = new MusicPlayer(5.0f);
	this->playerMusicPlayer = new MusicPlayer(10.0f);
	this->ufoMusicPlayer = new MusicPlayer(10.0f);

	//init font
	this->pixelFont = sf::Font();
	if (!pixelFont.loadFromFile(this->pixelFontPath))
	{
		//Invader Font could not be loaded / found
		std::cout << "Font could not be loaded" << std::endl;
	}

	//init menu
	menu = new Menu(this->gameWindow, &this->pixelFont);

	//Pause text init
	initText(&this->pauseText, "Press Enter to unpause", 40, true, true);
	
	//level text init
	initText(&this->levelText, std::string("Level " + std::to_string(this->level)), 30, true, false);
	this->levelText.setPosition(sf::Vector2f(this->gameWindow->getSize().x / 2, levelText.getGlobalBounds().height));
}

GameManager::~GameManager() {
	if (!invaderList.empty())
	{
		for (int i = this->invaderList.size() - 1; i >= 0; i--)
		{
			delete this->invaderList.at(i);
		}
	}

	if (!invaderBullets.empty())
	{
		for (int i = invaderBullets.size() - 1; i >= 0; i--)
		{
			delete this->invaderBullets.at(i);
		}
	}

	if (!ufoList.empty())
	{
		for (int i = this->ufoList.size() - 1; i >= 0; i--)
		{
			delete ufoList.at(i);
		}
	}

	delete menu;
	delete player;
	delete invaderMusicPlayer;
	delete playerMusicPlayer;
	delete ufoMusicPlayer;
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
		//update menu state and change if user clicks on play
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
		initInvaders(invadersPerRow, rowsOfInvaders, this->invaderInitialSpeed);
		this->player = new Player(&this->pixelFont, this->playerSheetPath, this->gameWindow);

		this->gameState = GAME_STATE_RUNNING;
	}

	//Game Running
	if (this->gameState == GAME_STATE_RUNNING)
	{
		//check if invader collide with player
		if (this->invaderList.at(this->invaderList.size() - 1)->invaderSprite.getPosition().y >
			(this->player->playerSprite.getPosition().y - this->player->playerSprite.getLocalBounds().height))
		{
			this->gameState = GAME_STATE_GAME_OVER;
		}

		//Pause the game if P is pressed
		if (InputHandler::isKeyPressed(sf::Keyboard::P))
		{
			this->pauseClock.restart();
			pauseGame();
		}

		//Update Player
		this->player->update(deltaTime);

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

		//Update ufo position
		for (int i = 0; i < this->ufoList.size(); i++)
		{
			this->ufoList.at(i)->update(this->gameWindow, deltaTime);
		}

		//Spawn an Ufo each 20sec
		if ((this->ufoSpawnClock.getElapsedTime().asSeconds() - pauseTime) > 20.0f)
		{
			pauseTime = 0.0f;
			this->ufoSpawnClock.restart();
			spawnUfo(400);
		}

		//delete ufos out of bounds
		for (int i = 0; i < this->ufoList.size(); i++)
		{
			if (this->ufoList.at(i)->ufoSprite.getPosition().x < 0)
			{
				delete ufoList.at(i);
				this->ufoList.erase(this->ufoList.begin() + i);
			}
		}

		//Make invaders shoot
		if (this->invaderClock.getElapsedTime().asSeconds() > this->invaderShootingFrequency && !this->player->exploded)
		{
			this->invaderClock.restart();
			invaderShoot();
		}

		//Remove bullets out of bounds
		for (int i = this->invaderBullets.size() - 1; i >= 0; i--)
		{
			if (this->invaderBullets.at(i)->bulletSprite.getPosition().y > this->gameWindow->getSize().y)
			{
				delete invaderBullets.at(i);
				this->invaderBullets.erase(this->invaderBullets.begin() + i);
			}
		}

		//Update invaders bullets
		for (int i = 0; i < this->invaderBullets.size(); i++)
			this->invaderBullets.at(i)->update(deltaTime, this->gameWindow);

		//Check for Collisions between Invaders and Bullets
		checkCollision();

		//check if player lost all lives
		if (this->player->lives == 0)
		{
			this->gameState = GAME_STATE_GAME_OVER;
		}
	}

	if (this->gameState == GAME_STATE_PAUSE)
	{
		//Unpause the game if Enter is pressed;
		if (InputHandler::isKeyPressed(sf::Keyboard::Enter))
		{
			pauseTime = this->pauseClock.getElapsedTime().asSeconds();
			this->gameState = GAME_STATE_RUNNING;
		}
	}
}

/// <summary>
/// Initializes the invaders
/// </summary>
/// <param name="invaderAmountPerRow"></param>
/// <param name="rowsOfInvaders"></param>
void GameManager::initInvaders(int invaderAmountPerRow, int rowsOfInvaders, int speed) {
	//Space between top of Window on first row of invaders
	int invaderYOffset = this->invaderYStart;

	for (int j = 0; j < rowsOfInvaders; j++) {
		for (int i = 0; i < invaderAmountPerRow; i++)
		{
			Invader* invader = new Invader(this->invaderSheetPath, j, (int)(MAX_INVADER_TYPES / (float)rowsOfInvaders * j), speed);
			invader->setPosition(sf::Vector2f((i * invader->rowHeigth) + borderOffset + 20, invaderYOffset));
			this->invaderList.push_back(invader);
		}
		//Space between each invader row
		invaderYOffset += this->invaderList.at(0)->rowHeigth;
	}

	//init most left and right invader indices
	this->mostLeftInvaderIndex = 0;
	this->mostRightInvaderIndex = invadersPerRow - 1;

	//init bottom invader indices
	for (int i = 0; i < invaderAmountPerRow; i++)
	{
		this->bottomInvaderList.push_back(this->invaderList.size() - i - 1);
	}
}

/// <summary>
/// Checks for collisions between Bullets, Invaders and the player
/// Removes Invader and Bullet from list
/// </summary>
void GameManager::checkCollision()
{
	//check collision of invader bullets with player
	for (int i = 0; i < this->invaderBullets.size(); i++)
	{
		if (Collision::PixelPerfectTest(this->player->playerSprite, this->invaderBullets.at(i)->bulletSprite))
		{
			//if player hit delete all invader bullets to prevent double death
			for (int i = this->invaderBullets.size() - 1; i >= 0; i--)
			{
				delete invaderBullets.at(i);
				this->invaderBullets.erase(this->invaderBullets.end() - 1);
			}

			//if collision detected
			this->player->playerExplode();
			break;
		}
	}

	//check player bullet collisions
	for (int i = 0; i < this->player->bulletList.size(); i++)
	{
		//check if player bullet hit invader
		for (int j = 0; j < this->invaderList.size(); j++)
		{
			if (Collision::PixelPerfectTest(this->player->bulletList[i]->bulletSprite, this->invaderList[j]->invaderSprite))
			{
				//delete invader from list
				delete this->invaderList.at(j);
				this->invaderList.erase(this->invaderList.begin() + j);

				//Invader die sound
				this->playerMusicPlayer->openMusic(this->deadInvaderSoundPath, false);
				this->playerMusicPlayer->playMusic();

				//delete bullet from list
				delete this->player->bulletList.at(i);
				this->player->bulletList.erase(this->player->bulletList.begin() + i);

				//increase score of player
				this->player->score += 20;

				//check if all invaders dead
				if (this->invaderList.empty())
				{
					nextLevel();
					break;
				}

				//check most left and most right invader in the list
				findMostLeftandRightInvader();
				findMostBottomInvaders();

				break;
			}

			//check if player bullets hit ufo
			else {
				for (int i = 0; j < this->ufoList.size(); j++)
				{
					if (Collision::PixelPerfectTest(this->player->bulletList[i]->bulletSprite, this->ufoList.at(j)->ufoSprite))
					{
						//delete ufo
						delete this->ufoList.at(j);
						this->ufoList.erase(this->ufoList.begin() + j);

						//Ufo explosion sound
						this->ufoMusicPlayer->openMusic(this->explosionSoundPath, false);
						this->ufoMusicPlayer->playMusic();

						//increase score of player
						this->player->score += 150;
						break;
					}
				}
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
	Ufo* ufo = new Ufo(speed, this->invaderSheetPath, this->gameWindow);
	this->ufoList.push_back(ufo);
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
		//draw border
		this->gameWindow->draw(this->border);

		//draw invaders
		for (int i = 0; i < this->invaderList.size(); i++)
		{
			this->invaderList.at(i)->draw(this->gameWindow);
		}

		//draw player
		this->player->draw();

		//draw ufo
		for (int i = 0; i < this->ufoList.size(); i++)
		{
			this->ufoList.at(i)->draw(gameWindow);
		}

		//draw invader bullets
		for (int i = 0; i < this->invaderBullets.size(); i++)
		{
			this->invaderBullets.at(i)->draw(this->gameWindow);
		}

		//draw level count
		this->gameWindow->draw(this->levelText);

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

/// <summary>
/// Searches in the current invader list for the most bottom one, that will be able to shoot
/// </summary>
void GameManager::findMostBottomInvaders()
{
	int currentMostBottom = 0;
	std::vector<short> checkedXList;
	int shift = 0;
	this->bottomInvaderList.clear();
	for (int i = 0; i < this->invaderList.size(); i++)
	{
		for (int y = i; y < this->invaderList.size(); y++)
		{
			//if any other invader in the list has the same x cords, he's under him
			//last one will be the most bottom one of that line
			if (this->invaderList.at(i)->invaderSprite.getPosition().x == this->invaderList.at(y)->invaderSprite.getPosition().x)
			{
				currentMostBottom = y;
			}
		}
		if (std::find(bottomInvaderList.begin(), bottomInvaderList.end(), currentMostBottom) == bottomInvaderList.end())
			this->bottomInvaderList.push_back(currentMostBottom);
	}
}

/// <summary>
/// Make the invaders shoot the player
/// </summary>
void GameManager::invaderShoot()
{
	int indexOfInvaderShooting = rand() % this->bottomInvaderList.size();

	Bullet* invaderBullet = new Bullet(this->playerSheetPath,
		this->invaderList.at(this->bottomInvaderList.at(indexOfInvaderShooting))->invaderSprite.getPosition().x,
		this->invaderList.at(this->bottomInvaderList.at(indexOfInvaderShooting))->invaderSprite.getPosition().y, -1, true);
	this->invaderBullets.push_back(invaderBullet);

	//play shooting sound
	this->invaderMusicPlayer->openMusic(this->laserSoundPath, false);
	this->invaderMusicPlayer->playMusic();
}

void GameManager::nextLevel()
{
	//make game harder
	this->level++;
	this->levelText.setString(std::string("Level " + std::to_string(this->level)));
	this->invaderShootingFrequency = this->invaderShootingFrequency - 0.1f;
	this->invaderInitialSpeed = this->invaderInitialSpeed + 10;
	this->player->playerSprite.setPosition(sf::Vector2f(this->gameWindow->getSize().x / 2,
		this->gameWindow->getSize().y - this->player->playerSprite.getGlobalBounds().height / 2));
	if (this->rowsOfInvaders < 6)
	{
		this->rowsOfInvaders++;
	}

	//delete all ufos
	if (!this->ufoList.empty())
	{
		for (int i = this->ufoList.size() - 1; i >= 0; i--)
		{
			delete this->ufoList.at(i);
			this->ufoList.erase(this->ufoList.end() - 1);
		}
	}

	//delete all invader bullets
	if (!this->invaderBullets.empty())
	{
		for (int i = this->invaderBullets.size() - 1; i >= 0; i--)
		{
			delete this->invaderBullets.at(i);
			this->invaderBullets.erase(this->invaderBullets.end() - 1);
		}
	}

	//delete all player bullets
	if (!this->player->bulletList.empty())
	{
		for (int i = this->player->bulletList.size() - 1; i >= 0; i--)
		{
			delete this->player->bulletList.at(i);
			this->player->bulletList.erase(this->player->bulletList.end() - 1);
		}
	}

	initInvaders(this->invadersPerRow, this->rowsOfInvaders, this->invaderInitialSpeed);
}

void GameManager::initText(sf::Text* text, std::string string, unsigned int size, bool setOriginToCenter, bool setPositionToCenter)
{
	text->setFont(this->pixelFont);
	text->setString(string);
	text->setCharacterSize(size);

	if (setOriginToCenter)
		text->setOrigin(sf::Vector2f(text->getLocalBounds().width / 2, text->getLocalBounds().height / 2));
	
	if (setPositionToCenter)
		text->setPosition(sf::Vector2f(this->gameWindow->getSize().x / 2, this->gameWindow->getSize().y / 2));
}

void GameManager::initEdge()
{
	//Game is designed for 1200x and 800y window size if bigger draw a border
	if (this->gameWindow->getSize().x > 1200 || this->gameWindow->getSize().y > 800)
	{
		this->border = sf::RectangleShape(sf::Vector2f(1200, 800));
		this->border.setOrigin(sf::Vector2f(this->border.getLocalBounds().width / 2, this->border.getLocalBounds().height / 2));
		this->border.setPosition(sf::Vector2f(this->gameWindow->getSize().x / 2, this->gameWindow->getSize().y / 2));
		this->border.setFillColor(sf::Color::Transparent);
		this->border.setOutlineThickness(1.0f);
		this->border.setOutlineColor(sf::Color::White);

	}
}
