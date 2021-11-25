#ifndef UTILS_QT_H
#define UTILS_QT_H

#include <QObject>
#include <type_traits>

namespace utils_qt {

#define QX_PROPERTY_DECL(TYPE, GETTER, SETTER, VALUE) \
    Q_SIGNALS:\
        void GETTER##Changed(TYPE);\
    private: \
        Q_PROPERTY(TYPE GETTER READ GETTER WRITE SETTER NOTIFY GETTER##Changed)\
        TYPE m_##GETTER = VALUE;\
    public: \
        TYPE GETTER() const; \
        void SETTER(std::add_const_t<TYPE>& type); \

#define QX_PROPERTY_GETTER_IMPL(CLASS, GETTER) \
    decltype(CLASS::m_##GETTER) CLASS::GETTER() const { return m_##GETTER; } \

#define QX_PROPERTY_SETTER_IMPL(CLASS, GETTER, SETTER) \
    void CLASS::SETTER(typename std::add_const_t<decltype(m_##GETTER)>& val) { \
        if (val == m_##GETTER) \
            return; \
        m_##GETTER = val; \
        emit GETTER##Changed(m_##GETTER); \
    }

#define QX_PROPERTY_IMPL(CLASS, GETTER, SETTER) \
    QX_PROPERTY_GETTER_IMPL(CLASS, GETTER) \
    QX_PROPERTY_SETTER_IMPL(CLASS, GETTER, SETTER) \

} //namespace utils_qt
#endif // UTILS_QT_H
