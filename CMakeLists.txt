cmake_minimum_required(VERSION 3.10)
project(Semestralka)

set(CMAKE_CXX_STANDARD 14)
set(-lncurses)

find_package( Curses REQUIRED )
include_directories( ${CURSES_INCLUDE_DIRS} )



ADD_EXECUTABLE(Semestralka src/main.cpp src/CGame.cpp src/CDeck.cpp src/CCard.cpp src/CCardArtefakt.cpp src/CCardSpell.cpp src/CPlayer.cpp src/CPlayerComputer.cpp src/CPlayerHuman.cpp src/CPlayerComputerExpert.cpp src/CSaveSystem.cpp src/Graphics.cpp )
