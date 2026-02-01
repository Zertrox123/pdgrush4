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
    timeout(500);
    start_color();
    init_pair(1, 13, 0);


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
    winw = getCWindowSize();
    WINDOW *win = newwin(winh, winw, staticpadding + padding, 0);
    wattron(win, COLOR_PAIR(1));
    box(win, 0, 0);
    mvwprintw(win, 0, 2, Name.c_str());
    actual_win = win;
    wrefresh(actual_win);
    wattroff(win, COLOR_PAIR(1));
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
    
    drawcall += 1;
    wrefresh(actual_win);
    return true;
};

void Display::Ncurses::refresh() {
    clear();
    padding = 0;
    wrefresh(actual_win);
    drawcall = 0;
    ::refresh();
    init_pair(1, lastcolor, 0);
    lastcolor++;
    if (lastcolor >= COLORS)
        lastcolor = 0;

};

void Display::Ncurses::setscroll(int value) {
    staticpadding += value;

    if (staticpadding > 0)
        staticpadding = 0;

    int overflow = drawcall - 6;
    if (overflow < 0)
        overflow = 0;

    int minPadding = -overflow * winh;

    if (staticpadding < minPadding)
        staticpadding = minPadding;
}
