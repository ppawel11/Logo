#ifndef TKOM_PROGRAM_H
#define TKOM_PROGRAM_H

#include <utility>
#include <vector>
#include <string>
#include <map>

#include "LanguageElements/FunctionDefinition.h"
#include "LanguageElements/LanguageElement.h"
#include <QtCore/QObject>

class Program: public QObject {
    Q_OBJECT
    Q_PROPERTY(bool valid MEMBER valid READ is_valid WRITE set_valid NOTIFY valid_changed );

    bool valid = false;

public:

    Program(QObject * parent = nullptr ): QObject( parent ) {}
    std::vector<std::unique_ptr<LanguageElement>> instructions;

    std::map<std::string, std::unique_ptr<FunctionDefinition>> func_defs;
    explicit Program(std::vector<std::unique_ptr<LanguageElement>> statements_, std::map<std::string, std::unique_ptr<FunctionDefinition>> func_defs_)
            : instructions{std::move(statements_)}, func_defs{std::move(func_defs_)} {}

    void clear() {
        instructions.clear();
        func_defs.clear();
    };

    bool is_valid() const {
        return valid;
    }

    void set_valid(bool valid) {
        Program::valid = valid;
        emit valid_changed();
    }

    signals:
    void valid_changed();
};



#endif //TKOM_PROGRAM_H
