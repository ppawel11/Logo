#ifndef TKOM_IOCONTROLLER_H
#define TKOM_IOCONTROLLER_H

#include <iostream>

class IOController {
public:
    IOController() = default;

    static void write(const std::string& msg);
    static std::string read();
};


#endif //TKOM_IOCONTROLLER_H
