#include <gtest/gtest.h>

#include "../../src/Source/StringStream/StringStreamSource.h"
#include "../../src/Source/SourceInterface.h"
#include "../../src/Lexical/Lexer/Lexer.h"

class single_token_test: public ::testing::Test
{
protected:
};

TEST_F(single_token_test, define_token_test )
{
    std::istringstream input("define");
    SourceInterface * scanner = new StringStreamSource(input);
    Lexer lexer = Lexer(scanner);
    ASSERT_EQ(lexer.getNextToken().getType(), TokenType::DEFINE);
}

TEST_F(single_token_test, func_token_test )
{
    std::istringstream input("func");
    SourceInterface * scanner = new StringStreamSource(input);
    Lexer lexer = Lexer(scanner);
    ASSERT_EQ(lexer.getNextToken().getType(), TokenType::FUNC);
}

TEST_F(single_token_test, for_token_test )
{
    std::istringstream input("for");
    SourceInterface * scanner = new StringStreamSource(input);
    Lexer lexer = Lexer(scanner);
    ASSERT_EQ(lexer.getNextToken().getType(), TokenType::FOR);
}

TEST_F(single_token_test, while_token_test)
{
    std::istringstream input("while");
    SourceInterface * scanner = new StringStreamSource(input);
    Lexer lexer = Lexer(scanner);
    ASSERT_EQ(lexer.getNextToken().getType(), TokenType::WHILE);
}

TEST_F(single_token_test, repeat_token_test )
{
    std::istringstream input("repeat");
    SourceInterface * scanner = new StringStreamSource(input);
    Lexer lexer = Lexer(scanner);
    ASSERT_EQ(lexer.getNextToken().getType(), TokenType::REPEAT);
}

TEST_F(single_token_test, if_token_test )
{
    std::istringstream input("if");
    SourceInterface * scanner = new StringStreamSource(input);
    Lexer lexer = Lexer(scanner);
    ASSERT_EQ(lexer.getNextToken().getType(), TokenType::IF);
}

TEST_F(single_token_test, else_token_test )
{
    std::istringstream input("else");
    SourceInterface * scanner = new StringStreamSource(input);
    Lexer lexer = Lexer(scanner);
    ASSERT_EQ(lexer.getNextToken().getType(), TokenType::ELSE);
}

TEST_F(single_token_test, parenthesis_open_token_test )
{
    std::istringstream input("(");
    SourceInterface * scanner = new StringStreamSource(input);
    Lexer lexer = Lexer(scanner);
    Token token = lexer.getNextToken();
    ASSERT_EQ(token.getType(), TokenType::PARENTHESIS_OPEN);
}

TEST_F(single_token_test, parenthesis_close_token_test )
{
    std::istringstream input(")");
    SourceInterface * scanner = new StringStreamSource(input);
    Lexer lexer = Lexer(scanner);
    ASSERT_EQ(lexer.getNextToken().getType(), TokenType::PARENTHESIS_CLOSE);
}

TEST_F(single_token_test, bracket_open_token_test )
{
    std::istringstream input("[");
    SourceInterface * scanner = new StringStreamSource(input);
    Lexer lexer = Lexer(scanner);
    ASSERT_EQ(lexer.getNextToken().getType(), TokenType::BRACKET_OPEN);
}

TEST_F(single_token_test, bracket_close_token_test )
{
    std::istringstream input("]");
    SourceInterface * scanner = new StringStreamSource(input);
    Lexer lexer = Lexer(scanner);
    ASSERT_EQ(lexer.getNextToken().getType(), TokenType::BRACKET_CLOSE);
}

TEST_F(single_token_test, curly_bracket_open_token_test )
{
    std::istringstream input("{");
    SourceInterface * scanner = new StringStreamSource(input);
    Lexer lexer = Lexer(scanner);
    ASSERT_EQ(lexer.getNextToken().getType(), TokenType::CURLY_BRACKET_OPEN);
}

TEST_F(single_token_test, curly_bracket_close_token_test )
{
    std::istringstream input("}");
    SourceInterface * scanner = new StringStreamSource(input);
    Lexer lexer = Lexer(scanner);
    ASSERT_EQ(lexer.getNextToken().getType(), TokenType::CURLY_BRACKET_CLOSE);
}

TEST_F(single_token_test, string_token_test )
{
    std::string napis = "\"to je\\\\st \\\" napis\"";
    std::string napis_bez = "to je\\st \" napis";

    std::istringstream input(napis);
    SourceInterface * scanner = new StringStreamSource(input);
    Lexer lexer = Lexer(scanner);

    ASSERT_EQ(lexer.getNextToken().getType(), TokenType::STRING);
    ASSERT_EQ( lexer.getCurrentToken().getLiteralValue(),napis_bez);
}

