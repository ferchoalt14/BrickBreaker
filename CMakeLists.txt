cmake_minimum_required(VERSION 3.16)
project(BrickBreaker LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(Qt6 REQUIRED COMPONENTS Core Widgets Multimedia)
qt_standard_project_setup()

set(CMAKE_AUTORCC ON)

qt_add_executable(BrickBreaker
    WIN32 MACOSX_BUNDLE
    main.cpp
    motorjuego.h motorjuego.cpp
    pruebamotor.h pruebamotor.cpp
    startscreen.h startscreen.cpp
    loginscreen.h loginscreen.cpp
    storyscreen.h storyscreen.cpp
    menuscreen.h menuscreen.cpp
    mapscreen.h mapscreen.cpp
    usuario.h usuario.cpp
    gestorusuarios.h gestorusuarios.cpp
    resources.qrc
)

target_link_libraries(BrickBreaker PRIVATE
    Qt6::Core
    Qt6::Widgets
    Qt6::Multimedia
)

include(GNUInstallDirs)
install(TARGETS BrickBreaker
    BUNDLE DESTINATION .
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)
