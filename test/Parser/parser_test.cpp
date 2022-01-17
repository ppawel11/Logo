#include <gtest/gtest.h>

#include "../../src/Source/StringStream/StringStreamSource.h"
#include "../../src/Source/SourceInterface.h"
#include "../../src/Lexical/Lexer/Lexer.h"
#include "../../src/Parsing/Parser.h"

#include "LanguageElementVisitorMock.h"
#include "../../src/Program/LanguageElements/VariableDeclaration.h"

class parser_test: public ::testing::Test
{
public:
    ::testing::Sequence sequence;
    ::testing::StrictMock<LanguageElementVisitorMock> language_element_visitor;
    ::testing::StrictMock<LanguageElementsHolderMock> language_elements_holder;

    Lexer * lexer;
    Parser parser;
    SourceInterface * scanner;

    std::istringstream input;
protected:
    void SetUp(std::string& to_parse) {
        input = std::istringstream( to_parse );
        scanner = new StringStreamSource( input );

        lexer = new Lexer( scanner );
        parser.set_lexer( lexer );

        parser.parseProgram( &language_elements_holder );
    }

    void TearDown() override {
        delete lexer;
        delete scanner;
    }
};


TEST_F(parser_test, parser_basic_test )
{
    EXPECT_CALL( language_elements_holder, clear ).Times(1).InSequence( sequence );
    EXPECT_CALL( language_elements_holder, appending_instructions_proxy( ::testing::WhenDynamicCastTo<VariableDeclaration*>( ::testing::NotNull() ) ) ).Times(1).InSequence( sequence );
    EXPECT_CALL( language_elements_holder, appending_instructions_proxy( ::testing::WhenDynamicCastTo<RepeatLoop*>( ::testing::NotNull() ) ) ).Times(1).InSequence( sequence );
    EXPECT_CALL( language_elements_holder, set_valid( true) ).Times(1).InSequence( sequence );

    std::string to_be_parsed = ""
                               "var num_1 = 4;\n"
                               "repeat( num_1 ){\n"
                               "    forward(100);\n"
                               "    turn(180);\n"
                               "}";
    SetUp( to_be_parsed );

    EXPECT_CALL( language_element_visitor, interpret_variable_declaration_proxy() ).Times(1).InSequence( sequence );
    EXPECT_CALL( language_element_visitor, notice_std_string( "num_1" ) ).Times(1).InSequence( sequence );
    EXPECT_CALL( language_element_visitor, evaluate_or_condition_proxy( ) ).Times(1).InSequence( sequence );
    EXPECT_CALL( language_element_visitor, evaluate_and_condition_proxy( ) ).Times(1).InSequence( sequence );
    EXPECT_CALL( language_element_visitor, evaluate_equality_condition_proxy( ) ).Times(1).InSequence( sequence );
    EXPECT_CALL( language_element_visitor, evaluate_comparison_proxy( ) ).Times(1).InSequence( sequence );
    EXPECT_CALL( language_element_visitor, evaluate_additive_expression_proxy( ) ).Times(1).InSequence( sequence );
    EXPECT_CALL( language_element_visitor, evaluate_multiply_expression_proxy( ) ).Times(1).InSequence( sequence );
    EXPECT_CALL( language_element_visitor, evaluate_num_val_proxy( ) ).Times(1).InSequence( sequence );
    EXPECT_CALL( language_element_visitor, notice_int( 4 ) ).Times(1).InSequence( sequence );

    EXPECT_CALL( language_element_visitor, interpret_repeat_loop_proxy() ).Times(1).InSequence( sequence );
    EXPECT_CALL( language_element_visitor, evaluate_additive_expression_proxy( ) ).Times(1).InSequence( sequence );
    EXPECT_CALL( language_element_visitor, evaluate_multiply_expression_proxy( ) ).Times(1).InSequence( sequence );
    EXPECT_CALL( language_element_visitor, evaluate_label_val_proxy( ) ).Times(1).InSequence( sequence );
    EXPECT_CALL( language_element_visitor, notice_std_string( "num_1" ) ).Times(1).InSequence( sequence );

    EXPECT_CALL( language_element_visitor, interpret_block_proxy() ).Times(1).InSequence( sequence );

    EXPECT_CALL( language_element_visitor, interpret_function_call_proxy( ) ).Times(1).InSequence( sequence );
    EXPECT_CALL( language_element_visitor, notice_std_string( "forward" ) ).Times(1).InSequence( sequence );
    EXPECT_CALL( language_element_visitor, evaluate_or_condition_proxy( ) ).Times(1).InSequence( sequence );
    EXPECT_CALL( language_element_visitor, evaluate_and_condition_proxy( ) ).Times(1).InSequence( sequence );
    EXPECT_CALL( language_element_visitor, evaluate_equality_condition_proxy( ) ).Times(1).InSequence( sequence );
    EXPECT_CALL( language_element_visitor, evaluate_comparison_proxy( ) ).Times(1).InSequence( sequence );
    EXPECT_CALL( language_element_visitor, evaluate_additive_expression_proxy( ) ).Times(1).InSequence( sequence );
    EXPECT_CALL( language_element_visitor, evaluate_multiply_expression_proxy( ) ).Times(1).InSequence( sequence );
    EXPECT_CALL( language_element_visitor, evaluate_num_val_proxy( ) ).Times(1).InSequence( sequence );
    EXPECT_CALL( language_element_visitor, notice_int( 100 ) ).Times(1).InSequence( sequence );

    EXPECT_CALL( language_element_visitor, interpret_function_call_proxy( ) ).Times(1).InSequence( sequence );
    EXPECT_CALL( language_element_visitor, notice_std_string( "turn" ) ).Times(1).InSequence( sequence );
    EXPECT_CALL( language_element_visitor, evaluate_or_condition_proxy( ) ).Times(1).InSequence( sequence );
    EXPECT_CALL( language_element_visitor, evaluate_and_condition_proxy( ) ).Times(1).InSequence( sequence );
    EXPECT_CALL( language_element_visitor, evaluate_equality_condition_proxy( ) ).Times(1).InSequence( sequence );
    EXPECT_CALL( language_element_visitor, evaluate_comparison_proxy( ) ).Times(1).InSequence( sequence );
    EXPECT_CALL( language_element_visitor, evaluate_additive_expression_proxy( ) ).Times(1).InSequence( sequence );
    EXPECT_CALL( language_element_visitor, evaluate_multiply_expression_proxy( ) ).Times(1).InSequence( sequence );
    EXPECT_CALL( language_element_visitor, evaluate_num_val_proxy( ) ).Times(1).InSequence( sequence );
    EXPECT_CALL( language_element_visitor, notice_int( 180 ) ).Times(1).InSequence( sequence );


    for( auto& instruction : language_elements_holder.instructions )
    {
       instruction->be_handled( &language_element_visitor );
    }
}

