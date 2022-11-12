CXX=g++
CXXFLAGS=-Wall -pedantic -fsanitize=address -Wno-long-long -O2
LD=g++
LDFLAGS=-Wall -pedantic -fsanitize=address -Wno-long-long -O2
O= src/main.o src/CGame.o src/CCard.o src/CCardArtefakt.o src/CCardSpell.o src/CDeck.o src/CPlayer.o src/CPlayerComputer.o src/CPlayerHuman.o
LIBS=-lncurses

all: semestral doc run


clean:
	rm -f rohusdav src/*.o src/*~ core
	rm -r ./doc


run:
	./src/rohusdav

compile: semestral

doc:
	doxygen doxfile



semestral: $(O)
	$(LD) $(LDFLAGS) $(O)  -o rohusdav ${LIBS}


main.o: src/main.cpp
CGame.o: src/CGame.h
CGraphics.o: src/CGraphics.h

CCard.o: src/CCard.h src/SEffect.h

CCardArtefakt.o: src/CCardArtefakt.h src/CCard.h
CCardSpell.o: src/CCardArtefakt.h src/CCard.h
CDeck.o: src/CDeck.h  src/SEffect.h
CPlayer.o: src/CPlayer.h
CPlayerComputer.o: src/CPlayerComputer.h src/CPlayer.h
CPlayerHuman.o: src/CPlayerHuman.h src/CPlayer.h
SEffect.o: src/SEffect.h





%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

