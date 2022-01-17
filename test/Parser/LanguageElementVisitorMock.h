#ifndef TKOM_LANGUAGEELEMENTVISITORMOCK_H
#define TKOM_LANGUAGEELEMENTVISITORMOCK_H

#include <gmock/gmock.h>
#include "../../src/Program/LanguageElements/LanguageElementVisitor.h"
#include "../../src/Program/LanguageElements/LanguageElementVisitor.h"
#include "../../src/Program/LanguageElements/Variables/Evaluator.h"

#include "../../src/Program/Program.h"

class LanguageElementsHolderMock: public LanguageElementsHolder
{
public:
    void append_instructions( std::unique_ptr<LanguageElement>& new_instr ) override { appending_instructions_proxy( new_instr.get() ); instructions.push_back( std::move( new_instr ) ); }
    void append_functions( std::unique_ptr<FunctionDefinition>& new_func ) override { appending_functions_proxy( new_func.get() ); func_defs[new_func->getName()] = std::move( new_func ); };

    MOCK_METHOD(void, clear, (  ), (override));
    MOCK_METHOD(void, set_valid, ( bool ), (override));

    MOCK_METHOD1( appending_instructions_proxy,void ( LanguageElement* ) );
    MOCK_METHOD1( appending_functions_proxy,void ( LanguageElement* ) );
};

class LanguageElementVisitorMock : public LanguageElementVisitor, public Evaluator
{
    std::variant<Number, Bool, String> result;
public:
    void interpret( ForEachLoop* for_each_loop ) override {
        interpret_for_each_loop_proxy();

        notice_std_string( for_each_loop->getValueLabel() );
        for_each_loop->getContainer()->be_evaluated( this );
        for_each_loop->getLoop()->be_handled( this );
    }
    void interpret( FunctionDefinition* func_def ) override {
        interpret_function_definition_proxy();

        notice_std_string( func_def->getName() );

        for( auto& param : func_def->getParameters() )
            notice_std_string( param );

        func_def->getBody()->be_handled( this );
    }
    void interpret( If* if_ ) override {
        interpret_if_proxy();
        if_->getCondition()->be_evaluated( this );
        if_->getIfBlock()->be_handled( this );
        auto& else_ = if_->getElseBlock();
        if( else_ )
            else_.value()->be_handled( this );
    }
    void interpret( RepeatLoop* repeat_loop ) override {
        interpret_repeat_loop_proxy();
        repeat_loop->getRepeats()->be_evaluated( this );
        repeat_loop->getLoop()->be_handled( this );
    }
    void interpret( WhileLoop* while_loop ) override {
        interpret_while_loop_proxy();
        while_loop->getCondition()->be_evaluated( this );
        while_loop->getLoop()->be_handled( this );
    }
    void interpret( Block* block ) override {
        interpret_block_proxy(); for( auto& statement : block->getStatements() ) { statement->be_handled( this ); }
    }
    void interpret(FunctionCall* func_call) override {
        interpret_function_call_proxy();
        notice_std_string( func_call->getName() );

        for( auto & arg : func_call->getArguments().getArgs() )
            arg->be_evaluated( this );
    }
    void interpret(Return* return_ ) override {
        interpret_return_proxy();
        return_->getValue()->be_evaluated( this );
    }
    void interpret(VariableAssignment* var_assignment ) override {
        interpret_variable_assignment_proxy();
        notice_std_string( var_assignment->getLabel() );
        var_assignment->getValue()->be_evaluated( this );
    }
    void interpret(VariableDeclaration* var_declaration ) override {
        interpret_variable_declaration_proxy();
        notice_std_string( var_declaration->getLabel() );
        var_declaration->getValue()->be_evaluated( this );
    }

