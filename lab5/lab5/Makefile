SRC_MAIN=main.cpp
SRC_BASE=FSS_Base.cpp
SRC_FSS=FSS.cpp
SRC_FSSB=FSSB.cpp
SRC_FSSNW=FSSNW.cpp

MAIN=main
BASE=base
CLASSES=classes

COMP_MAC=clang++
COMP_LINUX=g++
STD_LINUX=-std=c++17
STD_MAC=-std=c++1z
# delete will generate 3 warnings that can be ignored, thus -w
FLAGS=-pipe -Ofast -msse4 -ffast-math -ffinite-math-only -w -pthread

# check OS as clang++ does not support c++17 
ifeq ($(OS), Linux)
	STD := $(STD_LINUX)
	CXX := $(COMP_LINUX)
else
	ifeq ($(OS), Windows)
		$(error Use Visual Studio for Windows Compilation)
	else 
		STD := $(STD_MAC)
		CXX := $(COMP_MAC)
	endif 
endif



all: $(MAIN)

$(MAIN): $(CLASSES)
	$(CXX) $(SRC_MAIN) $(FLAGS) $(STD) -o $(MAIN) *.o

$(CLASSES):
	$(CXX) -c $(SRC_BASE) $(SRC_FSS) $(SRC_FSSB) $(SRC_FSSNW) $(FLAGS) $(STD)

	
removeObjects:
	rm -f *.o *.h.gch *.hpp.gch

clean: removeObjects
	rm -f $(MAIN)
