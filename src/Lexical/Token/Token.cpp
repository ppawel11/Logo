#include "Token.h"


Token::Token(TokenType _type, Position _position, std::string _literal):
        type {_type }, position{_position }, literal_value{std::move(_literal)}, numeric_value{-1}
{
    if( _type != TokenType::LABEL &&
        _type != TokenType::STRING &&
        _type != TokenType::INVALID
        )
        throw std::runtime_error("Invalid type of token with literal value");
}

Token::Token(TokenType _type, Position _position, int _numeric):
        type {_type }, position{_position }, literal_value{""}, numeric_value{_numeric}
{
    if( _type != TokenType::NUMBER &&
        _type != TokenType::INVALID
        )
        throw std::runtime_error("Invalid type of token with numeric value");
}

Token::Token(TokenType _type, Position _position):
        type {_type }, position{_position }, literal_value{""}, numeric_value{-1}
{
    if( _type == TokenType::LABEL ||
        _type == TokenType::STRING ||
        _type == TokenType::NUMBER
            )
        throw std::runtime_error("Value Token created without value");
}

TokenType Token::getType() const {
    return type;
}

const Position &Token::getPosition() const {
    return position;
}

const std::string &Token::getLiteralValue() const {
    return literal_value;
}

int Token::getNumericValue() const {
    return numeric_value;
}

