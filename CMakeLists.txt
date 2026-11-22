cmake_minimum_required(VERSION 3.19)
project(TrimStudio LANGUAGES CXX)

find_package(Qt6 6.10 REQUIRED COMPONENTS Core Widgets)

qt_standard_project_setup()
set(CMAKE_AUTORCC ON)

qt_add_executable(TrimStudio
    WIN32 MACOSX_BUNDLE
    main.cpp
    mainwindow.cpp
    mainwindow.h
    napravleniawindow.cpp
    napravleniawindow.h
    teacherswindow.cpp
    teacherswindow.h
    schedulewindow.cpp
    schedulewindow.h
    resour.qrc
)

target_link_libraries(TrimStudio
    PRIVATE
        Qt::Core
        Qt::Widgets
)

install(TARGETS TrimStudio
    BUNDLE  DESTINATION .
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
)

qt_generate_deploy_app_script(
    TARGET TrimStudio
    OUTPUT_SCRIPT deploy_script
    NO_UNSUPPORTED_PLATFORM_ERROR
)
install(SCRIPT ${deploy_script})
