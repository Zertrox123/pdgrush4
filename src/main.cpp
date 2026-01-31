#include <cstdio>
#include <ncurses.h>
#include "Displays/Ncurses.hpp"
#include "Displays/Sfml.hpp"
#include "Modules/Hostname.hpp"
#include "Modules/Kernel.hpp"
#include "Modules/Temp.hpp"

int main(int argc, char **argv){
    if (argc > 1 && (std::string(argv[1]) == "-gui")) {   
         Display::Sfml a;
         a.init();
         a.refresh();
    } else {
        Display::Ncurses *a = new Display::Ncurses;
        a->init();
        Hostname hm;
        Kernel hm2;
        Temp tp;
        while (1) {
            a->refresh();
            hm.Draw(a);
            hm2.Draw(a);
            tp.Draw(a);
            int c = getch();
            if (c == 'q') break;
            if (c == KEY_DOWN) a->setscroll(-5);
            if (c == KEY_UP) a->setscroll(5);
        }
        delete a;
    }
}
