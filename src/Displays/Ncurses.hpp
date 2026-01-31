#pragma once
#include "IDisplay.hpp"
#include <ncurses.h>
#include <string>
#include <sys/ioctl.h>
#include <unistd.h>

namespace Display{ 
    class Ncurses: public Krell::IDisplay {
private:
    int getWindowSize() {
        struct winsize w;
        ioctl(STDOUT_FILENO, TIOCGWINSZ, &w);
        return w.ws_col;
    };
    WINDOW *actual_win = nullptr;
    int winh = 1;
    int winw = 1;
    int padding = 0;
    int staticpadding = 0;

public:
        ~Ncurses() override;
        bool init() override;

        void NewSection(std::string Name) override;
        bool drawText(std::string text) override;
        void refresh() override;
        void setscroll(int value);
    };
}
