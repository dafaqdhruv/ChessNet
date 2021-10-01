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
find_package(Qt6 COMPONENTS Network REQUIRED)

#qt_add_executable(connectClient
#	connectClient.cpp
#	connectClientWindow.hpp
#)
#
#qt_add_executable(setupScrambler
#	setupServer.cpp
#	setupServer.hpp   
#)

qt_add_executable(setupGameWindow
	gameTile.hpp
	gameWindow.hpp
	gameWindow.cpp

)

set_target_properties(setupGameWindow PROPERTIES
    WIN32_EXECUTABLE TRUE
    MACOSX_BUNDLE TRUE
)
target_link_libraries(setupGameWindow PUBLIC
    Qt::Core
    Qt::Gui
    Qt::Widgets
    Qt::Network
)
qt6_add_resources(setupGameWindow "icons"
    PREFIX
	  "/"
    FILES
	  "icons/whiteKing.png"
	  "icons/whiteQueen.png"
	  "icons/whiteRook.png"
	  "icons/whiteBishop.png"
	  "icons/whitePawn.png"
	  "icons/whiteKnight.png"
	  "icons/blackKing.png"
	  "icons/blackQueen.png"
	  "icons/blackRook.png"
	  "icons/blackBishop.png"
	  "icons/blackPawn.png"
	  "icons/blackKnight.png"
)
#set_target_properties(connectClient PROPERTIES
#    WIN32_EXECUTABLE TRUE
#    MACOSX_BUNDLE TRUE
#)
#target_link_libraries(connectClient PUBLIC
#    Qt::Core
#    Qt::Gui
#    Qt::Widgets
#    Qt::Network
#)
#qt6_add_resources(connectClient "clientSide"
#    PREFIX
#        "/"
#    FILES
#        ${application_resource_files}
#
#)
#
#set_target_properties(setupScrambler PROPERTIES
#    WIN32_EXECUTABLE TRUE
#    MACOSX_BUNDLE TRUE
#)
#target_link_libraries(setupScrambler PUBLIC
#    Qt::Core
#    Qt::Gui
#    Qt::Widgets
#    Qt::Network
#)
#
#qt6_add_resources(setupScrambler "serverSide"
#    PREFIX
#        "/"
#    FILES
#        ${application_resource_files}
#)

#install(TARGETS connectClient 
#    RUNTIME DESTINATION "${INSTALL_DIR}"
#    BUNDLE DESTINATION "${INSTALL_DIR}"
#    LIBRARY DESTINATION "${INSTALL_DIR}"
#)
#
#install(TARGETS setupScrambler
#    RUNTIME DESTINATION "${INSTALL_DIR}"
#    BUNDLE DESTINATION "${INSTALL_DIR}"
#    LIBRARY DESTINATION "${INSTALL_DIR}"
#)

install(TARGETS setupGameWindow
    RUNTIME DESTINATION "${INSTALL_DIR}"
    BUNDLE DESTINATION "${INSTALL_DIR}"
    LIBRARY DESTINATION "${INSTALL_DIR}"
)
