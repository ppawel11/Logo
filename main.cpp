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
#include "../../src/Program/LanguageElements/Variables/Number.h"

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
//    auto val1 = std::make_unique<Bool>(true);
//    auto val1 = std::make_unique<Bool>(true);
    std::unique_ptr<VariantValue> val1 = std::make_unique<Bool>(true);
    std::unique_ptr<VariantValue> val2 = std::make_unique<Bool>(false);
    std::unique_ptr<VariantValue> val3 = std::make_unique<Number>(1);
    std::unique_ptr<VariantValue> val4 = std::make_unique<Number>(2);


    std::unique_ptr<VariantValue> and_ = *val1 && val2;
    std::unique_ptr<VariantValue> sum_ = *val3 + val4.get();
//    auto or_ = *val1 || val2.get();

    and_->to_bool() ? std::cout<<"and true"<<std::endl : std::cout<<"and false"<<std::endl;
    std::cout<<"sumowanie: "<<sum_->to_number()<<std::endl;
//    or_->to_bool() ? std::cout<<"or true"<<std::endl : std::cout<<"or false"<<std::endl;
    std::cout<<"..."<<std::endl;
    return 0;
}