TEST_F(parser_test, for_each_loop_test)
{
    EXPECT_CALL( language_elements_holder, clear ).Times(1);
    EXPECT_CALL( language_elements_holder, appending_instructions_proxy(
            ::testing::WhenDynamicCastTo<ForEachLoop*>( ::testing::NotNull() ) )
            ).Times(1);
    EXPECT_CALL( language_elements_holder, set_valid( true) ).Times(1);

    std::string to_parse =
            "for( a : list ) { }";

    SetUp( to_parse );

    EXPECT_CALL( language_element_visitor, interpret_for_each_loop_proxy( ) ).Times(1).InSequence( sequence );

    EXPECT_CALL( language_element_visitor, notice_std_string("a") ).Times(1).InSequence( sequence );

    EXPECT_CALL( language_element_visitor, evaluate_or_condition_proxy( ) ).Times(1).InSequence( sequence );
    EXPECT_CALL( language_element_visitor, evaluate_and_condition_proxy( ) ).Times(1).InSequence( sequence );
    EXPECT_CALL( language_element_visitor, evaluate_equality_condition_proxy( ) ).Times(1).InSequence( sequence );
    EXPECT_CALL( language_element_visitor, evaluate_comparison_proxy( ) ).Times(1).InSequence( sequence );
    EXPECT_CALL( language_element_visitor, evaluate_additive_expression_proxy( ) ).Times(1).InSequence( sequence );
    EXPECT_CALL( language_element_visitor, evaluate_multiply_expression_proxy( ) ).Times(1).InSequence( sequence );
    EXPECT_CALL( language_element_visitor, evaluate_label_val_proxy( ) ).Times(1).InSequence( sequence );
    EXPECT_CALL( language_element_visitor, notice_std_string("list") ).Times(1).InSequence( sequence );

    EXPECT_CALL( language_element_visitor, interpret_block_proxy() ).Times(1).InSequence( sequence );


    for( auto& instruction : language_elements_holder.instructions )
    {
        instruction->be_handled( &language_element_visitor );
    }
}

TEST_F(parser_test, function_call_test)
{
    EXPECT_CALL( language_elements_holder, clear ).Times(1);
    EXPECT_CALL( language_elements_holder, appending_instructions_proxy( ::testing::WhenDynamicCastTo<FunctionCall*>( ::testing::NotNull() ) ) ).Times(1);
    EXPECT_CALL( language_elements_holder, set_valid( true) ).Times(1);

    std::string to_parse = "this_is_function();";

    SetUp( to_parse );

    EXPECT_CALL( language_element_visitor, interpret_function_call_proxy() ).Times(1).InSequence( sequence );
    EXPECT_CALL( language_element_visitor, notice_std_string( "this_is_function" ) ).Times(1).InSequence( sequence );

    for( auto& instruction : language_elements_holder.instructions )
    {
        instruction->be_handled( &language_element_visitor );
    }
}

TEST_F(parser_test, function_call_with_args_test)
{
    EXPECT_CALL( language_elements_holder, clear ).Times(1);
    EXPECT_CALL( language_elements_holder, appending_instructions_proxy( ::testing::WhenDynamicCastTo<FunctionCall*>( ::testing::NotNull() ) ) ).Times(1);
    EXPECT_CALL( language_elements_holder, set_valid( true) ).Times(1);

    std::string to_parse = "this_is_function( 1, 2, another(), \"testowy\" );";

    SetUp( to_parse );

    EXPECT_CALL( language_element_visitor, interpret_function_call_proxy() ).Times(1).InSequence( sequence );
    EXPECT_CALL( language_element_visitor, notice_std_string( "this_is_function" ) ).Times(1).InSequence( sequence );

    EXPECT_CALL( language_element_visitor, evaluate_or_condition_proxy( ) ).Times(1).InSequence( sequence );
    EXPECT_CALL( language_element_visitor, evaluate_and_condition_proxy( ) ).Times(1).InSequence( sequence );
    EXPECT_CALL( language_element_visitor, evaluate_equality_condition_proxy( ) ).Times(1).InSequence( sequence );
    EXPECT_CALL( language_element_visitor, evaluate_comparison_proxy( ) ).Times(1).InSequence( sequence );
    EXPECT_CALL( language_element_visitor, evaluate_additive_expression_proxy( ) ).Times(1).InSequence( sequence );
    EXPECT_CALL( language_element_visitor, evaluate_multiply_expression_proxy( ) ).Times(1).InSequence( sequence );
    EXPECT_CALL( language_element_visitor, evaluate_num_val_proxy( ) ).Times(1).InSequence( sequence );
    EXPECT_CALL( language_element_visitor, notice_int( 1 ) ).Times(1).InSequence( sequence );

    EXPECT_CALL( language_element_visitor, evaluate_or_condition_proxy( ) ).Times(1).InSequence( sequence );
    EXPECT_CALL( language_element_visitor, evaluate_and_condition_proxy( ) ).Times(1).InSequence( sequence );
    EXPECT_CALL( language_element_visitor, evaluate_equality_condition_proxy( ) ).Times(1).InSequence( sequence );
    EXPECT_CALL( language_element_visitor, evaluate_comparison_proxy( ) ).Times(1).InSequence( sequence );
    EXPECT_CALL( language_element_visitor, evaluate_additive_expression_proxy( ) ).Times(1).InSequence( sequence );
    EXPECT_CALL( language_element_visitor, evaluate_multiply_expression_proxy( ) ).Times(1).InSequence( sequence );
    EXPECT_CALL( language_element_visitor, evaluate_num_val_proxy( ) ).Times(1).InSequence( sequence );
    EXPECT_CALL( language_element_visitor, notice_int( 2 ) ).Times(1).InSequence( sequence );

    EXPECT_CALL( language_element_visitor, evaluate_or_condition_proxy( ) ).Times(1).InSequence( sequence );
    EXPECT_CALL( language_element_visitor, evaluate_and_condition_proxy( ) ).Times(1).InSequence( sequence );
    EXPECT_CALL( language_element_visitor, evaluate_equality_condition_proxy( ) ).Times(1).InSequence( sequence );
    EXPECT_CALL( language_element_visitor, evaluate_comparison_proxy( ) ).Times(1).InSequence( sequence );
    EXPECT_CALL( language_element_visitor, evaluate_additive_expression_proxy( ) ).Times(1).InSequence( sequence );
    EXPECT_CALL( language_element_visitor, evaluate_multiply_expression_proxy( ) ).Times(1).InSequence( sequence );
    EXPECT_CALL( language_element_visitor, evaluate_function_call_proxy( ) ).Times(1).InSequence( sequence );
    EXPECT_CALL( language_element_visitor, notice_std_string( "another" ) ).Times(1).InSequence( sequence );

    EXPECT_CALL( language_element_visitor, evaluate_or_condition_proxy( ) ).Times(1).InSequence( sequence );
    EXPECT_CALL( language_element_visitor, evaluate_and_condition_proxy( ) ).Times(1).InSequence( sequence );
    EXPECT_CALL( language_element_visitor, evaluate_equality_condition_proxy( ) ).Times(1).InSequence( sequence );
    EXPECT_CALL( language_element_visitor, evaluate_comparison_proxy( ) ).Times(1).InSequence( sequence );
    EXPECT_CALL( language_element_visitor, evaluate_additive_expression_proxy( ) ).Times(1).InSequence( sequence );
    EXPECT_CALL( language_element_visitor, evaluate_multiply_expression_proxy( ) ).Times(1).InSequence( sequence );
    EXPECT_CALL( language_element_visitor, evaluate_string_val_proxy( ) ).Times(1).InSequence( sequence );
    EXPECT_CALL( language_element_visitor, notice_std_string( "testowy" ) ).Times(1).InSequence( sequence );

    for( auto& instruction : language_elements_holder.instructions )
    {
        instruction->be_handled( &language_element_visitor );
    }
}

