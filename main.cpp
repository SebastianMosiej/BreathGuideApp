#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <iostream>
#include <BreathingGraphItem.h>

int main(int argc, char* argv[])
{
    QGuiApplication app(argc, argv);
    
    QQmlApplicationEngine engine;

    qmlRegisterType<BreathingGraphItem>("breathAppItems", 1, 0, "BreathingGraphItem");

    engine.addImportPath("qrc:/");
    engine.load("qrc:/qml/main.qml");


    return app.exec();
}
