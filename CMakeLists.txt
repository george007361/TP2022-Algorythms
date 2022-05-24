cmake_minimum_required(VERSION 3.16)
project(graphs)

set(CMAKE_CXX_STANDARD 11)

set(SOURCES
./ArcGraph/ArcGraph.cpp
./IGraph/IGraph.cpp
./ListGraph/ListGraph.cpp
./MatrixGraph/MatrixGraph.cpp
./SetGraph/SetGraph.cpp
./main.cpp
)

set( HEADERS
./ArcGraph/ArcGraph.h
./IGraph/IGraph.h
./ListGraph/ListGraph.h
./MatrixGraph/MatrixGraph.h
./SetGraph/SetGraph.h
)

add_executable(graphs ${SOURCES} ${HEADERS})