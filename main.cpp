#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <iostream>
#include <BreathingGraphItem.h>
#include <QSurfaceFormat>
#include <QWindow>

int main(int argc, char* argv[])
{
    QGuiApplication app(argc, argv);
    
    QQmlApplicationEngine engine;

    qmlRegisterType<BreathingGraphItem>("breathAppItems", 1, 0, "BreathingGraphItem");

    engine.addImportPath("qrc:/");
    engine.load("qrc:/qml/main.qml");

    QSurfaceFormat format;
    format.setSamples(16);
    app.topLevelWindows().first()->setFormat(format);

    return app.exec();
}
