#include <ncurses.h>
#include "Displays/Ncurses.hpp"

int main(int argc, char **argv){
    if (argc > 1 && (std::string(argv[1]) == "-gui")) {   
        Display::Sfml a;
        a.init();
    } else {
        Display::Ncurses a;
        a.init();
        a.newSection("q");
        getch();
    }
}
