#ifndef TKOM_SOURCEINTERFACE_H
#define TKOM_SOURCEINTERFACE_H

#include "Position.h"

#include <QtCore/QObject>

class SourceInterface: public QObject {
    Q_OBJECT
protected:
    Position current_position;
    char current_char;
public:
    SourceInterface(QObject * parent = nullptr):
        QObject(parent),
        current_position{0, 0, 0},
        current_char{0}
        {
        }

    char getCurrentChar() const { return current_char; }
    const Position& getCurrentPosition() const { return current_position; }

    virtual char getNextChar() = 0;
    virtual char peek() = 0;
    virtual bool eof() = 0;
};
#endif //TKOM_SOURCEINTERFACE_H
