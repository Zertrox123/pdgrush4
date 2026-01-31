#include <ncurses.h>
#include "Ncurses.hpp"

bool Display::Ncurses::init() {
    initscr();
	cbreak();
    noecho();
    keypad(stdscr, TRUE);
    curs_set(0);
    timeout(1);

    return true;
};

Display::Ncurses::~Ncurses() {
    clear();
    endwin();
    exit_curses(0);
}

void Display::Ncurses::NewSection(std::string Name) {
    if (actual_win != nullptr) {
        delwin(actual_win);
    }

    winh = 5;
    winw = getWindowSize();
    WINDOW *win = newwin(5, winw, staticpadding + padding, 0);
    box(win, 0, 0);
    mvwprintw(win, 0, 2, Name.c_str());
    actual_win = win;
    wrefresh(actual_win);
    padding += winh;
};

bool Display::Ncurses::drawText(std::string text) {
    mvwprintw(actual_win, winh / 2, winw / 2 - (text.length() / 2), text.c_str());
    wrefresh(actual_win);
    return true;
};

void Display::Ncurses::refresh() {
    padding = 0;
    wrefresh(actual_win);
};

void Display::Ncurses::setscroll(int value) {
    staticpadding += value;
    if (staticpadding > 0)
        staticpadding = 0;
}
