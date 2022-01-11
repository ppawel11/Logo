#ifndef TKOM_INTERPRETEREXVEPTION_H
#define TKOM_INTERPRETEREXVEPTION_H

class InterpreterException : public std::runtime_error {
public:
    InterpreterException(const std::string &msg_) : std::runtime_error{ msg_ } {}
};

#endif //TKOM_INTERPRETEREXVEPTION_H