    void evaluate( OrCondition *or_condition ) override {
        evaluate_or_condition_proxy();

        ASSERT_THAT( or_condition != nullptr, "or_condition nullptr" );
        ASSERT_THAT( !or_condition->getElements().empty(), "or_condition not containing anything");

        for( auto& elem : or_condition->getElements() )
        {
            elem->be_evaluated( this );
        }
    }
    void evaluate( AndCondition *and_condition ) override {
        evaluate_and_condition_proxy();

        ASSERT_THAT( and_condition != nullptr, "and_condition nullptr" );
        ASSERT_THAT( !and_condition->getEqConditions().empty(), "and_condition not containing anything");

        for( auto& elem : and_condition->getEqConditions() )
        {
            elem->be_evaluated( this );
        }
    }
    void evaluate( EqualityCondition *equality_condition ) override {
        evaluate_equality_condition_proxy();

        ASSERT_THAT( equality_condition != nullptr, "equality condition nullptr" );
        ASSERT_THAT( equality_condition->getFirstCondition() != nullptr, "equality condition first condition nullptr" );


        equality_condition->getFirstCondition()->be_evaluated( this );

        if( equality_condition->getSecondCondition() )
        {
            ASSERT_THAT( equality_condition->getEquals() != std::nullopt, "equality_condition has two expressions but no equals" );
            notice_bool( equality_condition->getEquals().value() );
            equality_condition->getSecondCondition().value()->be_evaluated( this );
        }
    }
    void evaluate( Comparison *comparison ) override {
        evaluate_comparison_proxy();

        ASSERT_THAT( comparison != nullptr, "comparison nullptr" );
        ASSERT_THAT( comparison->getFirstExpression() != nullptr, "comparison first expression nullptr" );


        comparison->getFirstExpression()->be_evaluated( this );

        if( comparison->getSecondExpression() )
        {
            ASSERT_THAT( comparison->getType() != std::nullopt, "comparison has two expressions but no type" );
            notice_comparison_type( comparison->getType().value() );
            comparison->getSecondExpression().value()->be_evaluated( this );
        }
    }
    void evaluate( AdditiveExpression *additive_expression ) override {
        evaluate_additive_expression_proxy();

        ASSERT_THAT( additive_expression != nullptr, "additive expression nullptr" );
        ASSERT_THAT( !additive_expression->getExpressions().empty(), "additive_expressions empty" );
        ASSERT_THAT( additive_expression->getExpressions().size() - 1 == additive_expression->getOperators().size(), "additive_expressions wrong number of elements and operators" );

        additive_expression->getExpressions()[0]->be_evaluated( this );

        for( int i = 0; i < additive_expression->getOperators().size(); ++i )
        {
            notice_operator( additive_expression->getOperators()[i].getType() );
            additive_expression->getExpressions()[i+1]->be_evaluated(this);
        }
    }

    void evaluate( MultiplyExpression *multiply_expression ) override {
        evaluate_multiply_expression_proxy();

        ASSERT_THAT( multiply_expression != nullptr, "multiply expression nullptr" );
        ASSERT_THAT( !multiply_expression->getElements().empty(), "multiply expressions empty" );
        ASSERT_THAT( multiply_expression->getElements().size() - 1 == multiply_expression->getOperators().size(), "multiply expression: wrong number of elements and operators" );

        multiply_expression->getElements()[0]->be_evaluated( this );

        for( int i = 0; i < multiply_expression->getOperators().size(); ++i )
        {
            notice_operator( multiply_expression->getOperators()[i].getType() );
            multiply_expression->getElements()[i+1]->be_evaluated(this);
        }
    }

    void evaluate( FunctionCall *function_call ) override {
        evaluate_function_call_proxy();

        notice_std_string( function_call->getName() );

        for( auto& arg: function_call->getArguments().getArgs() )
            arg->be_evaluated( this );
    }
    void evaluate( Bool *bool_val ) override {
        evaluate_bool_val_proxy();
        notice_bool( bool_val->isValue() );
    }
    void evaluate( String *string_val ) override {
        evaluate_string_val_proxy();
        notice_std_string( string_val->getValue() );
    }
    void evaluate( Number *num_val ) override {
        evaluate_num_val_proxy();
        notice_int( num_val->getValue() );
    }
    void evaluate( ListOfVariantValues *list_val ) override {
        evaluate_list_of_variant_values_proxy();
    }
    void evaluate( ListOfAssignable *list_val ) override {
        evaluate_list_of_assignable_proxy();

        for( auto& val : list_val->get_elements() )
            val->be_evaluated( this );
    }
    void evaluate( Label *label_val ) override {
        evaluate_label_val_proxy();
        notice_std_string( label_val->get_variable_name() );
    }
    void evaluate( NegatedMathElement *negated_math_element ) override {
        evaluate_negated_math_element_proxy();
        negated_math_element->getElement()->be_evaluated( this );
    }
    void evaluate( NegatedLogicalElement *negated_logical_element ) override {
        evaluate_negated_logical_element_proxy();
        negated_logical_element->getElement()->be_evaluated( this );
    }