TEST_F(parser_test, function_definition_test)
{
    EXPECT_CALL( language_elements_holder, clear ).Times(1);
    EXPECT_CALL( language_elements_holder, appending_functions_proxy( ::testing::WhenDynamicCastTo<FunctionDefinition*>( ::testing::NotNull() ) ) ).Times(1);
    EXPECT_CALL( language_elements_holder, set_valid( true) ).Times(1);

    std::string to_parse =
            "func testowa_funkcja( a, drugi_arg, Abc ) { }";


    SetUp( to_parse );

    auto added_func = language_elements_holder.func_defs.find( "testowa_funkcja" );
    ASSERT_THAT( added_func != language_elements_holder.func_defs.end(), "Function not added" );
    ASSERT_THAT( added_func->second->getName() == "testowa_funkcja", "funtion name not matching" );
    ASSERT_THAT( added_func->second->getParameters() == std::vector<std::string>({"a", "drugi_arg", "Abc"}), "arguments not matching" );

    EXPECT_CALL( language_element_visitor, interpret_block_proxy() ).Times(1).InSequence( sequence );
    added_func->second->getBody()->be_handled( &language_element_visitor );
}

TEST_F(parser_test, function_definition_with_instructions_test)
{
    EXPECT_CALL( language_elements_holder, clear ).Times(1);
    EXPECT_CALL( language_elements_holder, appending_functions_proxy( ::testing::WhenDynamicCastTo<FunctionDefinition*>( ::testing::NotNull() ) ) ).Times(1);
    EXPECT_CALL( language_elements_holder, set_valid( true) ).Times(1);

    std::string to_parse =
            "func testowa_funkcja() {"
            "   var a = 1;"
            "}";


    SetUp( to_parse );

    auto added_func = language_elements_holder.func_defs.find( "testowa_funkcja" );
    ASSERT_THAT( added_func != language_elements_holder.func_defs.end(), "Function not added" );
    ASSERT_THAT( added_func->second->getName() == "testowa_funkcja", "funtion name not matching" );
    ASSERT_THAT( added_func->second->getParameters().empty(), "arguments not matching" );

    EXPECT_CALL( language_element_visitor, interpret_block_proxy() ).Times(1).InSequence( sequence );
    EXPECT_CALL( language_element_visitor, interpret_variable_declaration_proxy() ).Times(1).InSequence( sequence );

    EXPECT_CALL( language_element_visitor, notice_std_string( "a" ) ).Times(1).InSequence( sequence );

    EXPECT_CALL( language_element_visitor, evaluate_or_condition_proxy( ) ).Times(1).InSequence( sequence );
    EXPECT_CALL( language_element_visitor, evaluate_and_condition_proxy( ) ).Times(1).InSequence( sequence );
    EXPECT_CALL( language_element_visitor, evaluate_equality_condition_proxy( ) ).Times(1).InSequence( sequence );
    EXPECT_CALL( language_element_visitor, evaluate_comparison_proxy( ) ).Times(1).InSequence( sequence );
    EXPECT_CALL( language_element_visitor, evaluate_additive_expression_proxy( ) ).Times(1).InSequence( sequence );
    EXPECT_CALL( language_element_visitor, evaluate_multiply_expression_proxy( ) ).Times(1).InSequence( sequence );
    EXPECT_CALL( language_element_visitor, evaluate_num_val_proxy( ) ).Times(1).InSequence( sequence );
    EXPECT_CALL( language_element_visitor, notice_int( 1 ) ).Times(1).InSequence( sequence );

    added_func->second->getBody()->be_handled( &language_element_visitor );
}

TEST_F(parser_test, if_test)
{
    EXPECT_CALL( language_elements_holder, clear ).Times(1);
    EXPECT_CALL( language_elements_holder, appending_instructions_proxy( ::testing::WhenDynamicCastTo<If*>( ::testing::NotNull() ) ) ).Times(1);
    EXPECT_CALL( language_elements_holder, set_valid( true) ).Times(1);

    std::string to_parse =
            "if( true ) { }";

    SetUp( to_parse );

    EXPECT_CALL( language_element_visitor, interpret_if_proxy( ) ).Times(1).InSequence( sequence );

    EXPECT_CALL( language_element_visitor, evaluate_or_condition_proxy( ) ).Times(1).InSequence( sequence );
    EXPECT_CALL( language_element_visitor, evaluate_and_condition_proxy( ) ).Times(1).InSequence( sequence );
    EXPECT_CALL( language_element_visitor, evaluate_equality_condition_proxy( ) ).Times(1).InSequence( sequence );
    EXPECT_CALL( language_element_visitor, evaluate_bool_val_proxy( ) ).Times(1).InSequence( sequence );
    EXPECT_CALL( language_element_visitor, notice_bool( true ) ).Times(1).InSequence( sequence );

    EXPECT_CALL( language_element_visitor, interpret_block_proxy() ).Times(1).InSequence( sequence );

    for( auto& instruction : language_elements_holder.instructions )
    {
        instruction->be_handled( &language_element_visitor );
    }
}

TEST_F(parser_test, repeat_loop_test)
{
    EXPECT_CALL( language_elements_holder, clear ).Times(1);
    EXPECT_CALL( language_elements_holder, appending_instructions_proxy( ::testing::WhenDynamicCastTo<RepeatLoop*>( ::testing::NotNull() ) ) ).Times(1);
    EXPECT_CALL( language_elements_holder, set_valid( true) ).Times(1);

    std::string to_parse =
            "repeat(3) { }";

    SetUp( to_parse );

    EXPECT_CALL( language_element_visitor, interpret_repeat_loop_proxy( ) ).Times(1).InSequence( sequence );

    EXPECT_CALL( language_element_visitor, evaluate_additive_expression_proxy( ) ).Times(1).InSequence( sequence );
    EXPECT_CALL( language_element_visitor, evaluate_multiply_expression_proxy( ) ).Times(1).InSequence( sequence );
    EXPECT_CALL( language_element_visitor, evaluate_num_val_proxy( ) ).Times(1).InSequence( sequence );
    EXPECT_CALL( language_element_visitor, notice_int( 3 ) ).Times(1).InSequence( sequence );

    EXPECT_CALL( language_element_visitor, interpret_block_proxy() ).Times(1).InSequence( sequence );

    for( auto& instruction : language_elements_holder.instructions )
    {
        instruction->be_handled( &language_element_visitor );
    }
}

