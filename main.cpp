#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QQmlContext>
#include <QQuickItem>

int main(int argc, char** argv) {
    QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);
    QGuiApplication app {argc, argv};
    QQmlApplicationEngine engine;
    QObject::connect(&engine, &QQmlApplicationEngine::quit, &app, &QGuiApplication::quit, Qt::QueuedConnection);
    QObject::connect(&engine, &QQmlApplicationEngine::exit, &app, &QGuiApplication::exit, Qt::QueuedConnection);

    engine.load(QUrl("qrc:/main.qml"));
    return( QGuiApplication::exec() );
}
