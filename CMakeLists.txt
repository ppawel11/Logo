cmake_minimum_required(VERSION 3.17)
project(TKOM)
set(CMAKE_CXX_STANDARD 17)

set(GUI 1)
if(GUI)
    find_package(Qt5 COMPONENTS Qml Quick QuickControls2 Widgets )

    if( NOT Qt5_FOUND )
        message("Qt not found")
    endif()
endif()

set(CMAKE_AUTOMOC ON)

set(SOURCE
        src/Lexical/Token/TokenType.h
        src/Lexical/Token/Token.cpp
        src/Lexical/Token/Token.h
        src/Lexical/Lexer/Lexer.cpp
        src/Lexical/Lexer/Lexer.h
        src/Lexical/Exceptions/LexicalException.h
        src/Source/Position.h
        src/Source/SourceInterface.h
        src/Source/StringStream/StringStreamSource.cpp
        src/Source/StringStream/StringStreamSource.h
        src/Program/LanguageElements/LanguageElement.cpp
        src/Program/LanguageElements/LanguageElement.h
        src/Program/LanguageElements/Arguments.cpp
        src/Program/LanguageElements/Arguments.h
        src/Program/LanguageElements/Block.cpp
        src/Program/LanguageElements/Block.h
        src/Program/LanguageElements/ForEachLoop.cpp
        src/Program/LanguageElements/ForEachLoop.h
        src/Program/LanguageElements/FunctionCall.cpp
        src/Program/LanguageElements/FunctionCall.h
        src/Program/LanguageElements/FunctionDefinition.cpp
        src/Program/LanguageElements/FunctionDefinition.h
        src/Program/LanguageElements/RepeatLoop.cpp
        src/Program/LanguageElements/RepeatLoop.h
        src/Program/LanguageElements/Return.cpp
        src/Program/LanguageElements/Return.h
        src/Program/LanguageElements/VariableAssignment.cpp
        src/Program/LanguageElements/VariableAssignment.h
        src/Program/LanguageElements/VariableDeclaration.cpp
        src/Program/LanguageElements/VariableDeclaration.h
        src/Program/LanguageElements/If.cpp
        src/Program/LanguageElements/If.h
        src/Program/LanguageElements/WhileLoop.cpp
        src/Program/LanguageElements/WhileLoop.h
        src/Program/LanguageElements/Math/AdditiveExpression.h
        src/Program/LanguageElements/Math/AdditiveExpression.cpp
        src/Program/LanguageElements/Math/AdditiveOperator.cpp
        src/Program/LanguageElements/Math/AdditiveOperator.h
        src/Program/LanguageElements/Math/MultiplyExpression.h
        src/Program/LanguageElements/Math/MultiplyExpression.cpp
        src/Program/LanguageElements/Math/MultiplyOperator.cpp
        src/Program/LanguageElements/Math/MultiplyOperator.h
        src/Program/LanguageElements/Math/OperationType.h
        src/Program/LanguageElements/Logical/AndCondition.cpp
        src/Program/LanguageElements/Logical/AndCondition.h
        src/Program/LanguageElements/Logical/Comparison.cpp
        src/Program/LanguageElements/Logical/Comparison.h
        src/Program/LanguageElements/Logical/OrCondition.cpp
        src/Program/LanguageElements/Logical/OrCondition.h
        src/Program/LanguageElements/Logical/EqualityCondition.h
        src/Program/LanguageElements/Logical/EqualityCondition.cpp
        src/Program/LanguageElements/Logical/RelationType.h
        src/Program/Program.cpp
        src/Program/Program.h
        src/Parsing/Parser.cpp
        src/Parsing/Parser.h
        src/Parsing/Exceptions/ParserException.h
        src/Interpreter/Interpreter.cpp
        src/Interpreter/Interpreter.h
        src/Interpreter/Scope.cpp
        src/Interpreter/Scope.h
        src/Interpreter/ScopeStack.cpp
        src/Interpreter/ScopeStack.h
        src/Interpreter/CallContext.cpp
        src/Interpreter/CallContext.h
        src/Interpreter/Exception/InterpreterException.h
        src/Program/LanguageElements/Variables/Bool.cpp
        src/Program/LanguageElements/Variables/Bool.h
        src/Program/LanguageElements/Variables/Number.cpp
        src/Program/LanguageElements/Variables/Number.h
        src/Program/LanguageElements/Variables/ListOfVariantValues.cpp
        src/Program/LanguageElements/Variables/ListOfVariantValues.h
        src/Program/LanguageElements/Variables/String.cpp
        src/Program/LanguageElements/Variables/String.h
        src/Program/LanguageElements/Variables/Assignable.cpp
        src/Program/LanguageElements/Variables/Assignable.h
        src/Program/LanguageElements/Variables/Evaluator.h
        src/Program/LanguageElements/Math/NegatedMathElement.cpp
        src/Program/LanguageElements/Math/NegatedMathElement.h
        src/Program/LanguageElements/Variables/VariantValue.cpp
        src/Program/LanguageElements/Variables/VariantValue.h
        src/Program/LanguageElements/Label.cpp
        src/Program/LanguageElements/Label.h
        src/Program/LanguageElements/ListOfAssignable.cpp
        src/Program/LanguageElements/ListOfAssignable.h
        src/Program/LanguageElements/Logical/NegatedLogicalElement.cpp
        src/Program/LanguageElements/Logical/NegatedLogicalElement.h
        src/Program/LanguageElements/LanguageElementVisitor.h
        src/Interpreter/OperationExecutors/SumExecutor.h
        src/Interpreter/OperationExecutors/DivisionExecutor.h
        src/Interpreter/OperationExecutors/MultiplicationExecutor.h
        src/Interpreter/OperationExecutors/SubtractionExecutor.h
        src/Interpreter/OperationExecutors/AndExecutor.h
        src/Interpreter/OperationExecutors/OrExecutor.h
        src/Interpreter/OperationExecutors/EqualityExecutor.h
        src/Interpreter/OperationExecutors/LessExecutor.h
        src/Interpreter/OperationExecutors/LessOrEqualExecutor.h
        src/Interpreter/OperationExecutors/GreaterExecutor.h
        src/Interpreter/OperationExecutors/GreaterOrEqualExecutor.h
        src/Interpreter/OperationExecutors/Caster.h
        src/Interpreter/IOController/IOController.cpp
        src/Interpreter/IOController/IOController.h
        src/Interpreter/StandardLibrary/Backward.h
        src/Interpreter/StandardLibrary/Backward.cpp
        src/Interpreter/StandardLibrary/Forward.h
        src/Interpreter/StandardLibrary/Forward.cpp
        src/Interpreter/StandardLibrary/Clear.h
        src/Interpreter/StandardLibrary/Clear.cpp
        src/Interpreter/StandardLibrary/Circle.h
        src/Interpreter/StandardLibrary/Circle.cpp
        src/Interpreter/StandardLibrary/Read.h
        src/Interpreter/StandardLibrary/Read.cpp
        src/Interpreter/StandardLibrary/Reset.h
        src/Interpreter/StandardLibrary/Reset.cpp
        src/Interpreter/StandardLibrary/Write.h
        src/Interpreter/StandardLibrary/Write.cpp
        src/Interpreter/StandardLibrary/Switch.h
        src/Interpreter/StandardLibrary/Switch.cpp
        src/Interpreter/StandardLibrary/Turn.h
        src/Interpreter/StandardLibrary/Turn.cpp
        src/Interpreter/StandardLibrary/STD.h
        )


