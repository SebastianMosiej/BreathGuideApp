cmake_minimum_required(VERSION 3.1.0)

project(breathGuideApp VERSION 1.0.0 LANGUAGES C CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)

find_package(Qt6 COMPONENTS Quick REQUIRED)

set(APPNAME breathGuideApp )

set(SOURCES
    main.cpp
    BreathingGraphItem.cpp
    BreathingGraphItem.h
    BreathPhaseClass.h
    utils_qt.h
    breathGuideApp.qrc
)

add_executable(${APPNAME} ${SOURCES})

target_include_directories(${APPNAME} 
PUBLIC 
    ${CMAKE_SOURCE_DIR}
PRIVATE
    ${CMAKE_SOURCE_DIR}/common        
)

set(QML_IMPORT_PATH ${CMAKE_CURRENT_LIST_DIR}/qml CACHE STRING "" FORCE)

target_link_libraries(${APPNAME} Qt6::Quick )

install(TARGETS ${APPNAME}
    COMPONENT ${APPNAME}
    RUNTIME DESTINATION "/usr/bin"
    LIBRARY DESTINATION "/usr/lib"
)
