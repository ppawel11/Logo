#include <gtest/gtest.h>

#include "../../src/Lexical/Token/Token.h"

class token_test: public ::testing::Test
{
protected:
};

TEST_F(token_test, constructor_literal )
{
    Token token = Token(
            TokenType::STRING,
            Position(10, 20, 30),
            "test_literal");

    ASSERT_EQ(token.getNumericValue(), -1);
    ASSERT_EQ(token.getLiteralValue(), "test_literal");
    ASSERT_EQ(token.getPosition().sign, 20);
    ASSERT_EQ(token.getType(), TokenType::STRING);

    ASSERT_ANY_THROW(Token token1 = Token(TokenType::NUMBER, Position(0,0,0), "bad idea"));
    ASSERT_ANY_THROW(Token token2 = Token(TokenType::REPEAT, Position(0,0,0), "bad idea"));
    ASSERT_NO_THROW(Token token1 = Token(TokenType::LABEL, Position(0,0,0), "good idea"));
    ASSERT_NO_THROW(Token token1 = Token(TokenType::INVALID, Position(0,0,0), "good idea"));
}

TEST_F(token_test, constructor_numeric )
{
    Token token = Token(
            TokenType::NUMBER,
            Position(10, 20, 30),
            120);

    ASSERT_EQ(token.getNumericValue(), 120);
    ASSERT_EQ(token.getLiteralValue(), "");
    ASSERT_EQ(token.getPosition().sign, 20);
    ASSERT_EQ(token.getType(), TokenType::NUMBER);

    ASSERT_ANY_THROW(Token token1 = Token(TokenType::STRING, Position(0,0,0), 0));
    ASSERT_ANY_THROW(Token token2 = Token(TokenType::REPEAT, Position(0,0,0), 1));
    ASSERT_NO_THROW(Token token1 = Token(TokenType::NUMBER, Position(0,0,0), 100));
    ASSERT_NO_THROW(Token token1 = Token(TokenType::INVALID, Position(0,0,0), 100));
}

TEST_F(token_test, constructor_clear )
{
    Token token = Token(
            TokenType::REPEAT,
            Position(10, 20, 30)
            );

    ASSERT_EQ(token.getNumericValue(), -1);
    ASSERT_EQ(token.getLiteralValue(), "");
    ASSERT_EQ(token.getPosition().sign, 20);
    ASSERT_EQ(token.getType(), TokenType::REPEAT);

    ASSERT_ANY_THROW(Token token1 = Token(TokenType::STRING, Position(0,0,0)));
    ASSERT_ANY_THROW(Token token2 = Token(TokenType::LABEL, Position(0,0,0)));
    ASSERT_ANY_THROW(Token token1 = Token(TokenType::NUMBER, Position(0,0,0)));
    ASSERT_NO_THROW(Token token1 = Token(TokenType::INVALID, Position(0,0,0)));
}
