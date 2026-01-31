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

void Display::Sfml::NewSection(std::string name)
{
    float padding = 40.0f;
    float winsize_x = static_cast<float>(window->getSize().x);
    this->lastsectionpos = this->lastsectionpos + (this->sectionheight + 15.0f);
    this->sectionheight = 130.0f;
    this->cursor = this->lastsectionpos + 50.0f;

    sf::Text title(*font);
    title.setString(name);
    title.setCharacterSize(23);
    title.setFillColor(sf::Color::White);
    
    float titlex = (winsize_x - title.getLocalBounds().size.x) / 2.0f;
    float titley = static_cast<float>(this->lastsectionpos - 6.2f) - title.getLocalBounds().position.y;
    title.setPosition(sf::Vector2f(titlex, titley));
    
    sf::RectangleShape topline_left({titlex - padding, 5.0f});
    topline_left.setFillColor(sf::Color::Green);
    topline_left.setPosition(sf::Vector2f(padding, static_cast<float>(this->lastsectionpos)));
    window->draw(topline_left);
    
    float linerightwidth = winsize_x - padding - (titlex + (title.getLocalBounds().size.x + 5));
    sf::RectangleShape topline_right({linerightwidth, 5.0f});
    topline_right.setFillColor(sf::Color::Green);
    topline_right.setPosition(sf::Vector2f(titlex + (title.getLocalBounds().size.x + 5), static_cast<float>(this->lastsectionpos)));
    window->draw(topline_right);
    
    sf::RectangleShape leftline({5.0f, this->sectionheight});
    leftline.setFillColor(sf::Color::Green);
    leftline.setPosition(sf::Vector2f(padding, static_cast<float>(this->lastsectionpos)));
    window->draw(leftline);

    sf::RectangleShape rightline({5.0f, this->sectionheight});
    rightline.setFillColor(sf::Color::Green);
    rightline.setPosition(sf::Vector2f(winsize_x - padding - 5.0f, static_cast<float>(this->lastsectionpos)));
    window->draw(rightline);
    
    sf::RectangleShape downline({winsize_x - 2.0f * padding, 5.0f});
    downline.setFillColor(sf::Color::Green);
    downline.setPosition(sf::Vector2f(padding, static_cast<float>(this->lastsectionpos) + this->sectionheight));
    window->draw(downline);
    
    window->draw(title);
}

bool Display::Sfml::drawText(std::string text)
{
    sf::Text sftext(*font);
    sftext.setString(text);
    sftext.setCharacterSize(20);
    sftext.setFillColor(sf::Color::White);
    float width = sftext.getLocalBounds().size.x;
    sftext.setPosition({(window->getSize().x - width) / 2.0f, this->cursor + 10.0f});
    window->draw(sftext);
    this->cursor = this->cursor + 25.0f;
    return true;
}

void Display::Sfml::refresh()
{
    Hostname host;
    while (window->isOpen()) {
        while (auto event = window->pollEvent()) {
            if (event->is<sf::Event::Closed>())
                window->close();
        }
        this->lastsectionpos = 0;
        this->sectionheight = 0;
        this->cursor = 0;
        window->clear();
        host.Draw(this);
        window->display();
    }
}
