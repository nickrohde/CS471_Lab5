SRC_MAIN=main.cpp
SRC_BASE=FSS_Base.cpp
SRC_FSS=FSS.cpp
SRC_FSSB=FSSB.cpp
SRC_FSSNW=FSSNW.cpp

MAIN=main
BASE=base
FSS=flowshopsched
FSSB=flowshopblock
FSSNW=flowshopnowait

CXX=g++
FLAGS=-std=c++17


all: $(MAIN)

$(MAIN): $(FSS) $(FSSB) $(FSSNW)
	$(CXX) $(SRC_MAIN) $(FLAGS) -o $(MAIN) *.o

$(FSS): $(BASE)
	$(CXX) -c $(SRC_FSS) $(FLAGS)

$(FSSB): $(BASE)
	$(CXX) -c $(SRC_FSSB) $(FLAGS)

$(FSSNW): $(BASE)
	$(CXX) -c $(SRC_FSSNW) $(FLAGS)

$(BASE):
	$(CXX) -c $(SRC_BASE) $(FLAGS)
	
removeObjects:
	rm -f *.o *.h.gch *.hpp.gch

clean: removeObjects
	rm -f $(MAIN)