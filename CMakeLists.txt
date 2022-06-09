cmake_minimum_required(VERSION 3.1.0)
project(Chess)

set(CMAKE_CXX_STANDARD 11)

set(SRC_DIRECTORY src)
set(INCLUDE_DIRECTORY headers)

set(SOURCES
	${SRC_DIRECTORY}/Piece.cpp
	${SRC_DIRECTORY}/King.cpp
	${SRC_DIRECTORY}/Bishop.cpp
	${SRC_DIRECTORY}/Knight.cpp
	${SRC_DIRECTORY}/Pawn.cpp
	${SRC_DIRECTORY}/Queen.cpp
	${SRC_DIRECTORY}/Rook.cpp
	${SRC_DIRECTORY}/GameBoard.cpp
)

include_directories(${INCLUDE_DIRECTORY})
add_executable(${PROJECT_NAME}
	${SRC_DIRECTORY}/main.cpp
	${SOURCES})

target_link_libraries(${PROJECT_NAME} sfml-system sfml-window sfml-graphics)