#include "Lexer.h"

const Token &Lexer::getNextToken() {
    if( scanner == nullptr )
        throw std::runtime_error("Lexer scanner not initialized");

    char next_char = scanner->getNextChar();

    while( std::isblank(next_char) )
    {
        next_char = scanner->getNextChar();
    }

    current_token_position = scanner->getCurrentPosition();

    if( scanner->eof() )
    {
        current_token = Token(TokenType::END_OF_FILE, current_token_position);
        return current_token;
    }

    if( single_char_token_map.find(next_char) != single_char_token_map.end() )
        current_token = Token( single_char_token_map[next_char], current_token_position );
    else if( next_char == '"')
        current_token = getStringToken();
    else if( std::isdigit(next_char) )
        current_token = getNumericToken();
    else if( std::isalpha( next_char ) )
        current_token = getLiteralToken();
    else
        current_token = getComparisionToken();

    return current_token;
}

Token Lexer::getStringToken() {
    std::string str = "";
    char next_char = scanner->getNextChar();

    while( !scanner->eof() && next_char != '"' )  //
    {
        if( next_char == 0x5C )
        {
            next_char = scanner->getNextChar();
            if( scanner->eof() )
            {
                throw LexicalException("eof while scanning string", current_token_position.line, current_token_position.sign);
            }
        }

        str.append(1, next_char);
        if( str.length() > max_string_length )
        {
            throw LexicalException("string too long", current_token_position.line, current_token_position.sign);
        }

        next_char = scanner->getNextChar();
    }

    return Token( TokenType::STRING, current_token_position, str );
}

Token Lexer::getNumericToken() {
    std::string number;
    number.append(1, scanner->getCurrentChar() );

    while( std::isdigit( scanner->peek() ) )
    {
        number.append(1, scanner->getNextChar());
    }

    return Token( TokenType::NUMBER, current_token_position, std::stol(number.c_str()));
}

Token Lexer::getLiteralToken() {
    std::string literal;
    literal.append(1, scanner->getCurrentChar() );
    int literal_length = 1;

    while( std::isalpha( scanner->peek() ) || '_' == scanner->peek() || std::isdigit( scanner->peek() ) )
    {
        literal_length++;
        if( literal_length > max_literal_length )
        {
            throw LexicalException("literal too long", current_token_position.line, current_token_position.sign );
        }
        literal.append(1, scanner->getNextChar());
    }

    if( literal_token_map.find(literal) != literal_token_map.end() )
    {
        return Token( literal_token_map[literal], current_token_position );
    }
    else
        return Token(TokenType::LABEL, current_token_position, literal );
}

Token Lexer::getComparisionToken() {
    char current_char = scanner->getCurrentChar();

    bool next_is_equal = false;
    if (scanner->peek() == '=')
    {
        scanner->getNextChar();
        next_is_equal = true;
    }

    switch (current_char)
    {
        case '<':
            if( next_is_equal )
                return Token( TokenType::LOWER_OR_EQUAL, current_token_position );
            return Token( TokenType::LOWER, current_token_position );
        case '>':
            if( next_is_equal )
                return Token( TokenType::GREATER_OR_EQUAL, current_token_position );
            return Token( TokenType::GREATER, current_token_position );
        case '=':
            if( next_is_equal )
                return Token( TokenType::EQUAL, current_token_position );
            return Token( TokenType::ASSIGN, current_token_position );
        case '!':
            if( next_is_equal )
                return Token( TokenType::NOT_EQUAL, current_token_position );
            return Token( TokenType::NEGATION, current_token_position );
        default:
            return Token( TokenType::INVALID, current_token_position );
    }
}

const Token &Lexer::getCurrentToken() const {
    return current_token;
}

void Lexer::setScanner(SourceInterface *_scanner) {
    Lexer::scanner = _scanner;
}

int Lexer::getMaxLiteralLength() const {
    return max_literal_length;
}

void Lexer::setMaxLiteralLength(int maxLiteralLength) {
    max_literal_length = maxLiteralLength;
}

int Lexer::getMaxStringLength() const {
    return max_string_length;
}

void Lexer::setMaxStringLength(int maxStringLength) {
    max_string_length = maxStringLength;
}
