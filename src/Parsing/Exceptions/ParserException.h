#ifndef TKOM_PARSEREXCEPTION_H
#define TKOM_PARSEREXCEPTION_H

class ParserException : public std::runtime_error {
public:
    ParserException(const std::string &msg_, unsigned int line_, unsigned int column_) : std::runtime_error{
            std::string(msg_ + " at line: ") + std::to_string(line_) + " column: " + std::to_string(column_)
    } {}
};

#endif //TKOM_PARSEREXCEPTION_H
