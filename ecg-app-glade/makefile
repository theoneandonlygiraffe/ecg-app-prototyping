# change application name here (executable output name)
TARGET=template_app

# compiler
CC=g++
# debug
DEBUG=-g
# optimisation
OPT=-O0
# warnings
WARN=-Wall -Wextra

PTHREAD=-pthread

CCFLAGS=$(DEBUG) $(OPT) $(WARN) $(PTHREAD) -pipe #-Wl --export-dynamic
GTKLIB=`pkg-config --cflags --libs gtk+-3.0`

# linker
LD=g++
LDFLAGS= $(PTHREAD) $(GTKLIB) -export-dynamic -rdynamic -lm #-lgmodule-export-2.0

OBJS=main.o filt.o paint.o vector_processing.o rect.o

all: $(OBJS)
	$(LD) -o $(TARGET) $(OBJS) $(LDFLAGS)
    
main.o: src/main.cpp $(OBJS)
	$(CC) -c $(CCFLAGS) src/main.cpp $(GTKLIB) -o main.o

filt.o: src/signal/filt.cpp src/signal/filt.h
	$(CC) -c $(CCFLAGS) src/signal/filt.cpp $(GTKLIB) -o filt.o

paint.o: src/paint/paint.cpp src/paint/paint.h src/paint/rect.cpp src/paint/rect.h
	$(CC) -c $(CCFLAGS) src/paint/paint.cpp $(GTKLIB) -o paint.o

vector_processing.o: src/signal/vector_processing.cpp src/signal/vector_processing.h
	$(CC) -c $(CCFLAGS) src/signal/vector_processing.cpp $(GTKLIB) -o vector_processing.o

rect.o: src/paint/rect.cpp src/paint/rect.h
	$(CC) -c $(CCFLAGS) src/paint/rect.cpp $(GTKLIB) -o rect.o
    
clean:
	rm -f *.o *.csv $(TARGET)

ccsv:
	rm -f *.csv

