#include <iostream>
#include "Sfml.hpp"

bool Display::Sfml::init() {
    window = new sf::RenderWindow();
    window->create(sf::VideoMode(sf::Vector2u{700, 800}), "myGKrellm", sf::Style::Titlebar | sf::Style::Close);
    return true;
};

Display::Sfml::~Sfml() {
}

void Display::Sfml::NewSection(std::string Name) {
    std::cout << Name << std::endl;
    return;
};

bool Display::Sfml::drawText(std::string text) {
    std::cout << text << std::endl;
    return true;
};

void Display::Sfml::refresh()
{
    while (window->isOpen()) {
        while (auto event = window->pollEvent()) {
            if (event->is<sf::Event::Closed>())
                window->close();
        }
    }
    window->clear();
    window->display();
}
