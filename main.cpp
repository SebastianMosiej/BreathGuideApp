#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <iostream>
#include <BreathingGraphItem.h>
#include <BreathPhaseClass.h>
#include <QSurfaceFormat>
#include <QWindow>

int main(int argc, char* argv[])
{
    QGuiApplication app(argc, argv);
    
    QQmlApplicationEngine engine;
    BreathingGraphItem::init();
    BreathPhase::init();

    engine.addImportPath("qrc:/");
    engine.load("qrc:/qml/main.qml");

    QSurfaceFormat format;
    format.setSamples(16);
    auto window  = app.topLevelWindows();
    window.first()->setFormat(format);

    return app.exec();
}
