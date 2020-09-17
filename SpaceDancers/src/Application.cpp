/////////////////////////////////////
/// 
/// Source File: Application.h
/// 
/// AUTHOR: Enrico Gamil Toros de Chadarevian
/// MATRNR: 567011
/// CREATE DATE: 9/17/2020 1:58:20 PM
///
/////////////////////////////////////

#include "Application.h"


Application::Application(unsigned int windowWidth, unsigned int windowHeight, bool isFullScreen) {
	this->gameWindow.create(sf::VideoMode(windowWidth, windowHeight), "Space Dancers", isFullScreen ? sf::Style::Fullscreen : sf::Style::Default);
}

Application::~Application() {

}


void Application::initGame() {

}

void Application::startGame() {
    while (this->gameWindow.isOpen())
    {
        sf::Event event;
        while (this->gameWindow.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                this->gameWindow.close();
        }

        this->gameWindow.clear();
        this->gameWindow.display();
    }
}