TEST_F(single_token_test, too_long_string_token_test )
{
    std::string napis = "\"abcdefg\"";

    std::istringstream input(napis);
    SourceInterface * scanner = new StringStreamSource(input);
    Lexer lexer = Lexer(scanner);
    lexer.setMaxStringLength(6);

    ASSERT_ANY_THROW(lexer.getNextToken());
}

TEST_F(single_token_test, not_too_long_string_token_test )
{
    std::string napis = "\"abcdefg\"";

    std::istringstream input(napis);
    SourceInterface * scanner = new StringStreamSource(input);
    Lexer lexer = Lexer(scanner);
    lexer.setMaxStringLength(7);

    ASSERT_NO_THROW(lexer.getNextToken());
}

TEST_F(single_token_test, comma_token_test )
{
    std::istringstream input(",");
    SourceInterface * scanner = new StringStreamSource(input);
    Lexer lexer = Lexer(scanner);
    ASSERT_EQ(lexer.getNextToken().getType(), TokenType::COMMA);
}

TEST_F(single_token_test, plus_token_test )
{
    std::istringstream input("+");
    SourceInterface * scanner = new StringStreamSource(input);
    Lexer lexer = Lexer(scanner);
    ASSERT_EQ(lexer.getNextToken().getType(), TokenType::PLUS);
}

TEST_F(single_token_test, minus_token_test )
{
    std::istringstream input("-");
    SourceInterface * scanner = new StringStreamSource(input);
    Lexer lexer = Lexer(scanner);
    ASSERT_EQ(lexer.getNextToken().getType(), TokenType::MINUS);
}

TEST_F(single_token_test, multiply_token_test )
{
    std::istringstream input("*");
    SourceInterface * scanner = new StringStreamSource(input);
    Lexer lexer = Lexer(scanner);
    ASSERT_EQ(lexer.getNextToken().getType(), TokenType::MULTIPLY);
}

TEST_F(single_token_test, divide_token_test )
{
    std::istringstream input("/");
    SourceInterface * scanner = new StringStreamSource(input);
    Lexer lexer = Lexer(scanner);
    ASSERT_EQ(lexer.getNextToken().getType(), TokenType::DIVIDE);
}

TEST_F(single_token_test, assign_token_test )
{
    std::istringstream input("=");
    SourceInterface * scanner = new StringStreamSource(input);
    Lexer lexer = Lexer(scanner);
    ASSERT_EQ(lexer.getNextToken().getType(), TokenType::ASSIGN);
}

TEST_F(single_token_test, equal_token_test )
{
    std::istringstream input("==");
    SourceInterface * scanner = new StringStreamSource(input);
    Lexer lexer = Lexer(scanner);
    ASSERT_EQ(lexer.getNextToken().getType(), TokenType::EQUAL);
}

TEST_F(single_token_test, not_equal_token_test )
{
    std::istringstream input("!=");
    SourceInterface * scanner = new StringStreamSource(input);
    Lexer lexer = Lexer(scanner);
    ASSERT_EQ(lexer.getNextToken().getType(), TokenType::NOT_EQUAL);
}

TEST_F(single_token_test, lower_token_test )
{
    std::istringstream input("<");
    SourceInterface * scanner = new StringStreamSource(input);
    Lexer lexer = Lexer(scanner);
    ASSERT_EQ(lexer.getNextToken().getType(), TokenType::LOWER);
}

TEST_F(single_token_test, lower_or_equal_token_test )
{
    std::istringstream input("<=");
    SourceInterface * scanner = new StringStreamSource(input);
    Lexer lexer = Lexer(scanner);
    ASSERT_EQ(lexer.getNextToken().getType(), TokenType::LOWER_OR_EQUAL);
}

TEST_F(single_token_test, greater_token_test )
{
    std::istringstream input(">");
    SourceInterface * scanner = new StringStreamSource(input);
    Lexer lexer = Lexer(scanner);
    ASSERT_EQ(lexer.getNextToken().getType(), TokenType::GREATER);
}

TEST_F(single_token_test, greater_or_equal_token_test )
{
    std::istringstream input(">=");
    SourceInterface * scanner = new StringStreamSource(input);
    Lexer lexer = Lexer(scanner);
    ASSERT_EQ(lexer.getNextToken().getType(), TokenType::GREATER_OR_EQUAL);
}

