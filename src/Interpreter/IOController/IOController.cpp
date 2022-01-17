#include "IOController.h"

void IOController::write(const std::string& msg) {
    std::cout<<msg<<std::endl;
}

std::string IOController::read() {
    std::string user_msg;
    std::cin >> user_msg;
    return user_msg;
}
