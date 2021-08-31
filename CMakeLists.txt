cmake_minimum_required(VERSION 3.10)

# set the project name
project(ChessNet)


# specify the C++ standard
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# Configure build flags
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -pthread")
if(UNIX)
    SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=gnu++17")
endif()

add_subdirectory(include)
add_subdirectory(include/network)
add_subdirectory(src)

include_directories(include)
include_directories(include/network)
include_directories(src)

find_package (Threads REQUIRED) #find pthreads package

# add the executable
add_executable(ChessNet-server src/chess_server.cpp)
add_executable(ChessNet-client src/chess_client.cpp)

target_link_libraries(ChessNet-server PUBLIC ChessLib ChessNetLib ${CMAKE_THREAD_LIBS_INIT})
target_link_libraries(ChessNet-client PUBLIC ChessLib ChessNetLib ${CMAKE_THREAD_LIBS_INIT})

target_include_directories(ChessNet-server PUBLIC 
								include
								include/network
								src
								)
target_include_directories(ChessNet-client PUBLIC 
								include
								include/network
								src
								)
                           