TEST_F(single_token_test, label_token_test )
{
    std::istringstream input("aa_aa1");
    SourceInterface * scanner = new StringStreamSource(input);
    Lexer lexer = Lexer(scanner);
    Token token = lexer.getNextToken();
    ASSERT_EQ(token.getType(), TokenType::LABEL);
    ASSERT_EQ(token.getLiteralValue(), "aa_aa1");
}

TEST_F(single_token_test, too_long_label_token_test )
{
    std::istringstream input("abcdef");
    SourceInterface * scanner = new StringStreamSource(input);
    Lexer lexer = Lexer(scanner);
    lexer.setMaxLiteralLength(5);
    ASSERT_ANY_THROW(lexer.getNextToken());
}

TEST_F(single_token_test, not_too_long_label_token_test )
{
    std::istringstream input("abcdef");
    SourceInterface * scanner = new StringStreamSource(input);
    Lexer lexer = Lexer(scanner);
    lexer.setMaxLiteralLength(6);
    ASSERT_NO_THROW(lexer.getNextToken());
}

TEST_F(single_token_test, number_token_test )
{
    std::istringstream input("123");
    SourceInterface * scanner = new StringStreamSource(input);
    Lexer lexer = Lexer(scanner);
    Token token = lexer.getNextToken();
    ASSERT_EQ(token.getType(), TokenType::NUMBER);
    ASSERT_EQ(token.getNumericValue(), 123);
}

TEST_F(single_token_test, true_token_test )
{
    std::istringstream input("true");
    SourceInterface * scanner = new StringStreamSource(input);
    Lexer lexer = Lexer(scanner);
    Token token = lexer.getNextToken();
    ASSERT_EQ(token.getType(), TokenType::TRUE);
}

TEST_F(single_token_test, false_token_test )
{
    std::istringstream input("false");
    SourceInterface * scanner = new StringStreamSource(input);
    Lexer lexer = Lexer(scanner);
    Token token = lexer.getNextToken();
    ASSERT_EQ(token.getType(), TokenType::FALSE);
}

TEST_F(single_token_test, and_token_test )
{
    std::istringstream input("and");
    SourceInterface * scanner = new StringStreamSource(input);
    Lexer lexer = Lexer(scanner);
    Token token = lexer.getNextToken();
    ASSERT_EQ(token.getType(), TokenType::AND);
}

TEST_F(single_token_test, and_symbolic_token_test )
{
    std::istringstream input("&");
    SourceInterface * scanner = new StringStreamSource(input);
    Lexer lexer = Lexer(scanner);
    Token token = lexer.getNextToken();
    ASSERT_EQ(token.getType(), TokenType::AND_SYMBOLIC);
}

TEST_F(single_token_test, or_token_test )
{
    std::istringstream input("or");
    SourceInterface * scanner = new StringStreamSource(input);
    Lexer lexer = Lexer(scanner);
    Token token = lexer.getNextToken();
    ASSERT_EQ(token.getType(), TokenType::OR);
}

TEST_F(single_token_test, or_symbolic_token_test )
{
    std::istringstream input("|");
    SourceInterface * scanner = new StringStreamSource(input);
    Lexer lexer = Lexer(scanner);
    Token token = lexer.getNextToken();
    ASSERT_EQ(token.getType(), TokenType::OR_SYMBOLIC);
}

TEST_F(single_token_test, negation_token_test )
{
    std::istringstream input("!");
    SourceInterface * scanner = new StringStreamSource(input);
    Lexer lexer = Lexer(scanner);
    Token token = lexer.getNextToken();
    ASSERT_EQ(token.getType(), TokenType::NEGATION);
}

TEST_F(single_token_test, semicolon_token_test )
{
    std::istringstream input(";");
    SourceInterface * scanner = new StringStreamSource(input);
    Lexer lexer = Lexer(scanner);
    Token token = lexer.getNextToken();
    ASSERT_EQ(token.getType(), TokenType::SEMICOLON);
}

TEST_F(single_token_test, eof_token_test )
{
    std::istringstream input("");
    SourceInterface * scanner = new StringStreamSource(input);
    Lexer lexer = Lexer(scanner);
    Token token = lexer.getNextToken();
    ASSERT_EQ(token.getType(), TokenType::END_OF_FILE);
}

TEST_F(single_token_test, invalid_token_test )
{
    std::istringstream input("?");
    SourceInterface * scanner = new StringStreamSource(input);
    Lexer lexer = Lexer(scanner);
    Token token = lexer.getNextToken();
    ASSERT_EQ(token.getType(), TokenType::INVALID);
}
