#include <iostream>
#include "Sfml.hpp"
#include "Modules/Hostname.hpp"

bool Display::Sfml::init() {
    window = new sf::RenderWindow();
    font = new sf::Font();
    if (!font->openFromFile("assets/comic.ttf")) {
        std::cerr << "Cannot open font file" << std::endl;
        delete window;
        delete font;
        exit(1);
    }
    window->create(sf::VideoMode(sf::Vector2u{700, 800}), "myGKrellm", sf::Style::Titlebar | sf::Style::Close);
    return true;
};

Display::Sfml::~Sfml() {
    delete window;
    delete font;
}

void Display::Sfml::NewSection(std::string Name) {
    std::cout << Name << std::endl;
    return;
};

bool Display::Sfml::drawText(std::string text) {
    std::cout << text << std::endl;
    sf::Text sftext(*font);
    sftext.setString(text);
    sftext.setCharacterSize(30);
    sftext.setFillColor(sf::Color::White);
    sftext.setPosition({10, 10});
    window->draw(sftext);
    return true;
};

void Display::Sfml::refresh()
{
    Hostname host;
    while (window->isOpen()) {
        while (auto event = window->pollEvent()) {
            if (event->is<sf::Event::Closed>())
                window->close();
        }
        window->clear();
        host.Draw(this);
        window->display();
    }
}
