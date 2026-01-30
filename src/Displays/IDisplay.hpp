#include <string>
#include <sys/types.h>
namespace Krell{ 
    class IDisplay {
private:

public:
        virtual ~IDisplay()  {};
        virtual bool init() = 0;

        virtual void NewSection(std::string Name) = 0;
        virtual bool drawText(std::string text) = 0;
    };
}
