#ifndef TKOM_TEXTSOURCE_H
#define TKOM_TEXTSOURCE_H

#include <QtCore/QObject>
#include "../SourceInterface.h"
#include <QString>
#include <iostream>
#include <sstream>
#include <memory>

class TextSource: public SourceInterface  {
Q_OBJECT
    Q_PROPERTY(QString code MEMBER code READ get_code WRITE set_code NOTIFY code_changed );

    QString code;

    std::unique_ptr<std::istringstream> code_stream;
public:
    TextSource(QObject * parent = nullptr): SourceInterface( parent ) {};

    char getNextChar() override;

    char peek() override;

    bool eof() override;

    void set_code(const QString& code_);

    QString get_code();

signals:
    void code_changed();
};


#endif //TKOM_TEXTSOURCE_H
