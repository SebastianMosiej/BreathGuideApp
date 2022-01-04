#ifndef BREATHPHASE_H
#define BREATHPHASE_H
#include <QObject>

namespace BreathPhase
{
    Q_NAMESPACE         // required for meta object creation
    enum Phase {
        INHALE_SECTION = 0,
        INHALE_HOLD_SECTION,
        EXHALE_SECTION,
        EXHALE_HOLD_SECTION,
        SECTION_MAX
    };
    Q_ENUM_NS(Phase)  // register the enum in meta object data
    void init();
}

#endif // BREATHPHASE_H
