#include <cstdio>
#include <ncurses.h>
#include "Displays/Ncurses.hpp"
#include "Displays/Sfml.hpp"
#include "Modules/Cpu.hpp"
#include "Modules/Date.hpp"
#include "Modules/Disk.hpp"
#include "Modules/Hostname.hpp"
#include "Modules/Kernel.hpp"
#include "Modules/Network.hpp"
#include "Modules/Ram.hpp"
#include "Modules/Temp.hpp"
#include "Modules/Users.hpp"
#include "Modules/Battery.hpp"

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
        Cpu cpu;
        Users usr;
        Battery batt;
        Ram ram;
        Date date;
        Network ntwrk;
        Disk disk;
        while (1) {
            a->refresh();
            hm.Draw(a);
            hm2.Draw(a);
            tp.Draw(a);
            cpu.Draw(a);
            usr.Draw(a);
            batt.Draw(a);
            ram.Draw(a);
            date.Draw(a);
            ntwrk.Draw(a);
            disk.Draw(a);
            int c = getch();
            if (c == 'q') break;
            if (c == KEY_DOWN) a->setscroll(-7);
            if (c == KEY_UP) a->setscroll(7);
        }
        delete a;
    }
}
