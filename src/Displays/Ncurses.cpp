#include <sstream>
#include <ncurses.h>
#include <vector>
#include "Ncurses.hpp"

bool Display::Ncurses::init() {
    initscr();
	cbreak();
    noecho();
    keypad(stdscr, TRUE);
    curs_set(0);
    timeout(1000);

    return true;
};

Display::Ncurses::~Ncurses() {
    clear();
    ::refresh();
    clear();
    endwin();
    exit_curses(0);
}

void Display::Ncurses::NewSection(std::string Name) {
    if (actual_win != nullptr) {
        delwin(actual_win);
    }

    winh = 7;
    winw = getWindowSize();
    WINDOW *win = newwin(winh, winw, staticpadding + padding, 0);
    box(win, 0, 0);
    mvwprintw(win, 0, 2, Name.c_str());
    actual_win = win;
    wrefresh(actual_win);
    padding += winh;
};

bool Display::Ncurses::drawText(std::string text) {
    std::vector<std::string> lines;
    std::stringstream ss(text);
    std::string line;
    
    while (std::getline(ss, line, '\n')) {
        lines.push_back(line);
    }
    
    int start_y = winh / 2 - (lines.size() / 2);
    
    for (size_t i = 0; i < lines.size(); i++) {
        int x = winw / 2 - (lines[i].length() / 2);
        mvwprintw(actual_win, start_y + i, x, lines[i].c_str());
    }
    
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
