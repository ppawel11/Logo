#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QQmlContext>
#include <QQuickItem>

#include "../../src/GUI/DrawingController/DrawingController.h"
#include "../../src/Source/StringStream/StringStreamSource.h"
#include "../../src/Source/SourceInterface.h"
#include "../../src/Lexical/Lexer/Lexer.h"
#include "../../src/Parsing/Parser.h"

#include <iostream>

#include "../../src/Program/LanguageElements/Variables/VariantValue.h"
#include "../../src/Program/LanguageElements/Variables/Bool.h"
#include "../../src/Program/LanguageElements/Variables/Number.h"
#include "src/Interpreter/Interpreter.h"
#include "src/Source/TextSource/TextSource.h"

int main(int argc, char** argv) {
    QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);
    QGuiApplication app {argc, argv};
    QQmlApplicationEngine engine;
    QObject::connect(&engine, &QQmlApplicationEngine::quit, &app, &QGuiApplication::quit, Qt::QueuedConnection);
    QObject::connect(&engine, &QQmlApplicationEngine::exit, &app, &QGuiApplication::exit, Qt::QueuedConnection);

    qmlRegisterType<DrawingController>("TKOM", 1, 0, "DrawingController");
    qmlRegisterType<Interpreter>("TKOM", 1, 0, "Interpreter");
    qmlRegisterType<Parser>("TKOM", 1, 0, "Parser");
    qmlRegisterType<Lexer>("TKOM", 1, 0, "Lexer");
    qmlRegisterType<Program>("TKOM", 1, 0, "Program");
    qmlRegisterType<TextSource>("TKOM", 1, 0, "TextSource");
    qmlRegisterUncreatableType<SourceInterface>("TKOM", 1, 0, "SourceInterface", "error: source interface");
    qmlRegisterUncreatableType<LanguageElementsHolder>("TKOM", 1, 0, "LanguageElementsHolder", "error: language element holder");
    engine.load(QUrl("qrc:/main.qml"));
    return( QGuiApplication::exec() );
//
//    std::string to_be_parsed =
//"    func trojkat( bok ) {\n"
//"repeat(3) {\n"
//"forward(bok);\n"
//"            turn(120);\n"
//"        }\n"
//"    }\n"
//"\n"
//"    func dywan( bok, ile ) {\n"
//"        if( ile == 0 ) {\n"
//"            trojkat(bok);\n"
//"        }\n"
//"        else {\n"
//"            repeat(3) {\n"
//"                dywan(bok/2, ile-1);\n"
//"                forward(bok);\n"
//"                turn(120);\n"
//"            }\n"
//"        }\n"
//"    }\n";
//
//    std::istringstream input(to_be_parsed);
//    SourceInterface * scanner = new StringStreamSource(input);
//    Lexer lexer = Lexer(scanner);
//////    Parser parser = Parser(lexer);
////    Parser parser = Parser();
////    parser.set_lexer( &lexer );
//    Program program = Program();
//    parser.parseProgram(program);
//    Interpreter interpreter = Interpreter();
//    interpreter.interpret( program );

//    const std::string name = "num_1";
//    const std::variant<Number, Bool, String, ListOfVariantValues> value = Number(4);
//    std::list<Scope> lista_scopow;
//    lista_scopow.emplace_back( Scope() );
//    lista_scopow.rbegin()->set_symbol( name, value );
//////    std::map<std::string, std::variant<Number, Bool, String, ListOfVariantValues>> mapa;
//////    mapa.insert( {name, value });
//    std::cout<<"OK"<<std::endl;

//
//    int a = 1;
//    if( true == 1 == 2 )
//    {
//
//    }
//    auto val1 = std::make_unique<Bool>(true);
//    auto val1 = std::make_unique<Bool>(true);
//    std::unique_ptr<VariantValue> val1 = std::make_unique<Bool>(true);
//    std::unique_ptr<VariantValue> val2 = std::make_unique<Bool>(false);
//    std::unique_ptr<VariantValue> val3 = std::make_unique<Number>(1);
//    std::unique_ptr<VariantValue> val4 = std::make_unique<Number>(2);
//
//
//    std::unique_ptr<VariantValue> and_ = *val1 && val2;
//    std::unique_ptr<VariantValue> sum_ = *val3 + val4.get();
////    auto or_ = *val1 || val2.get();
//
//    and_->to_bool() ? std::cout<<"and true"<<std::endl : std::cout<<"and false"<<std::endl;
//    std::cout<<"sumowanie: "<<sum_->to_number()<<std::endl;
////    or_->to_bool() ? std::cout<<"or true"<<std::endl : std::cout<<"or false"<<std::endl;
//    std::cout<<"..."<<std::endl;
//    return 0;
}
