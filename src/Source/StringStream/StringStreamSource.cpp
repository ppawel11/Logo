#include "StringStreamSource.h"

StringStreamSource::StringStreamSource(std::istringstream & _input):
    SourceInterface(),
    input {_input}
{
}

char StringStreamSource::getNextChar() {
    char next_char = input.get();

    if( next_char == '\n' )
    {
        current_position.sign = 0;
        while( next_char == '\n' )
        {
            current_position.line++;
            next_char = input.get();
        }
    }

    current_position.sign++;

    current_char = next_char;
    current_position.stream_position = input.tellg();
    return next_char;
}

char StringStreamSource::peek() {
    return static_cast<char>( input.peek() );
}

bool StringStreamSource::eof() {
    return input.eof();
}
