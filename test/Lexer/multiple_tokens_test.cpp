#include <gtest/gtest.h>

#include "../../src/Source/StringStream/StringStreamSource.h"
#include "../../src/Source/SourceInterface.h"
#include "../../src/Lexical/Lexer/Lexer.h"

class multiple_tokens_test: public ::testing::Test
{
protected:
};

std::string basic_program_1 =
        "define num_1 = 1;\n"
        "repeat(num_1){\n"
        "\n"
        "\n"
        "   forward (                  100);\n"
        "\n"
        "   turn (180-(360/num_1)  )\n"
        ";\n"
        "}\n";


TEST_F(multiple_tokens_test, basic_program_1 )
{
    std::istringstream input(basic_program_1);
    SourceInterface * scanner = new StringStreamSource(input);
    Lexer lexer = Lexer(scanner);
    Token token = lexer.getNextToken();
    ASSERT_EQ(token.getType(), TokenType::DEFINE);
    token = lexer.getNextToken();
    ASSERT_EQ(token.getType(), TokenType::LABEL);
    ASSERT_EQ(token.getLiteralValue(), "num_1");
    ASSERT_EQ(lexer.getNextToken().getType(), TokenType::ASSIGN);
    token = lexer.getNextToken();
    ASSERT_EQ(token.getType(), TokenType::NUMBER);
    ASSERT_EQ(token.getNumericValue(), 1);
    ASSERT_EQ(lexer.getNextToken().getType(), TokenType::SEMICOLON);
    ASSERT_EQ(lexer.getNextToken().getType(), TokenType::REPEAT);
    ASSERT_EQ(lexer.getNextToken().getType(), TokenType::PARENTHESIS_OPEN);
    ASSERT_EQ(lexer.getNextToken().getType(), TokenType::LABEL);
    ASSERT_EQ(lexer.getCurrentToken().getLiteralValue(), "num_1");
    ASSERT_EQ(lexer.getNextToken().getType(), TokenType::PARENTHESIS_CLOSE);
    ASSERT_EQ(lexer.getNextToken().getType(), TokenType::CURLY_BRACKET_OPEN);
    ASSERT_EQ(lexer.getNextToken().getType(), TokenType::LABEL);
    ASSERT_EQ(lexer.getNextToken().getType(), TokenType::PARENTHESIS_OPEN);
    token = lexer.getNextToken();
    ASSERT_EQ(token.getType(), TokenType::NUMBER);
    ASSERT_EQ(token.getNumericValue(), 100);
    ASSERT_EQ(lexer.getNextToken().getType(), TokenType::PARENTHESIS_CLOSE);
    ASSERT_EQ(lexer.getNextToken().getType(), TokenType::SEMICOLON);

    ASSERT_EQ(lexer.getNextToken().getType(), TokenType::LABEL);
    ASSERT_EQ(lexer.getNextToken().getType(), TokenType::PARENTHESIS_OPEN);

    token = lexer.getNextToken();
    ASSERT_EQ(token.getType(), TokenType::NUMBER);
    ASSERT_EQ(token.getNumericValue(), 180);
    ASSERT_EQ(lexer.getNextToken().getType(), TokenType::MINUS);
    ASSERT_EQ(lexer.getNextToken().getType(), TokenType::PARENTHESIS_OPEN);
    token = lexer.getNextToken();
    ASSERT_EQ(token.getType(), TokenType::NUMBER);
    ASSERT_EQ(token.getNumericValue(), 360);
    ASSERT_EQ(lexer.getNextToken().getType(), TokenType::DIVIDE);
    token = lexer.getNextToken();
    ASSERT_EQ(token.getType(), TokenType::LABEL);
    ASSERT_EQ(token.getLiteralValue(), "num_1");
    ASSERT_EQ(lexer.getNextToken().getType(), TokenType::PARENTHESIS_CLOSE);
    ASSERT_EQ(lexer.getNextToken().getType(), TokenType::PARENTHESIS_CLOSE);
    ASSERT_EQ(lexer.getNextToken().getType(), TokenType::SEMICOLON);
    ASSERT_EQ(lexer.getNextToken().getType(), TokenType::CURLY_BRACKET_CLOSE);
    ASSERT_EQ(lexer.getNextToken().getType(), TokenType::END_OF_FILE);
}
