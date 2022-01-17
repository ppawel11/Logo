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
#include "../Program/LanguageElements/LanguageElementVisitor.h"
#include "../Program/LanguageElements/Variables/Evaluator.h"

#include "StandardLibrary/Backward.h"
#include "StandardLibrary/Forward.h"
#include "StandardLibrary/Circle.h"
#include "StandardLibrary/Clear.h"
#include "StandardLibrary/Switch.h"
#include "StandardLibrary/Reset.h"
#include "StandardLibrary/Read.h"
#include "StandardLibrary/Write.h"
#include "StandardLibrary/Turn.h"
#include "StandardLibrary/STD.h"

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

//typedef std::function<void()> Callback;

class Interpreter: public QObject, public LanguageElementVisitor, public Evaluator {
Q_OBJECT

    Q_PROPERTY(DrawingController * drawing_controller MEMBER drawing_controller WRITE set_drawing_controller READ get_drawing_controller NOTIFY drawing_controller_changed );
    ScopeStack scope_stack;
    IOController io_controller;
    DrawingController * drawing_controller;

public:
    DrawingController *get_drawing_controller() const;

    void set_drawing_controller(DrawingController *drawingController);

    explicit Interpreter( ): scope_stack {}, io_controller {}, drawing_controller { nullptr } {};



    void interpret(ForEachLoop * for_each_loop) override;
    void interpret(FunctionCall * function_call) override;
    void interpret(FunctionDefinition * function_definition) override;
    void interpret(If * if_statement) override;
    void interpret(RepeatLoop * repeat_loop) override;
    void interpret(WhileLoop * while_loop) override;
    void interpret(Return * return_statement) override;
    void interpret(VariableAssignment * variable_assignment) override;
    void interpret(VariableDeclaration * variable_declaration) override;
    void interpret(Block * block) override;
    void interpret(Backward * backward) override;
    void interpret(Circle * circle) override;
    void interpret(Clear * clear) override;
    void interpret(Forward * forward) override;
    void interpret(Read * read) override;
    void interpret(Reset * reset) override;
    void interpret(Switch * switch_) override;
    void interpret(Turn * turn) override;
    void interpret(Write * write) override;

    void evaluate(AndCondition * and_condition) override;
    void evaluate(OrCondition * or_condition) override;
    void evaluate(Comparison * comparison) override;
    void evaluate(EqualityCondition * equality_condition) override;
    void evaluate(AdditiveExpression * additive_expression) override;
    void evaluate(MultiplyExpression * multiply_expression) override;
    void evaluate(FunctionCall * function_call) override;
    void evaluate(Bool * bool_val) override;
    void evaluate(String * string_val) override;
    void evaluate(Number * num_val) override;
    void evaluate(ListOfVariantValues * list_val) override;
    void evaluate(ListOfAssignable * list_val) override;
    void evaluate(Label * label_val) override;
    void evaluate(NegatedMathElement * negated_math_element) override;
    void evaluate(NegatedLogicalElement * negated_logical_element) override;

//    void write();
//    void read();
//    void forward();
//    void backward();
//    void circle();
//    void turn();
//    void reset();
//    void clear();
//    void switch_();

public slots:

    void interpret(Program *program);

signals:
    void drawing_controller_changed();
    void error(QString error);

};


#endif //TKOM_INTERPRETER_H
