#ifndef TKOM_TOKEN_H
#define TKOM_TOKEN_H

#include <stdexcept>
#include "TokenType.h"
#include "../../Source/Position.h"

class Token {
private:
    TokenType type;
    Position position;

    std::string literal_value;
    int numeric_value;
public:
    Token(TokenType _type, Position _position, std::string _literal);

    Token(TokenType _type, Position _position, int _numeric);

    Token(TokenType _type, Position _position);

    TokenType getType() const;

    const Position &getPosition() const;

    const std::string &getLiteralValue() const;

    int getNumericValue() const;
};



#endif //TKOM_TOKEN_H


