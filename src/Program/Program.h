#ifndef TKOM_PROGRAM_H
#define TKOM_PROGRAM_H

#include <utility>
#include <vector>
#include <string>
#include <map>

#include "LanguageElements/FunctionDefinition.h"
#include "LanguageElements/LanguageElement.h"
#include <QtCore/QObject>

class LanguageElementsHolder: public QObject {
Q_OBJECT
protected:
    bool valid;
public:
    std::vector<std::unique_ptr<LanguageElement>> instructions;
    std::map<std::string, std::unique_ptr<FunctionDefinition>> func_defs;

    explicit LanguageElementsHolder(QObject * parent = nullptr ): QObject(parent ), valid{false }, instructions{}, func_defs{} {};
    virtual void append_instructions( std::unique_ptr<LanguageElement>& new_instruction ) = 0;
    virtual void append_functions( std::unique_ptr<FunctionDefinition>&  new_function ) = 0;
    virtual void clear() = 0;
    virtual void set_valid(bool) = 0;
};


class Program: public LanguageElementsHolder {
Q_OBJECT
    Q_PROPERTY(bool valid MEMBER valid READ is_valid WRITE set_valid NOTIFY valid_changed );
public:

    explicit Program(QObject * parent = nullptr): LanguageElementsHolder(parent ) {}

    void clear() override {
        instructions.clear();
        func_defs.clear();
    };

    bool is_valid() const {
        return valid;
    }

    void set_valid(bool valid_) override {
        valid = valid_;
        emit valid_changed();
    }

    void append_instructions(std::unique_ptr<LanguageElement>& new_instruction) override { instructions.push_back( std::move(new_instruction ) ); }
    void append_functions( std::unique_ptr<FunctionDefinition>&  new_function ) override { func_defs[new_function->getName()] = std::move(new_function); }


signals:
    void valid_changed();
};



#endif //TKOM_PROGRAM_H
