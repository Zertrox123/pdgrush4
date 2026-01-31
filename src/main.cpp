#include <ncurses.h>
#include "Displays/Ncurses.hpp"
#include "Displays/Sfml.hpp"

int main(int argc, char **argv){
    if (argc > 1 && (std::string(argv[1]) == "-gui")) {   
        Display::Sfml a;
        a.init();
        a.refresh();
    } else {
        Display::Ncurses a;
        a.init();
        a.NewSection("q");
        getch();
    }
}
