#include "ADisplay.hpp"
#include <string>
#include <sys/ioctl.h>
#include <unistd.h>


namespace Display{ 
    class Ncurses: Krell::IDisplay {
private:
    int getWindowSize() {
        struct winsize w;
        ioctl(STDOUT_FILENO, TIOCGWINSZ, &w);
        return w.ws_col;
    };

public:
        ~Ncurses() override;
        bool init() override;

        void NewSection(std::string Name) override;
        bool drawText(std::string text) override;
    };
}
