#ifndef BREATHPHASE_H
#define BREATHPHASE_H
#include <QObject>
#include <QQmlEngine>

namespace BreathPhase
{
    Q_NAMESPACE         // required for meta object creation
    enum Phase {
        INHALE_SECTION = 0,
        INHALE_HOLD_SECTION,
        EXHALE_SECTION,
        EXHALE_HOLD_SECTION,
        SECTION_MAX,
        NONE_SECTION = 10
    };
    Q_ENUM_NS(Phase)  // register the enum in meta object data
    inline void init() {
        qmlRegisterUncreatableMetaObject(
            BreathPhase::staticMetaObject,  // meta object created by Q_NAMESPACE macro
            "breathAppItems",               // import statement (can be any string)
            1, 0,                           // major and minor version of the import
            "BreathPhase",                  // name in QML (does not have to match C++ name)
            "Can't create Enum type in QML" // error in case someone tries to create a MyNamespace object
        );
    }
}

#endif // BREATHPHASE_H
