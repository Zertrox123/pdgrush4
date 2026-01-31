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
    view = new sf::View(sf::FloatRect(sf::Vector2f(0.0f, 0.0f), sf::Vector2f(static_cast<float>(window->getSize().x), static_cast<float>(window->getSize().y))));
    return true;
};

Display::Sfml::~Sfml() {
    delete window;
    delete font;
    delete view;
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
    this->currentcontent = this->lastsectionpos + this->sectionheight + 20.0f;
    return;
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
            if (auto *data = event->getIf<sf::Event::MouseWheelScrolled>()) {
                float maxscrolling = this->currentcontent - window->getSize().y;
                this->scrolloffset = this->scrolloffset - (data->delta * 45.0f);
                if (this->scrolloffset < 0.0f)
                    this->scrolloffset = 0.0f;
                if (this->scrolloffset > maxscrolling)
                    this->scrolloffset = maxscrolling;
                if (maxscrolling < 0.0f)
                    maxscrolling = 0.0f;
            }
            if (event->is<sf::Event::Closed>())
                window->close();
        }
        this->lastsectionpos = 0;
        this->sectionheight = 0;
        this->cursor = 0;
        window->clear();
        view->setCenter(sf::Vector2f(window->getSize().x / 2.0f, window->getSize().y / 2.0f + this->scrolloffset));
        window->setView(*view);
        for (int i = 0; i < 30; i++)
            host.Draw(this);
        window->display();
        window->setView(window->getDefaultView());
    }
}
