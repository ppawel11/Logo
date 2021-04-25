//
// Created by pawel on 04.12.2020.
//

#ifndef TKOM_STRINGSTREAMSOURCE_H
#define TKOM_STRINGSTREAMSOURCE_H

#include <iostream>
#include <sstream>
#include "../Position.h"
#include "../SourceInterface.h"

class StringStreamSource: public SourceInterface{
private:
    std::istringstream& input;
public:
    explicit StringStreamSource(std::istringstream& _input);

    char getNextChar() override;
    char peek() override;
    bool eof() override;

};


#endif //TKOM_STRINGSTREAMSOURCE_H
