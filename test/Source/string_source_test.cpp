#include <gtest/gtest.h>

#include "../../src/Source/StringStream/StringStreamSource.h"
#include "../../src/Source/SourceInterface.h"

class string_source_test: public ::testing::Test
{
protected:
};

TEST_F(string_source_test, init )
{
    std::istringstream input("ab"
                             "cd");
    SourceInterface * scanner = new StringStreamSource(input);

    ASSERT_EQ(scanner->getCurrentChar(), 0);
    ASSERT_EQ(scanner->getCurrentPosition().line, 0);
    ASSERT_EQ(scanner->getCurrentPosition().sign, 0);
    ASSERT_EQ(scanner->getCurrentPosition().stream_position, 0);
    ASSERT_FALSE(scanner->eof());
}

TEST_F(string_source_test, get_next_char )
{
    std::istringstream input("ab"
                             "cd");
    SourceInterface * scanner = new StringStreamSource(input);

    ASSERT_EQ(scanner->getNextChar(), 'a');
    ASSERT_EQ(scanner->getNextChar(), 'b');
    ASSERT_EQ(scanner->getNextChar(), 'c');
    ASSERT_EQ(scanner->getNextChar(), 'd');
    ASSERT_EQ(scanner->getNextChar(), '\xFF');
}

TEST_F(string_source_test, lines_counting )
{
    std::istringstream input("aaa\n"
                             "\n"
                             "cd\n"
                             "a");
    SourceInterface * scanner = new StringStreamSource(input);

    scanner->getNextChar();
    ASSERT_EQ(scanner->getCurrentPosition().line, 0);
    scanner->getNextChar();
    ASSERT_EQ(scanner->getCurrentPosition().line, 0);
    scanner->getNextChar();
    ASSERT_EQ(scanner->getCurrentPosition().line, 0);
    scanner->getNextChar();
    ASSERT_EQ(scanner->getCurrentPosition().line, 2);
    scanner->getNextChar();
    ASSERT_EQ(scanner->getCurrentPosition().line, 2);
    scanner->getNextChar();
    ASSERT_EQ(scanner->getCurrentPosition().line, 3);
}

TEST_F(string_source_test, sign_position_counting )
{
    std::istringstream input("aaa\n"
                             "zc\n"
                             "c d");
    SourceInterface * scanner = new StringStreamSource(input);

    scanner->getNextChar();
    ASSERT_EQ(scanner->getCurrentPosition().sign, 1);
    scanner->getNextChar();
    ASSERT_EQ(scanner->getCurrentPosition().sign, 2);
    scanner->getNextChar();
    ASSERT_EQ(scanner->getCurrentPosition().sign, 3);
    scanner->getNextChar();
    ASSERT_EQ(scanner->getCurrentPosition().sign, 1);
    scanner->getNextChar();
    ASSERT_EQ(scanner->getCurrentPosition().sign, 2);
    scanner->getNextChar();
    ASSERT_EQ(scanner->getCurrentPosition().sign, 1);
    scanner->getNextChar();
    ASSERT_EQ(scanner->getCurrentPosition().sign, 2);
    scanner->getNextChar();
    ASSERT_EQ(scanner->getCurrentPosition().sign, 3);
}
TEST_F(string_source_test, stream_position_counting )
{
    std::istringstream input("a b\n"
                             "\n"
                             "\n"
                             "c d");
    SourceInterface * scanner = new StringStreamSource(input);

    scanner->getNextChar();
    ASSERT_EQ(scanner->getCurrentPosition().stream_position, 1);
    scanner->getNextChar();
    ASSERT_EQ(scanner->getCurrentPosition().stream_position, 2);
    scanner->getNextChar();
    ASSERT_EQ(scanner->getCurrentPosition().stream_position, 3);
    scanner->getNextChar();
    ASSERT_EQ(scanner->getCurrentPosition().stream_position, 7);
    scanner->getNextChar();
    ASSERT_EQ(scanner->getCurrentPosition().stream_position, 8);
    scanner->getNextChar();
    ASSERT_EQ(scanner->getCurrentPosition().stream_position, 9);
}

TEST_F(string_source_test, eof )
{
    std::istringstream input("a\n"
                             "c d");
    SourceInterface * scanner = new StringStreamSource(input);

    scanner->getNextChar();
    ASSERT_FALSE(scanner->eof());
    scanner->getNextChar();
    scanner->getNextChar();
    scanner->getNextChar();
    ASSERT_FALSE(scanner->eof());
    scanner->getNextChar();
    ASSERT_TRUE(scanner->eof());
    scanner->getNextChar();
    ASSERT_TRUE(scanner->eof());
}
