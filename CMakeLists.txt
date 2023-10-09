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
set(CMAKE_PREFIX_PATH "~/Qt/6.1.3/gcc_64/lib/cmake")
set(INSTALL_DIR "build")
#set(SOURCE_DIR "src")

set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)

find_package(Qt6 COMPONENTS Core REQUIRED)
find_package(Qt6 COMPONENTS Gui REQUIRED)
find_package(Qt6 COMPONENTS Widgets REQUIRED)
find_package(Qt6 COMPONENTS Network REQUIRED)

add_subdirectory(network)
include_directories(network)
add_subdirectory(src)
include_directories(src)

find_package(Threads REQUIRED)

qt_add_executable(setupGameWindow
	include/board.hpp
	include/gameTile.hpp
	include/gameWindow.hpp
	src/gameWindow.cpp
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

install(TARGETS setupGameWindow
    RUNTIME DESTINATION "${INSTALL_DIR}"
    BUNDLE DESTINATION "${INSTALL_DIR}"
    LIBRARY DESTINATION "${INSTALL_DIR}"
)

qt_add_executable(server
	include/board.hpp
	include/gameTile.hpp
	include/gameWindow.hpp
	include/ChessCommon.hpp
	include/easylogging++.cc
	src/chess_server.cpp
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
	include/board.hpp
	include/gameTile.hpp
	include/gameWindow.hpp
	include/clientConnect.hpp
	include/ChessCommon.hpp
	include/easylogging++.cc
	src/chess_client.cpp
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
