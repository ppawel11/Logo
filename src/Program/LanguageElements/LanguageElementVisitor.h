#ifndef TKOM_LANGUAGEELEMENTVISITOR_H
#define TKOM_LANGUAGEELEMENTVISITOR_H

class ForEachLoop;
class FunctionCall;
class FunctionDefinition;
class If;
class RepeatLoop;
class WhileLoop;
class Return;
class VariableAssignment;
class VariableDeclaration;
class Block;
class Backward;
class Circle;
class Clear;
class Forward;
class Read;
class Reset;
class Switch;
class Turn;
class Write;

class LanguageElementVisitor {
public:
    virtual void interpret(ForEachLoop * for_each_loop) = 0;
    virtual void interpret(FunctionCall * function_call) = 0;
    virtual void interpret(FunctionDefinition * function_definition) = 0;
    virtual void interpret(If * if_statement) = 0;
    virtual void interpret(RepeatLoop * repeat_loop) = 0;
    virtual void interpret(WhileLoop * while_loop) = 0;
    virtual void interpret(Return * return_statement) = 0;
    virtual void interpret(VariableAssignment * variable_assignment) = 0;
    virtual void interpret(VariableDeclaration * variable_declaration) = 0;
    virtual void interpret(Block * block) = 0;
    virtual void interpret(Backward * backward) = 0;
    virtual void interpret(Circle * circle) = 0;
    virtual void interpret(Clear * clear) = 0;
    virtual void interpret(Forward * forward) = 0;
    virtual void interpret(Read * read) = 0;
    virtual void interpret(Reset * reset) = 0;
    virtual void interpret(Switch * switch_) = 0;
    virtual void interpret(Turn * turn) = 0;
    virtual void interpret(Write * write) = 0;
};
#endif //TKOM_LANGUAGEELEMENTVISITOR_H
