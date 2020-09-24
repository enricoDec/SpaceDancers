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

Application::Application(unsigned int windowWidth, unsigned int windowHeight, bool isFullScreen) {
    this->gameWindow = new sf::RenderWindow(sf::VideoMode(windowWidth, windowHeight), 
        "Space Dancers", isFullScreen ? sf::Style::Fullscreen : sf::Style::Titlebar | sf::Style::Close);
    
    gameManager = new GameManager(this->gameWindow);
}

Application::~Application() {
    delete gameWindow;
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
        this->gameManager->update();

        this->gameWindow->clear();
        this->gameManager->render();
        this->gameWindow->display();
        InputHandler::clearKeys();
    }
}
