# Generated from application.pro.

cmake_minimum_required(VERSION 3.14)
project(application LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# Configure build flags
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -pthread")
if(UNIX)
    SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=gnu++17")
endif()


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

add_subdirectory(network)
include_directories(network)
find_package(Threads REQUIRED)

#qt_add_executable(connectClient
#      clientConnect.hpp
#      clientConnect.cpp
#)

#qt_add_executable(setupScrambler
#	setupServer.cpp
#	setupServer.hpp   
#)
#
#qt_add_executable(main
#    commonWindows.hpp
#    main.cpp
#)
qt_add_executable(setupGameWindow
	board.hpp
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
#set_target_properties(main PROPERTIES
#    WIN32_EXECUTABLE TRUE
#    MACOSX_BUNDLE TRUE
#)
#target_link_libraries(main PUBLIC
#    Qt::Core
#    Qt::Gui
#    Qt::Widgets
#    Qt::Network
#)
#qt6_add_resources(main "clientSide"
#    PREFIX
#        "/"
#    FILES
#        ${application_resource_files}
#
#)
#install(TARGETS main 
#    RUNTIME DESTINATION "${INSTALL_DIR}"
#    BUNDLE DESTINATION "${INSTALL_DIR}"
#    LIBRARY DESTINATION "${INSTALL_DIR}"
#)
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
#
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
#qt_add_executable(main
#    commonWindows.hpp
#    main.cpp
#)



qt_add_executable(server
	board.hpp
	gameTile.hpp
	gameWindow.hpp
      ChessCommon.hpp
      chess_server.cpp
)

set_target_properties(server PROPERTIES
    WIN32_EXECUTABLE TRUE
    MACOSX_BUNDLE TRUE
)
target_link_libraries(server PUBLIC
    Qt::Core
    Qt::Gui
    Qt::Widgets
    Qt::Network
    ChessNetLib
    ${CMAKE_THREAD_LIBS_INIT}
)
qt6_add_resources(server "icons"
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
install(TARGETS server
    RUNTIME DESTINATION "${INSTALL_DIR}"
    BUNDLE DESTINATION "${INSTALL_DIR}"
    LIBRARY DESTINATION "${INSTALL_DIR}"
)

qt_add_executable(client
	board.hpp
	gameTile.hpp
	gameWindow.hpp
      ChessCommon.hpp
      chess_client.cpp
)

set_target_properties(client PROPERTIES
    WIN32_EXECUTABLE TRUE
    MACOSX_BUNDLE TRUE
)
target_link_libraries(client PUBLIC
    Qt::Core
    Qt::Gui
    Qt::Widgets
    Qt::Network
    ChessNetLib
    ${CMAKE_THREAD_LIBS_INIT}
)
qt6_add_resources(client "icons"
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
install(TARGETS client
    RUNTIME DESTINATION "${INSTALL_DIR}"
    BUNDLE DESTINATION "${INSTALL_DIR}"
    LIBRARY DESTINATION "${INSTALL_DIR}"
)
