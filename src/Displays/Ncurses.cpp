#include <ncurses.h>
#include "Ncurses.hpp"

bool Display::Ncurses::init() {
    initscr();
	cbreak();
    noecho();
    keypad(stdscr, TRUE);

    return true;
};

Display::Ncurses::~Ncurses() {
    endwin();
}

void Display::Ncurses::NewSection(std::string Name) {
    WINDOW *win = newwin(10, getWindowSize(), 0, 0);
    box(win, 0, 0);
    mvwprintw(win, 0, 2, Name.c_str());


    mvwprintw(win, 2, 2, "Content inside the box");

    refresh();
    wrefresh(win);
};

bool Display::Ncurses::drawText(std::string text) {
    mvprintw(2, 2, text.c_str());
    return true;
};