    MOCK_METHOD(void, evaluate_or_condition_proxy, ( ), ( ) );
    MOCK_METHOD(void, evaluate_and_condition_proxy, ( ), ( ) );
    MOCK_METHOD(void, evaluate_comparison_proxy, ( ), ( ) );
    MOCK_METHOD(void, evaluate_equality_condition_proxy, ( ), ( ) );
    MOCK_METHOD(void, evaluate_additive_expression_proxy, ( ), ( ) );
    MOCK_METHOD(void, evaluate_multiply_expression_proxy, ( ), ( ) );
    MOCK_METHOD(void, evaluate_function_call_proxy, ( ), ( ) );
    MOCK_METHOD(void, evaluate_bool_val_proxy, ( ), ( ) );
    MOCK_METHOD(void, evaluate_string_val_proxy, ( ), ( ) );
    MOCK_METHOD(void, evaluate_num_val_proxy, ( ), ( ) );
    MOCK_METHOD(void, evaluate_list_of_variant_values_proxy, ( ), ( ) );
    MOCK_METHOD(void, evaluate_list_of_assignable_proxy, ( ), ( ) );
    MOCK_METHOD(void, evaluate_label_val_proxy, ( ), ( ) );
    MOCK_METHOD(void, evaluate_negated_math_element_proxy, ( ), ( ) );
    MOCK_METHOD(void, evaluate_negated_logical_element_proxy, ( ), ( ) );

    MOCK_METHOD(void, interpret_function_definition_proxy, ( ), () );
    MOCK_METHOD(void, interpret_for_each_loop_proxy, () );
    MOCK_METHOD(void, interpret_if_proxy, (), () );
    MOCK_METHOD(void, interpret_repeat_loop_proxy, (), () );
    MOCK_METHOD(void, interpret_while_loop_proxy, (), () );
    MOCK_METHOD(void, interpret_block_proxy, (), () );
    MOCK_METHOD(void, interpret_function_call_proxy, (), () );
    MOCK_METHOD(void, interpret_return_proxy, (), ());
    MOCK_METHOD(void, interpret_variable_assignment_proxy, (), ());
    MOCK_METHOD(void, interpret_variable_declaration_proxy, (), ());

    MOCK_METHOD(void, interpret, (Backward* ), (override));
    MOCK_METHOD(void, interpret, (Circle* ), (override));
    MOCK_METHOD(void, interpret, (Clear* ), (override));
    MOCK_METHOD(void, interpret, (Forward* ), (override));
    MOCK_METHOD(void, interpret, (Read* ), (override));
    MOCK_METHOD(void, interpret, (Reset* ), (override));
    MOCK_METHOD(void, interpret, (Switch* ), (override));
    MOCK_METHOD(void, interpret, (Turn* ), (override));
    MOCK_METHOD(void, interpret, (Write* ), (override));

    MOCK_METHOD(void, notice_bool, ( const bool ), ( ) );
    MOCK_METHOD(void, notice_std_string, ( const std::string ), ( ) );
    MOCK_METHOD(void, notice_int, ( const int ), ( ) );
    MOCK_METHOD(void, notice_operator, ( OperationType ), ( ) );
    MOCK_METHOD(void, notice_comparison_type, ( RelationType ), ( ) );
};

#endif //TKOM_LANGUAGEELEMENTVISITORMOCK_H
