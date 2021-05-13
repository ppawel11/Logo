#ifndef TKOM_POSITION_H
#define TKOM_POSITION_H

#include <string>

struct Position {
    unsigned int line;
    unsigned int sign;
    long stream_position;

    Position(unsigned int _line, unsigned int _sign, long _stream_pos):
        line { _line }, sign {_sign}, stream_position {_stream_pos} {};
};


#endif //TKOM_POSITION_H