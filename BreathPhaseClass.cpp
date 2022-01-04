#include "BreathPhaseClass.h"
#include <QQmlEngine>

namespace BreathPhase {
void init() {
    qmlRegisterUncreatableMetaObject(
        BreathPhase::staticMetaObject,  // meta object created by Q_NAMESPACE macro
        "breathAppItems",               // import statement (can be any string)
        1, 0,                           // major and minor version of the import
        "BreathPhase",                  // name in QML (does not have to match C++ name)
        "Can't create Enum type in QML" // error in case someone tries to create a MyNamespace object
    );
}

} //end namespace BreathPhase
