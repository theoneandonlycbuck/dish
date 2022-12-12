CPP = g++-4.8

OPTIMIZATIONS = -Os

CFLAGS = -std=c++11 $(OPTIMIZATIONS) -I../../src/ -DLANG_TABLE_HASHED
LFLAGS = -L../../src/

BINS = main.o

LIBS = -ldish -lm -lncurses

TARGETS = pldish

################################################################################

.PHONY: all
all : $(TARGETS)

.PHONY: clean
clean :
	rm -f $(TARGETS)
	rm -f $(BINS)
	rm -f *~

################################################################################

pldish : $(BINS)
	$(CPP) $(LFLAGS) -o pldish $(BINS) $(LIBS)
	
################################################################################

main.o : main.cpp
	$(CPP) -c $(CFLAGS) main.cpp

