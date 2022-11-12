CXX=g++
CXXFLAGS=-Wall -pedantic -g -fsanitize=address -Wno-long-long -O2
O= src/main.o src/Graphics.o src/CGame.o src/CCard.o src/CCardArtefakt.o src/CCardSpell.o src/CDeck.o src/CPlayer.o src/CPlayerComputer.o src/CPlayerHuman.o src/CPlayerComputerExpert.o src/CSaveSystem.o 
LIBS=-lncurses


all: doc semestral run


clean:
	rm -f rohusdav src/*.o src/*~ core
	rm -r ./doc


run:
	./rohusdav

compile: semestral

doc:
	doxygen doxfile



semestral: $(O)
	$(CXX) $(CXXFLAGS) $(O)  -o rohusdav ${LIBS}

Graphics.o: src/Graphics.h
main.o: src/main.cpp
CGame.o: src/Graphics.h src/CGame.h
CCard.o: src/CCard.h src/SEffect.h
CCardArtefakt.o: src/CCardArtefakt.h src/CCard.h
CCardSpell.o: src/CCardArtefakt.h src/CCard.h
CDeck.o: src/CDeck.h  src/SEffect.h
CPlayer.o: src/CPlayer.h
CPlayerComputer.o: src/CPlayerComputer.h src/CPlayer.h
CPlayerHuman.o: src/CPlayerHuman.h src/CPlayer.h
cPlayerComputerExpert.o: src/CPlayerComputerExpert.h src/CPlayerComputer.h src/CPlayer.h
SEffect.o: src/SEffect.h
CSafeSystem.o: src/CSaveSystem.h src/CGame.h


%.o: %.cpp %.h
	$(CXX)  -c $< -o $@