set(TEST_SOURCE
        test/Lexer/single_tokens_test.cpp
        test/Lexer/multiple_tokens_test.cpp
        test/Source/string_source_test.cpp
        test/Token/token_test.cpp
        test/Parser/parser_test.cpp
        test/Parser/LanguageElementVisitorMock.h
        )

if(GUI)
    qt5_add_resources(QML_RESOURCES qrc/tkom.qrc)
    set(SOURCE ${SOURCE}
            src/GUI/DrawingController/DrawingController.cpp
            src/GUI/DrawingController/DrawingController.h
            src/Source/TextSource/TextSource.cpp
            src/Source/TextSource/TextSource.h
            )
endif()

add_subdirectory(gtest)
enable_testing()
include_directories(${gtest_SOURCE_DIR}/include ${gtest_SOURCE_DIR})

add_executable(TKOM
        main.cpp
        ${SOURCE}
        ${QML_RESOURCES}
        )

add_executable(TKOM_testing
        ${SOURCE}
        ${TEST_SOURCE})

set(QT_PACK "")
if(GUI)
    set(QT_PACK
        Qt5::Qml
        Qt5::Quick
        Qt5::QuickControls2
        Qt5::Widgets)
endif()

TARGET_LINK_LIBRARIES(TKOM_testing
        gtest
        gmock
        gtest_main
        ${QT_PACK}
 )

TARGET_LINK_LIBRARIES(TKOM
        ${QT_PACK}
)
