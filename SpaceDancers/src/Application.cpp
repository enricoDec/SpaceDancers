/////////////////////////////////////
/// 
/// Source File: Application.cpp
/// 
/// AUTHOR: Enrico Gamil Toros de Chadarevian
/// MATRNR: 567011
/// CREATE DATE: 9/17/2020 1:58:20 PM
///
/////////////////////////////////////

#include "Application.h"
#include <iostream>

Application::Application(unsigned int windowWidth, unsigned int windowHeight, bool isFullScreen): isResetting(false) {
    this->gameWindow = new sf::RenderWindow(sf::VideoMode(windowWidth, windowHeight), 
        "Space Dancers", isFullScreen ? sf::Style::Fullscreen : sf::Style::Titlebar | sf::Style::Close);
    
    this->gameManager = new GameManager(this->gameWindow);
}

Application::~Application() {
    delete gameManager;
    delete gameWindow;
    delete gameOver;
}

/// <summary>
/// Main game loop
/// Register User Input
/// </summary>
void Application::startGame() {
    while (this->gameWindow->isOpen())
    {
        sf::Event event;
        while (this->gameWindow->pollEvent(event))
        {
            if (event.type == sf::Event::KeyPressed)
                InputHandler::registerPress(event.key.code);
            
            if (event.type == sf::Event::KeyReleased)
                InputHandler::registerRelease(event.key.code);
           
            if (event.type == sf::Event::Closed)
                this->gameWindow->close();

            else if (event.type == sf::Event::Resized)
            {
                std::cout << event.size.width << std::endl;
                gameWindow->setView(sf::View(sf::Vector2f(event.size.width / 2, event.size.height / 2), 
                    sf::Vector2f(event.size.width, event.size.height)));
            }
        }

        if (gameManager->gameState == GAME_STATE_GAME_OVER && isResetting == false)
        {
            this->isResetting = true;
            resetGame();
        }

        if (isResetting == true && gameOver->restart)
        {
            this->gameManager = new GameManager(gameWindow);
            delete this->gameOver;
            this->isResetting = false;
        }

        switch (isResetting)
        {
        case true:
            this->gameOver->update();
            this->gameWindow->clear();
            this->gameOver->render();
            break;
        case false:
            this->gameManager->update();
            this->gameWindow->clear();
            this->gameManager->render();
            break;
        }
        this->gameWindow->display();
        InputHandler::clearKeys();
    }
}

void Application::resetGame()
{
    this->gameOver = new GameOver(this->gameWindow, this->gameManager->player->score);
    delete this->gameManager;
}
