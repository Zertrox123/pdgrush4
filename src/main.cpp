#include <ncurses.h>
#include "Displays/Ncurses.hpp"

int main(){
    Display::Ncurses a;
    a.init();
    a.NewSection("q");
    getch();
}
