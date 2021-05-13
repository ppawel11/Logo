#ifndef TKOM_TOKENTYPE_H

enum class TokenType {
    FUNC,               // 0 // func
    DEFINE,             // 1 // define

    FOR,                // 2 // for
    WHILE,              // 3 // while
    REPEAT,             // 4 // repeat
    IF,                 // 5 // if
    ELSE,               // 6 // else

    PARENTHESIS_OPEN,   // 7 // (
    PARENTHESIS_CLOSE,  // 8 // )
    BRACKET_OPEN,       // 9 // [
    BRACKET_CLOSE,      // 10 // ]
    CURLY_BRACKET_OPEN, // 11 // {
    CURLY_BRACKET_CLOSE,// 12 // }
    COMMA,              // 13 // ,

    PLUS,               // 14 // +
    MINUS,              // 15 // -
    MULTIPLY,           // 16 // *
    DIVIDE,             // 17 // /

    ASSIGN,             // 18 // =
    EQUAL,              // 19 // ==
    NOT_EQUAL,          // 20 // !=
    LOWER,              // 21 // <
    LOWER_OR_EQUAL,     // 22 // <=
    GREATER,            // 23 // >
    GREATER_OR_EQUAL,   // 24 // >=

    LABEL,              // 25 // etykieta
    STRING,             // 26 // napis
    NUMBER,             // 27 // liczba

    TRUE,               // 28 // true
    FALSE,              // 29 // false
    AND,                // 30 // and
    AND_SYMBOLIC,       // 31 // &
    OR,                 // 32 // or
    OR_SYMBOLIC,        // 33 // |
    NEGATION,           // 34 // !

    SEMICOLON,          // 35 // ;
    INVALID,            // 36 // error
    END_OF_FILE,        // 37 // EOF
    COLON,              // 38 // :
    VAR,                // 39 // var
    RETURN              // 40 // return
};


#define TKOM_TOKENTYPE_H

#endif //TKOM_TOKENTYPE_H
