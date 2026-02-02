#include "RaylibDisplay.hpp"
#include "../src/Modules/Hostname.hpp"
#include "../src/Modules/Kernel.hpp"
#include "../src/Modules/Temp.hpp"
#include "../src/Modules/Cpu.hpp"
#include "../src/Modules/Users.hpp"
#include "../src/Modules/Battery.hpp"
#include "../src/Modules/Ram.hpp"
#include "../src/Modules/Date.hpp"
#include "../src/Modules/Network.hpp"
#include "../src/Modules/Disk.hpp"

int main() {
    RaylibDisplay* display = new RaylibDisplay();
    display->init();
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
    while (!display->shouldClose()) {
        display->refresh();
        hm.Draw(display);
        hm2.Draw(display);
        tp.Draw(display);
        cpu.Draw(display);
        usr.Draw(display);
        batt.Draw(display);
        ram.Draw(display);
        date.Draw(display);
        ntwrk.Draw(display);
        disk.Draw(display);
        display->endFrame();
    }
    delete display;
    return 0;
}