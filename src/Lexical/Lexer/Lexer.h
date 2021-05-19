#ifndef TKOM_LEXER_H
#define TKOM_LEXER_H

#include "../Token/TokenType.h"
#include "../../Source/StringStream/StringStreamSource.h"
#include "../Token/Token.h"

#include <memory>
#include <map>

class Lexer {
    SourceInterface * scanner;
    Token current_token;
    Position current_token_position;

    int max_literal_length = 20;
    int max_string_length = 200;

    std::map<std::string, TokenType> literal_token_map =
            {
                std::pair<std::string, TokenType>("if", TokenType::IF),
                std::pair<std::string, TokenType>("else", TokenType::ELSE),
                std::pair<std::string, TokenType>("for", TokenType::FOR),
                std::pair<std::string, TokenType>("while", TokenType::WHILE),
                std::pair<std::string, TokenType>("repeat", TokenType::REPEAT),
                std::pair<std::string, TokenType>("func", TokenType::FUNC),
                std::pair<std::string, TokenType>("define", TokenType::DEFINE),
                std::pair<std::string, TokenType>("and", TokenType::AND),
                std::pair<std::string, TokenType>("or", TokenType::OR),
                std::pair<std::string, TokenType>("false", TokenType::FALSE),
                std::pair<std::string, TokenType>("true", TokenType::TRUE),
                std::pair<std::string, TokenType>("return", TokenType::RETURN),
                std::pair<std::string, TokenType>("var", TokenType::VAR)
            };

    std::map<char, TokenType> single_char_token_map =
            {
                std::pair<char, TokenType>(',',TokenType::COMMA),
                std::pair<char, TokenType>('(',TokenType::PARENTHESIS_OPEN),
                std::pair<char, TokenType>(')',TokenType::PARENTHESIS_CLOSE),
                std::pair<char, TokenType>('[',TokenType::BRACKET_OPEN),
                std::pair<char, TokenType>(']',TokenType::BRACKET_CLOSE),
                std::pair<char, TokenType>('{',TokenType::CURLY_BRACKET_OPEN),
                std::pair<char, TokenType>('}',TokenType::CURLY_BRACKET_CLOSE),
                std::pair<char, TokenType>(';',TokenType::SEMICOLON),
                std::pair<char, TokenType>(':',TokenType::COLON),
                std::pair<char, TokenType>('+',TokenType::PLUS),
                std::pair<char, TokenType>('-',TokenType::MINUS),
                std::pair<char, TokenType>('/',TokenType::DIVIDE),
                std::pair<char, TokenType>('*',TokenType::MULTIPLY),
                std::pair<char, TokenType>('&',TokenType::AND_SYMBOLIC),
                std::pair<char, TokenType>('|',TokenType::OR_SYMBOLIC)
            };

public:
    Lexer(SourceInterface * _scanner):
        scanner{ _scanner },
        current_token{ TokenType::INVALID, Position(0, 0, -1) },
        current_token_position{ 0, 0, 0 }
        {};

    Lexer():
        scanner{ nullptr },
        current_token{ TokenType::INVALID, Position(0, 0, -1) },
        current_token_position{ 0, 0, 0 }
    {};

    const Token &getCurrentToken() const;

    const Token &getNextToken();

    int getMaxLiteralLength() const;

    void setMaxLiteralLength(int maxLiteralLength);

    int getMaxStringLength() const;

    void setMaxStringLength(int maxStringLength);

    void setScanner(SourceInterface * _scanner);

private:
    Token getStringToken();
    Token getNumericToken();
    Token getLiteralToken();
    Token getComparisionToken();
};

#endif //TKOM_LEXER_H
