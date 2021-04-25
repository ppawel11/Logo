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

#set(CMAKE_AUTOMOC ON)

set(SOURCE
        src/Lexical/Token/TokenType.h
        src/Lexical/Token/Token.cpp
        src/Lexical/Token/Token.h
        src/Lexical/Lexer/Lexer.cpp
        src/Lexical/Lexer/Lexer.h
        src/Source/Position.h
        src/Source/SourceInterface.h
        src/Source/StringStream/StringStreamSource.cpp
        src/Source/StringStream/StringStreamSource.h
        )

set(TEST_SOURCE
        test/Lexer/single_tokens_test.cpp
        test/Lexer/multiple_tokens_test.cpp
        test/Source/string_source_test.cpp
        test/Token/token_test.cpp
        )

if(GUI)
    qt5_add_resources(QML_RESOURCES qrc/tkom.qrc)
endif()

add_subdirectory(gtest)
enable_testing()
include_directories(${gtest_SOURCE_DIR}/include ${gtest_SOURCE_DIR})

add_executable(TKOM
        main.cpp
        ${SOURCE}
        ${QML_RESOURCES})

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
        gtest_main
        ${QT_PACK}
 )

TARGET_LINK_LIBRARIES(TKOM
        ${QT_PACK}
)
