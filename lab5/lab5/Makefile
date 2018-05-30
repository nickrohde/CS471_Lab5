SRC_MAIN=main.cpp
SRC_BASE=FSS_Base.cpp
SRC_FSS=FSS.cpp
SRC_FSSB=FSSB.cpp
SRC_FSSNW=FSSNW.cpp

MAIN=main
BASE=base
CLASSES=classes

CXX=g++
FLAGS=-std=c++17 -pipe -Ofast -msse4 -ffast-math -ffinite-math-only


all: $(MAIN)

$(MAIN): $(CLASSES)
	$(CXX) $(SRC_MAIN) $(FLAGS) -o $(MAIN) *.o

$(CLASSES):
	$(CXX) -c $(SRC_BASE) $(SRC_FSS) $(SRC_FSSB) $(SRC_FSSNW) $(FLAGS)

	
removeObjects:
	rm -f *.o *.h.gch *.hpp.gch

clean: removeObjects
	rm -f $(MAIN)
