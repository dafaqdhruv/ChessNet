# Generated from application.pro.

cmake_minimum_required(VERSION 3.14)
project(application LANGUAGES CXX)

set(CMAKE_INCLUDE_CURRENT_DIR ON)
set(CMAKE_PREFIX_PATH "/home/dfqm8/Qt/6.1.3/gcc_64/lib/cmake")
set(INSTALL_DIR "build")

set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)

find_package(Qt6 COMPONENTS Core REQUIRED)
find_package(Qt6 COMPONENTS Gui REQUIRED)
find_package(Qt6 COMPONENTS Widgets REQUIRED)

qt_add_executable(application
    main.cpp
    connectClientWindow.hpp
)
set_target_properties(application PROPERTIES
    WIN32_EXECUTABLE TRUE
    MACOSX_BUNDLE TRUE
)
target_link_libraries(application PUBLIC
    Qt::Core
    Qt::Gui
    Qt::Widgets
)


qt6_add_resources(application "application"
    PREFIX
        "/"
    FILES
        ${application_resource_files}
)

install(TARGETS application
    RUNTIME DESTINATION "${INSTALL_DIR}"
    BUNDLE DESTINATION "${INSTALL_DIR}"
    LIBRARY DESTINATION "${INSTALL_DIR}"
)