TEST_F(parser_test, while_loop_test)
{
    EXPECT_CALL( language_elements_holder, clear ).Times(1);
    EXPECT_CALL( language_elements_holder, appending_instructions_proxy( ::testing::WhenDynamicCastTo<WhileLoop*>( ::testing::NotNull() ) ) ).Times(1);
    EXPECT_CALL( language_elements_holder, set_valid( true) ).Times(1);

    std::string to_parse =
            "while( false ) { }";

    SetUp( to_parse );

    EXPECT_CALL( language_element_visitor, interpret_while_loop_proxy( ) ).Times(1).InSequence( sequence );

    EXPECT_CALL( language_element_visitor, evaluate_or_condition_proxy( ) ).Times(1).InSequence( sequence );
    EXPECT_CALL( language_element_visitor, evaluate_and_condition_proxy( ) ).Times(1).InSequence( sequence );
    EXPECT_CALL( language_element_visitor, evaluate_equality_condition_proxy( ) ).Times(1).InSequence( sequence );
    EXPECT_CALL( language_element_visitor, evaluate_bool_val_proxy( ) ).Times(1).InSequence( sequence );
    EXPECT_CALL( language_element_visitor, notice_bool( false ) ).Times(1).InSequence( sequence );

    EXPECT_CALL( language_element_visitor, interpret_block_proxy() ).Times(1).InSequence( sequence );

    for( auto& instruction : language_elements_holder.instructions )
    {
        instruction->be_handled( &language_element_visitor );
    }
}

TEST_F(parser_test, return_test)
{
    EXPECT_CALL( language_elements_holder, clear ).Times(1);
    EXPECT_CALL( language_elements_holder, appending_instructions_proxy( ::testing::WhenDynamicCastTo<Return*>( ::testing::NotNull() ) ) ).Times(1);
    EXPECT_CALL( language_elements_holder, set_valid( true) ).Times(1);

    std::string to_parse = "return 2;";

    SetUp( to_parse );

    EXPECT_CALL( language_element_visitor, interpret_return_proxy( ) ).Times(1).InSequence( sequence );

    EXPECT_CALL( language_element_visitor, evaluate_or_condition_proxy( ) ).Times(1).InSequence( sequence );
    EXPECT_CALL( language_element_visitor, evaluate_and_condition_proxy( ) ).Times(1).InSequence( sequence );
    EXPECT_CALL( language_element_visitor, evaluate_equality_condition_proxy( ) ).Times(1).InSequence( sequence );
    EXPECT_CALL( language_element_visitor, evaluate_comparison_proxy( ) ).Times(1).InSequence( sequence );
    EXPECT_CALL( language_element_visitor, evaluate_additive_expression_proxy( ) ).Times(1).InSequence( sequence );
    EXPECT_CALL( language_element_visitor, evaluate_multiply_expression_proxy( ) ).Times(1).InSequence( sequence );
    EXPECT_CALL( language_element_visitor, evaluate_num_val_proxy( ) ).Times(1).InSequence( sequence );
    EXPECT_CALL( language_element_visitor, notice_int( 2 ) ).Times(1).InSequence( sequence );

    for( auto& instruction : language_elements_holder.instructions )
    {
        instruction->be_handled( &language_element_visitor );
    }
}

TEST_F(parser_test, variable_assignment_test)
{
    EXPECT_CALL( language_elements_holder, clear ).Times(1);
    EXPECT_CALL( language_elements_holder, appending_instructions_proxy( ::testing::WhenDynamicCastTo<VariableAssignment*>( ::testing::NotNull() ) ) ).Times(1);
    EXPECT_CALL( language_elements_holder, set_valid( true) ).Times(1);

    std::string to_parse =
            "abc = 3;";

    SetUp( to_parse );

    EXPECT_CALL( language_element_visitor, interpret_variable_assignment_proxy() ).Times(1).InSequence( sequence );

    EXPECT_CALL( language_element_visitor, notice_std_string( "abc" ) ).Times(1).InSequence( sequence );

    EXPECT_CALL( language_element_visitor, evaluate_or_condition_proxy( ) ).Times(1).InSequence( sequence );
    EXPECT_CALL( language_element_visitor, evaluate_and_condition_proxy( ) ).Times(1).InSequence( sequence );
    EXPECT_CALL( language_element_visitor, evaluate_equality_condition_proxy( ) ).Times(1).InSequence( sequence );
    EXPECT_CALL( language_element_visitor, evaluate_comparison_proxy( ) ).Times(1).InSequence( sequence );
    EXPECT_CALL( language_element_visitor, evaluate_additive_expression_proxy( ) ).Times(1).InSequence( sequence );
    EXPECT_CALL( language_element_visitor, evaluate_multiply_expression_proxy( ) ).Times(1).InSequence( sequence );
    EXPECT_CALL( language_element_visitor, evaluate_num_val_proxy( ) ).Times(1).InSequence( sequence );
    EXPECT_CALL( language_element_visitor, notice_int( 3 ) ).Times(1).InSequence( sequence );

    for( auto& instruction : language_elements_holder.instructions )
    {
        instruction->be_handled( &language_element_visitor );
    }
}

