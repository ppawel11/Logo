#ifndef TKOM_LEXICALEXCEPTION_H
#define TKOM_LEXICALEXCEPTION_H

#include <system_error>
#include <stdexcept>

class LexicalException : public std::runtime_error {
public:
    LexicalException(const std::string &msg_, unsigned int line_, unsigned int column_) : std::runtime_error{
            std::string(msg_ + " at line: ") + std::to_string(line_) + " column: " + std::to_string(column_)
    } {}
};


#endif //TKOM_LEXICALEXCEPTION_H
