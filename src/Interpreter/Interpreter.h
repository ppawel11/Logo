#ifndef TKOM_INTERPRETER_H
#define TKOM_INTERPRETER_H

#include <utility>

#include "ScopeStack.h"
#include "../Program/Program.h"
#include "../Program/LanguageElements/ForEachLoop.h"
#include "../Program/LanguageElements/FunctionCall.h"
#include "../Program/LanguageElements/If.h"
#include "../Program/LanguageElements/RepeatLoop.h"
#include "../Program/LanguageElements/Return.h"
#include "../Program/LanguageElements/VariableAssignment.h"
#include "../Program/LanguageElements/VariableDeclaration.h"
#include "../Program/LanguageElements/WhileLoop.h"
#include "../Program/LanguageElements/Label.h"
#include "../Program/LanguageElements/ListOfAssignable.h"
#include "../Program/LanguageElements/Math/NegatedMathElement.h"
#include "../Program/LanguageElements/Logical/NegatedLogicalElement.h"
#include "../Program/LanguageElements/Logical/Comparison.h"

#include "OperationExecutors/SumExecutor.h"
#include "OperationExecutors/SubtractionExecutor.h"
#include "OperationExecutors/DivisionExecutor.h"
#include "OperationExecutors/MultiplicationExecutor.h"
#include "OperationExecutors/LessExecutor.h"
#include "OperationExecutors/LessOrEqualExecutor.h"
#include "OperationExecutors/EqualityExecutor.h"
#include "OperationExecutors/GreaterExecutor.h"
#include "OperationExecutors/GreaterOrEqualExecutor.h"
#include "OperationExecutors/AndExecutor.h"
#include "OperationExecutors/OrExecutor.h"
#include "OperationExecutors/Caster.h"

#include "IOController/IOController.h"
#include "../GUI/DrawingController/DrawingController.h"
#include "Exception/InterpreterException.h"
#include <functional>

#include <QtCore/QObject>

typedef std::function<void()> Callback;

class Interpreter: public QObject {
Q_OBJECT

    Q_PROPERTY(DrawingController * drawing_controller MEMBER drawing_controller WRITE set_drawing_controller READ get_drawing_controller NOTIFY drawing_controller_changed );
    ScopeStack scope_stack;
    IOController io_controller;
    DrawingController * drawing_controller;

    std::map<std::string, Callback> std_functions;
public:
    DrawingController *get_drawing_controller() const;

    void set_drawing_controller(DrawingController *drawingController);

    explicit Interpreter( ): scope_stack {}, io_controller {}, drawing_controller { nullptr } {
        std_functions.insert( { std::string("write"), [this]() { return this->write(); } } );
        std_functions.insert( { std::string("read"), [this]() { return this->read(); } } );
        std_functions.insert( { std::string("forward"), [this]() { return this->forward(); } } );
        std_functions.insert( { std::string("backward"), [this]() { return this->backward(); } } );
        std_functions.insert( { std::string("turn"), [this]() { return this->turn(); } } );
        std_functions.insert( { std::string("switch"), [this]() { return this->switch_(); } } );
        std_functions.insert( { std::string("reset"), [this]() { return this->reset(); } } );
        std_functions.insert( { std::string("circle"), [this]() { return this->circle(); } } );
        std_functions.insert( { std::string("clear"), [this]() { return this->clear(); } } );
    };



    void interpret(ForEachLoop * for_each_loop);
    void interpret(FunctionCall * function_call);
    void interpret(FunctionDefinition * function_definition);
    void interpret(If * if_statement);
    void interpret(RepeatLoop * repeat_loop);
    void interpret(WhileLoop * while_loop);
    void interpret(Return * return_statement);
    void interpret(VariableAssignment * variable_assignment);
    void interpret(VariableDeclaration * variable_declaration);
    void interpret(Block * block);

    void evaluate(AndCondition * and_condition);
    void evaluate(OrCondition * or_condition);
    void evaluate(Comparison * comparison);
    void evaluate(EqualityCondition * equality_condition);
    void evaluate(AdditiveExpression * additive_expression);
    void evaluate(MultiplyExpression * multiply_expression);
    void evaluate(FunctionCall * function_call);
    void evaluate(Bool * bool_val);
    void evaluate(String * string_val);
    void evaluate(Number * num_val);
    void evaluate(ListOfVariantValues * list_val);
    void evaluate(ListOfAssignable * list_val);
    void evaluate(Label * label_val);
    void evaluate(NegatedMathElement * negated_math_element);
    void evaluate(NegatedLogicalElement * negated_logical_element);

    void write();
    void read();
    void forward();
    void backward();
    void circle();
    void turn();
    void reset();
    void clear();
    void switch_();

public slots:

    void interpret(Program *program);

signals:
    void drawing_controller_changed();
    void error(QString error);

};


#endif //TKOM_INTERPRETER_H