TEST_F(parser_test, variable_declaration_test)
{
    EXPECT_CALL( language_elements_holder, clear ).Times(1);
    EXPECT_CALL( language_elements_holder, appending_instructions_proxy( ::testing::WhenDynamicCastTo<VariableDeclaration*>( ::testing::NotNull() ) ) ).Times(1);
    EXPECT_CALL( language_elements_holder, set_valid( true) ).Times(1);

    std::string to_parse =
            "var a = [1,2,3];";

    SetUp( to_parse );

    EXPECT_CALL( language_element_visitor, interpret_variable_declaration_proxy() ).Times(1).InSequence( sequence );

    EXPECT_CALL( language_element_visitor, notice_std_string( "a" ) ).Times(1).InSequence( sequence );

    EXPECT_CALL( language_element_visitor, evaluate_or_condition_proxy( ) ).Times(1).InSequence( sequence );
    EXPECT_CALL( language_element_visitor, evaluate_and_condition_proxy( ) ).Times(1).InSequence( sequence );
    EXPECT_CALL( language_element_visitor, evaluate_equality_condition_proxy( ) ).Times(1).InSequence( sequence );
    EXPECT_CALL( language_element_visitor, evaluate_comparison_proxy( ) ).Times(1).InSequence( sequence );
    EXPECT_CALL( language_element_visitor, evaluate_additive_expression_proxy( ) ).Times(1).InSequence( sequence );
    EXPECT_CALL( language_element_visitor, evaluate_multiply_expression_proxy( ) ).Times(1).InSequence( sequence );
    EXPECT_CALL( language_element_visitor, evaluate_list_of_assignable_proxy( ) ).Times(1).InSequence( sequence );

    EXPECT_CALL( language_element_visitor, evaluate_or_condition_proxy( ) ).Times(1).InSequence( sequence );
    EXPECT_CALL( language_element_visitor, evaluate_and_condition_proxy( ) ).Times(1).InSequence( sequence );
    EXPECT_CALL( language_element_visitor, evaluate_equality_condition_proxy( ) ).Times(1).InSequence( sequence );
    EXPECT_CALL( language_element_visitor, evaluate_comparison_proxy( ) ).Times(1).InSequence( sequence );
    EXPECT_CALL( language_element_visitor, evaluate_additive_expression_proxy( ) ).Times(1).InSequence( sequence );
    EXPECT_CALL( language_element_visitor, evaluate_multiply_expression_proxy( ) ).Times(1).InSequence( sequence );
    EXPECT_CALL( language_element_visitor, evaluate_num_val_proxy( ) ).Times(1).InSequence( sequence );
    EXPECT_CALL( language_element_visitor, notice_int( 1 ) ).Times(1).InSequence( sequence );

    EXPECT_CALL( language_element_visitor, evaluate_or_condition_proxy( ) ).Times(1).InSequence( sequence );
    EXPECT_CALL( language_element_visitor, evaluate_and_condition_proxy( ) ).Times(1).InSequence( sequence );
    EXPECT_CALL( language_element_visitor, evaluate_equality_condition_proxy( ) ).Times(1).InSequence( sequence );
    EXPECT_CALL( language_element_visitor, evaluate_comparison_proxy( ) ).Times(1).InSequence( sequence );
    EXPECT_CALL( language_element_visitor, evaluate_additive_expression_proxy( ) ).Times(1).InSequence( sequence );
    EXPECT_CALL( language_element_visitor, evaluate_multiply_expression_proxy( ) ).Times(1).InSequence( sequence );
    EXPECT_CALL( language_element_visitor, evaluate_num_val_proxy( ) ).Times(1).InSequence( sequence );
    EXPECT_CALL( language_element_visitor, notice_int( 2 ) ).Times(1).InSequence( sequence );

    EXPECT_CALL( language_element_visitor, evaluate_or_condition_proxy( ) ).Times(1).InSequence( sequence );
    EXPECT_CALL( language_element_visitor, evaluate_and_condition_proxy( ) ).Times(1).InSequence( sequence );
    EXPECT_CALL( language_element_visitor, evaluate_equality_condition_proxy( ) ).Times(1).InSequence( sequence );
    EXPECT_CALL( language_element_visitor, evaluate_comparison_proxy( ) ).Times(1).InSequence( sequence );
    EXPECT_CALL( language_element_visitor, evaluate_additive_expression_proxy( ) ).Times(1).InSequence( sequence );
    EXPECT_CALL( language_element_visitor, evaluate_multiply_expression_proxy( ) ).Times(1).InSequence( sequence );
    EXPECT_CALL( language_element_visitor, evaluate_num_val_proxy( ) ).Times(1).InSequence( sequence );
    EXPECT_CALL( language_element_visitor, notice_int( 3 ) ).Times(1).InSequence( sequence );

    for( auto& instruction : language_elements_holder.instructions )
    {
        instruction->be_handled( &language_element_visitor );
    }
}

TEST_F(parser_test, if_else_test)
{
    EXPECT_CALL( language_elements_holder, clear ).Times(1);
    EXPECT_CALL( language_elements_holder, appending_instructions_proxy( ::testing::WhenDynamicCastTo<If*>( ::testing::NotNull() ) ) ).Times(1);
    EXPECT_CALL( language_elements_holder, set_valid( true) ).Times(1);

    std::string to_parse =
            "if( 0 ) { } else { }";

    SetUp( to_parse );

    EXPECT_CALL( language_element_visitor, interpret_if_proxy( ) ).Times(1).InSequence( sequence );

    EXPECT_CALL( language_element_visitor, evaluate_or_condition_proxy( ) ).Times(1).InSequence( sequence );
    EXPECT_CALL( language_element_visitor, evaluate_and_condition_proxy( ) ).Times(1).InSequence( sequence );
    EXPECT_CALL( language_element_visitor, evaluate_equality_condition_proxy( ) ).Times(1).InSequence( sequence );
    EXPECT_CALL( language_element_visitor, evaluate_comparison_proxy( ) ).Times(1).InSequence( sequence );
    EXPECT_CALL( language_element_visitor, evaluate_additive_expression_proxy( ) ).Times(1).InSequence( sequence );
    EXPECT_CALL( language_element_visitor, evaluate_multiply_expression_proxy( ) ).Times(1).InSequence( sequence );
    EXPECT_CALL( language_element_visitor, evaluate_num_val_proxy( ) ).Times(1).InSequence( sequence );
    EXPECT_CALL( language_element_visitor, notice_int( 0 ) ).Times(1).InSequence( sequence );

    EXPECT_CALL( language_element_visitor, interpret_block_proxy() ).Times(1).InSequence( sequence );

    EXPECT_CALL( language_element_visitor, interpret_block_proxy() ).Times(1).InSequence( sequence );

    for( auto& instruction : language_elements_holder.instructions )
    {
        instruction->be_handled( &language_element_visitor );
    }
}

