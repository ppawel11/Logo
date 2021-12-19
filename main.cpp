//#include <QGuiApplication>
//#include <QQmlApplicationEngine>
//#include <QQmlContext>
//#include <QQuickItem>
//
//#include "../../src/Source/StringStream/StringStreamSource.h"
//#include "../../src/Source/SourceInterface.h"
//#include "../../src/Lexical/Lexer/Lexer.h"
//#include "../../src/Parsing/Parser.h"

#include <iostream>

#include "../../src/Program/LanguageElements/Variables/VariantValue.h"
#include "../../src/Program/LanguageElements/Variables/Bool.h"

int main(int argc, char** argv) {
//    QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);
//    QGuiApplication app {argc, argv};
//    QQmlApplicationEngine engine;
//    QObject::connect(&engine, &QQmlApplicationEngine::quit, &app, &QGuiApplication::quit, Qt::QueuedConnection);
//    QObject::connect(&engine, &QQmlApplicationEngine::exit, &app, &QGuiApplication::exit, Qt::QueuedConnection);
//
//    engine.load(QUrl("qrc:/main.qml"));
//    return( QGuiApplication::exec() );
//    std::string to_be_parsed =
//            "var num_1 = 4;"
//            "repeat(num_1){"
//            "   forward(100);"
//            "   turn(180);"
//            "}";
//
//    std::istringstream input(to_be_parsed);
//    SourceInterface * scanner = new StringStreamSource(input);
//    Lexer lexer = Lexer(scanner);
//    Parser parser = Parser(lexer);
//    Program program = parser.parseProgram();
//
//    int a = 1;
//    if( true == 1 == 2 )
//    {
//
//    }
    VariantValue* val1 = new Bool(true);
    VariantValue* val2 = new Bool(false);

    VariantValue* and_ = *val1 && val2;
    VariantValue* or_ = *val1 || val2;

    dynamic_cast<Bool*>(and_)->to_bool() ? std::cout<<"and true"<<std::endl : std::cout<<"and false"<<std::endl;
    dynamic_cast<Bool*>(or_)->to_bool() ? std::cout<<"or true"<<std::endl : std::cout<<"or false"<<std::endl;

    return 0;
}