TEST_F(parser_test, math_expression)
{
    EXPECT_CALL( language_elements_holder, clear ).Times(1);
    EXPECT_CALL( language_elements_holder, appending_instructions_proxy( ::testing::WhenDynamicCastTo<VariableAssignment*>( ::testing::NotNull() ) ) ).Times(1);
    EXPECT_CALL( language_elements_holder, set_valid( true) ).Times(1);

    std::string to_parse =
            "a = 1 * ( 2 + 3 - -4 ) / -5 + ( func_call() * [6, 7] + \"string\");";

    SetUp( to_parse );

    EXPECT_CALL( language_element_visitor, interpret_variable_assignment_proxy( ) ).Times(1).InSequence( sequence );

    EXPECT_CALL( language_element_visitor, notice_std_string("a") ).Times(1).InSequence( sequence );

    EXPECT_CALL( language_element_visitor, evaluate_or_condition_proxy( ) ).Times(1).InSequence( sequence );
    EXPECT_CALL( language_element_visitor, evaluate_and_condition_proxy( ) ).Times(1).InSequence( sequence );
    EXPECT_CALL( language_element_visitor, evaluate_equality_condition_proxy( ) ).Times(1).InSequence( sequence );
    EXPECT_CALL( language_element_visitor, evaluate_comparison_proxy( ) ).Times(1).InSequence( sequence );
    EXPECT_CALL( language_element_visitor, evaluate_additive_expression_proxy( ) ).Times(1).InSequence( sequence );
    EXPECT_CALL( language_element_visitor, evaluate_multiply_expression_proxy( ) ).Times(1).InSequence( sequence );
    EXPECT_CALL( language_element_visitor, evaluate_num_val_proxy( ) ).Times(1).InSequence( sequence );
    EXPECT_CALL( language_element_visitor, notice_int( 1 ) ).Times(1).InSequence( sequence ); // 1
    EXPECT_CALL( language_element_visitor, notice_operator( OperationType::MULTIPLY ) ).Times(1).InSequence( sequence ); // *
    EXPECT_CALL( language_element_visitor, evaluate_or_condition_proxy( ) ).Times(1).InSequence( sequence ); // (
    EXPECT_CALL( language_element_visitor, evaluate_and_condition_proxy( ) ).Times(1).InSequence( sequence );
    EXPECT_CALL( language_element_visitor, evaluate_equality_condition_proxy( ) ).Times(1).InSequence( sequence );
    EXPECT_CALL( language_element_visitor, evaluate_comparison_proxy( ) ).Times(1).InSequence( sequence );
    EXPECT_CALL( language_element_visitor, evaluate_additive_expression_proxy( ) ).Times(1).InSequence( sequence );
    EXPECT_CALL( language_element_visitor, evaluate_multiply_expression_proxy( ) ).Times(1).InSequence( sequence );
    EXPECT_CALL( language_element_visitor, evaluate_num_val_proxy( ) ).Times(1).InSequence( sequence );
    EXPECT_CALL( language_element_visitor, notice_int( 2 ) ).Times(1).InSequence( sequence ); // 2
    EXPECT_CALL( language_element_visitor, notice_operator( OperationType::SUM ) ).Times(1).InSequence( sequence ); // +
    EXPECT_CALL( language_element_visitor, evaluate_multiply_expression_proxy( ) ).Times(1).InSequence( sequence );
    EXPECT_CALL( language_element_visitor, evaluate_num_val_proxy( ) ).Times(1).InSequence( sequence );
    EXPECT_CALL( language_element_visitor, notice_int( 3 ) ).Times(1).InSequence( sequence ); // 3
    EXPECT_CALL( language_element_visitor, notice_operator( OperationType::SUBSTRACTION ) ).Times(1).InSequence( sequence ); // -
    EXPECT_CALL( language_element_visitor, evaluate_multiply_expression_proxy( ) ).Times(1).InSequence( sequence );
    EXPECT_CALL( language_element_visitor, evaluate_negated_math_element_proxy( ) ).Times(1).InSequence( sequence );
    EXPECT_CALL( language_element_visitor, evaluate_num_val_proxy( ) ).Times(1).InSequence( sequence );
    EXPECT_CALL( language_element_visitor, notice_int( 4 ) ).Times(1).InSequence( sequence ); // 4 )
    EXPECT_CALL( language_element_visitor, notice_operator( OperationType::DIVIDE ) ).Times(1).InSequence( sequence ); // /
    EXPECT_CALL( language_element_visitor, evaluate_negated_math_element_proxy( ) ).Times(1).InSequence( sequence );
    EXPECT_CALL( language_element_visitor, evaluate_num_val_proxy( ) ).Times(1).InSequence( sequence );
    EXPECT_CALL( language_element_visitor, notice_int( 5 ) ).Times(1).InSequence( sequence ); // 5
    EXPECT_CALL( language_element_visitor, notice_operator( OperationType::SUM ) ).Times(1).InSequence( sequence ); // +
    EXPECT_CALL( language_element_visitor, evaluate_multiply_expression_proxy( ) ).Times(1).InSequence( sequence );
    EXPECT_CALL( language_element_visitor, evaluate_or_condition_proxy( ) ).Times(1).InSequence( sequence ); // (
    EXPECT_CALL( language_element_visitor, evaluate_and_condition_proxy( ) ).Times(1).InSequence( sequence );
    EXPECT_CALL( language_element_visitor, evaluate_equality_condition_proxy( ) ).Times(1).InSequence( sequence );
    EXPECT_CALL( language_element_visitor, evaluate_comparison_proxy( ) ).Times(1).InSequence( sequence );
    EXPECT_CALL( language_element_visitor, evaluate_additive_expression_proxy( ) ).Times(1).InSequence( sequence );
    EXPECT_CALL( language_element_visitor, evaluate_multiply_expression_proxy( ) ).Times(1).InSequence( sequence );
    EXPECT_CALL( language_element_visitor, evaluate_function_call_proxy( ) ).Times(1).InSequence( sequence ); // func_call()
    EXPECT_CALL( language_element_visitor, notice_std_string( "func_call" ) ).Times(1).InSequence( sequence );
    EXPECT_CALL( language_element_visitor, notice_operator( OperationType::MULTIPLY ) ).Times(1).InSequence( sequence ); // *
    EXPECT_CALL( language_element_visitor, evaluate_list_of_assignable_proxy() ).Times(1).InSequence( sequence ); // [
    EXPECT_CALL( language_element_visitor, evaluate_or_condition_proxy( ) ).Times(1).InSequence( sequence );
    EXPECT_CALL( language_element_visitor, evaluate_and_condition_proxy( ) ).Times(1).InSequence( sequence );
    EXPECT_CALL( language_element_visitor, evaluate_equality_condition_proxy( ) ).Times(1).InSequence( sequence );
    EXPECT_CALL( language_element_visitor, evaluate_comparison_proxy( ) ).Times(1).InSequence( sequence );
    EXPECT_CALL( language_element_visitor, evaluate_additive_expression_proxy( ) ).Times(1).InSequence( sequence );
    EXPECT_CALL( language_element_visitor, evaluate_multiply_expression_proxy( ) ).Times(1).InSequence( sequence );
    EXPECT_CALL( language_element_visitor, evaluate_num_val_proxy( ) ).Times(1).InSequence( sequence );
    EXPECT_CALL( language_element_visitor, notice_int( 6 ) ).Times(1).InSequence( sequence ); // 6
    EXPECT_CALL( language_element_visitor, evaluate_or_condition_proxy( ) ).Times(1).InSequence( sequence );
    EXPECT_CALL( language_element_visitor, evaluate_and_condition_proxy( ) ).Times(1).InSequence( sequence );
    EXPECT_CALL( language_element_visitor, evaluate_equality_condition_proxy( ) ).Times(1).InSequence( sequence );
    EXPECT_CALL( language_element_visitor, evaluate_comparison_proxy( ) ).Times(1).InSequence( sequence );
    EXPECT_CALL( language_element_visitor, evaluate_additive_expression_proxy( ) ).Times(1).InSequence( sequence );
    EXPECT_CALL( language_element_visitor, evaluate_multiply_expression_proxy( ) ).Times(1).InSequence( sequence );
    EXPECT_CALL( language_element_visitor, evaluate_num_val_proxy( ) ).Times(1).InSequence( sequence );
    EXPECT_CALL( language_element_visitor, notice_int( 7 ) ).Times(1).InSequence( sequence ); // 7 ]
    EXPECT_CALL( language_element_visitor, notice_operator( OperationType::SUM ) ).Times(1).InSequence( sequence ); // +
    EXPECT_CALL( language_element_visitor, evaluate_multiply_expression_proxy( ) ).Times(1).InSequence( sequence );
    EXPECT_CALL( language_element_visitor, evaluate_string_val_proxy() ).Times(1).InSequence( sequence );
    EXPECT_CALL( language_element_visitor, notice_std_string( "string" ) ).Times(1).InSequence( sequence ); // "string" )

    for( auto& instruction : language_elements_holder.instructions )
    {
        instruction->be_handled( &language_element_visitor );
    }
}

TEST_F(parser_test, logical_expression)
{
    EXPECT_CALL( language_elements_holder, clear ).Times(1);
    EXPECT_CALL( language_elements_holder, appending_instructions_proxy( ::testing::WhenDynamicCastTo<VariableAssignment*>( ::testing::NotNull() ) ) ).Times(1);
    EXPECT_CALL( language_elements_holder, set_valid( true) ).Times(1);

    std::string to_parse =
            "a = true or ( 1 == 2 and 3 < 4 and 5 <= 6 ) | ( !7 > 8 & !false or 9 >= 10 or 11 != 12 );";

    SetUp( to_parse );

    EXPECT_CALL( language_element_visitor, interpret_variable_assignment_proxy( ) ).Times(1).InSequence( sequence );
    EXPECT_CALL( language_element_visitor, notice_std_string("a") ).Times(1).InSequence( sequence );

    EXPECT_CALL( language_element_visitor, evaluate_or_condition_proxy( ) ).Times(1).InSequence( sequence );
    EXPECT_CALL( language_element_visitor, evaluate_and_condition_proxy( ) ).Times(1).InSequence( sequence );
    EXPECT_CALL( language_element_visitor, evaluate_equality_condition_proxy( ) ).Times(1).InSequence( sequence );
    EXPECT_CALL( language_element_visitor, evaluate_bool_val_proxy( ) ).Times(1).InSequence( sequence );
    EXPECT_CALL( language_element_visitor, notice_bool( true ) ).Times(1).InSequence( sequence ); // true
    EXPECT_CALL( language_element_visitor, evaluate_and_condition_proxy( ) ).Times(1).InSequence( sequence ); // or
    EXPECT_CALL( language_element_visitor, evaluate_equality_condition_proxy( ) ).Times(1).InSequence( sequence );
    EXPECT_CALL( language_element_visitor, evaluate_comparison_proxy( ) ).Times(1).InSequence( sequence );
    EXPECT_CALL( language_element_visitor, evaluate_additive_expression_proxy( ) ).Times(1).InSequence( sequence );
    EXPECT_CALL( language_element_visitor, evaluate_multiply_expression_proxy( ) ).Times(1).InSequence( sequence );
    EXPECT_CALL( language_element_visitor, evaluate_or_condition_proxy( ) ).Times(1).InSequence( sequence ); // (
    EXPECT_CALL( language_element_visitor, evaluate_and_condition_proxy( ) ).Times(1).InSequence( sequence );
    EXPECT_CALL( language_element_visitor, evaluate_equality_condition_proxy( ) ).Times(1).InSequence( sequence );
    EXPECT_CALL( language_element_visitor, evaluate_comparison_proxy( ) ).Times(1).InSequence( sequence );
    EXPECT_CALL( language_element_visitor, evaluate_additive_expression_proxy( ) ).Times(1).InSequence( sequence );
    EXPECT_CALL( language_element_visitor, evaluate_multiply_expression_proxy( ) ).Times(1).InSequence( sequence );
    EXPECT_CALL( language_element_visitor, evaluate_num_val_proxy( ) ).Times(1).InSequence( sequence );
    EXPECT_CALL( language_element_visitor, notice_int( 1 ) ).Times(1).InSequence( sequence ); // 1
    EXPECT_CALL( language_element_visitor, notice_bool( true ) ).Times(1).InSequence( sequence ); // ==
    EXPECT_CALL( language_element_visitor, evaluate_comparison_proxy( ) ).Times(1).InSequence( sequence );
    EXPECT_CALL( language_element_visitor, evaluate_additive_expression_proxy( ) ).Times(1).InSequence( sequence );
    EXPECT_CALL( language_element_visitor, evaluate_multiply_expression_proxy( ) ).Times(1).InSequence( sequence );
    EXPECT_CALL( language_element_visitor, evaluate_num_val_proxy( ) ).Times(1).InSequence( sequence );
    EXPECT_CALL( language_element_visitor, notice_int( 2 ) ).Times(1).InSequence( sequence ); // 2
    EXPECT_CALL( language_element_visitor, evaluate_equality_condition_proxy( ) ).Times(1).InSequence( sequence ); // and
    EXPECT_CALL( language_element_visitor, evaluate_comparison_proxy( ) ).Times(1).InSequence( sequence );
    EXPECT_CALL( language_element_visitor, evaluate_additive_expression_proxy( ) ).Times(1).InSequence( sequence );
    EXPECT_CALL( language_element_visitor, evaluate_multiply_expression_proxy( ) ).Times(1).InSequence( sequence );
    EXPECT_CALL( language_element_visitor, evaluate_num_val_proxy( ) ).Times(1).InSequence( sequence );
    EXPECT_CALL( language_element_visitor, notice_int( 3 ) ).Times(1).InSequence( sequence ); // 3
    EXPECT_CALL( language_element_visitor, notice_comparison_type( RelationType::LOWER ) ).Times(1).InSequence( sequence ); // <
    EXPECT_CALL( language_element_visitor, evaluate_additive_expression_proxy( ) ).Times(1).InSequence( sequence );
    EXPECT_CALL( language_element_visitor, evaluate_multiply_expression_proxy( ) ).Times(1).InSequence( sequence );
    EXPECT_CALL( language_element_visitor, evaluate_num_val_proxy( ) ).Times(1).InSequence( sequence );
    EXPECT_CALL( language_element_visitor, notice_int( 4 ) ).Times(1).InSequence( sequence ); // 4
    EXPECT_CALL( language_element_visitor, evaluate_equality_condition_proxy( ) ).Times(1).InSequence( sequence ); // and
    EXPECT_CALL( language_element_visitor, evaluate_comparison_proxy( ) ).Times(1).InSequence( sequence );
    EXPECT_CALL( language_element_visitor, evaluate_additive_expression_proxy( ) ).Times(1).InSequence( sequence );
    EXPECT_CALL( language_element_visitor, evaluate_multiply_expression_proxy( ) ).Times(1).InSequence( sequence );
    EXPECT_CALL( language_element_visitor, evaluate_num_val_proxy( ) ).Times(1).InSequence( sequence );
    EXPECT_CALL( language_element_visitor, notice_int( 5 ) ).Times(1).InSequence( sequence ); // 5
    EXPECT_CALL( language_element_visitor, notice_comparison_type( RelationType::LOWER_OR_EQUAL ) ).Times(1).InSequence( sequence ); // <=
    EXPECT_CALL( language_element_visitor, evaluate_additive_expression_proxy( ) ).Times(1).InSequence( sequence );
    EXPECT_CALL( language_element_visitor, evaluate_multiply_expression_proxy( ) ).Times(1).InSequence( sequence );
    EXPECT_CALL( language_element_visitor, evaluate_num_val_proxy( ) ).Times(1).InSequence( sequence );
    EXPECT_CALL( language_element_visitor, notice_int( 6 ) ).Times(1).InSequence( sequence ); // 6 )
    EXPECT_CALL( language_element_visitor, evaluate_and_condition_proxy( ) ).Times(1).InSequence( sequence ); // |
    EXPECT_CALL( language_element_visitor, evaluate_equality_condition_proxy( ) ).Times(1).InSequence( sequence );
    EXPECT_CALL( language_element_visitor, evaluate_comparison_proxy( ) ).Times(1).InSequence( sequence );
    EXPECT_CALL( language_element_visitor, evaluate_additive_expression_proxy( ) ).Times(1).InSequence( sequence );
    EXPECT_CALL( language_element_visitor, evaluate_multiply_expression_proxy( ) ).Times(1).InSequence( sequence );
    EXPECT_CALL( language_element_visitor, evaluate_or_condition_proxy( ) ).Times(1).InSequence( sequence ); // (
    EXPECT_CALL( language_element_visitor, evaluate_and_condition_proxy( ) ).Times(1).InSequence( sequence );
    EXPECT_CALL( language_element_visitor, evaluate_equality_condition_proxy( ) ).Times(1).InSequence( sequence );
    EXPECT_CALL( language_element_visitor, evaluate_negated_logical_element_proxy( ) ).Times(1).InSequence( sequence );
    EXPECT_CALL( language_element_visitor, evaluate_comparison_proxy( ) ).Times(1).InSequence( sequence );
    EXPECT_CALL( language_element_visitor, evaluate_additive_expression_proxy( ) ).Times(1).InSequence( sequence );
    EXPECT_CALL( language_element_visitor, evaluate_multiply_expression_proxy( ) ).Times(1).InSequence( sequence );
    EXPECT_CALL( language_element_visitor, evaluate_num_val_proxy( ) ).Times(1).InSequence( sequence );
    EXPECT_CALL( language_element_visitor, notice_int( 7 ) ).Times(1).InSequence( sequence ); // 7
    EXPECT_CALL( language_element_visitor, notice_comparison_type( RelationType::GREATER ) ).Times(1).InSequence( sequence ); // >
    EXPECT_CALL( language_element_visitor, evaluate_additive_expression_proxy( ) ).Times(1).InSequence( sequence );
    EXPECT_CALL( language_element_visitor, evaluate_multiply_expression_proxy( ) ).Times(1).InSequence( sequence );
    EXPECT_CALL( language_element_visitor, evaluate_num_val_proxy( ) ).Times(1).InSequence( sequence );
    EXPECT_CALL( language_element_visitor, notice_int( 8 ) ).Times(1).InSequence( sequence ); // 8
    EXPECT_CALL( language_element_visitor, evaluate_equality_condition_proxy( ) ).Times(1).InSequence( sequence ); &
    EXPECT_CALL( language_element_visitor, evaluate_negated_logical_element_proxy( ) ).Times(1).InSequence( sequence );
    EXPECT_CALL( language_element_visitor, evaluate_bool_val_proxy( ) ).Times(1).InSequence( sequence );
    EXPECT_CALL( language_element_visitor, notice_bool( false ) ).Times(1).InSequence( sequence ); // false
    EXPECT_CALL( language_element_visitor, evaluate_and_condition_proxy( ) ).Times(1).InSequence( sequence ); // or
    EXPECT_CALL( language_element_visitor, evaluate_equality_condition_proxy( ) ).Times(1).InSequence( sequence );
    EXPECT_CALL( language_element_visitor, evaluate_comparison_proxy( ) ).Times(1).InSequence( sequence );
    EXPECT_CALL( language_element_visitor, evaluate_additive_expression_proxy( ) ).Times(1).InSequence( sequence );
    EXPECT_CALL( language_element_visitor, evaluate_multiply_expression_proxy( ) ).Times(1).InSequence( sequence );
    EXPECT_CALL( language_element_visitor, evaluate_num_val_proxy( ) ).Times(1).InSequence( sequence );
    EXPECT_CALL( language_element_visitor, notice_int( 9 ) ).Times(1).InSequence( sequence ); // 9
    EXPECT_CALL( language_element_visitor, notice_comparison_type( RelationType::GREATER_OR_EQUAL ) ).Times(1).InSequence( sequence ); // >=
    EXPECT_CALL( language_element_visitor, evaluate_additive_expression_proxy( ) ).Times(1).InSequence( sequence );
    EXPECT_CALL( language_element_visitor, evaluate_multiply_expression_proxy( ) ).Times(1).InSequence( sequence );
    EXPECT_CALL( language_element_visitor, evaluate_num_val_proxy( ) ).Times(1).InSequence( sequence );
    EXPECT_CALL( language_element_visitor, notice_int( 10 ) ).Times(1).InSequence( sequence ); // 10
    EXPECT_CALL( language_element_visitor, evaluate_and_condition_proxy( ) ).Times(1).InSequence( sequence ); // or
    EXPECT_CALL( language_element_visitor, evaluate_equality_condition_proxy( ) ).Times(1).InSequence( sequence );
    EXPECT_CALL( language_element_visitor, evaluate_comparison_proxy( ) ).Times(1).InSequence( sequence );
    EXPECT_CALL( language_element_visitor, evaluate_additive_expression_proxy( ) ).Times(1).InSequence( sequence );
    EXPECT_CALL( language_element_visitor, evaluate_multiply_expression_proxy( ) ).Times(1).InSequence( sequence );
    EXPECT_CALL( language_element_visitor, evaluate_num_val_proxy( ) ).Times(1).InSequence( sequence );
    EXPECT_CALL( language_element_visitor, notice_int( 11 ) ).Times(1).InSequence( sequence ); // 11
    EXPECT_CALL( language_element_visitor, notice_bool( false ) ).Times(1).InSequence( sequence ); // !=
    EXPECT_CALL( language_element_visitor, evaluate_comparison_proxy( ) ).Times(1).InSequence( sequence );
    EXPECT_CALL( language_element_visitor, evaluate_additive_expression_proxy( ) ).Times(1).InSequence( sequence );
    EXPECT_CALL( language_element_visitor, evaluate_multiply_expression_proxy( ) ).Times(1).InSequence( sequence );
    EXPECT_CALL( language_element_visitor, evaluate_num_val_proxy( ) ).Times(1).InSequence( sequence );
    EXPECT_CALL( language_element_visitor, notice_int( 12 ) ).Times(1).InSequence( sequence ); // 12


    for( auto& instruction : language_elements_holder.instructions )
    {
        instruction->be_handled( &language_element_visitor );
    }
}
