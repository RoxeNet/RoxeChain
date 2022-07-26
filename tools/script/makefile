CC=gcc
CFLAGS=-Wall
EXE=roxe
EXE_WATCH=watchapp

ifeq ($(ver), roxe)
all:
	$(CC) $(CFLAGS) $(EXE).c -o ../$(EXE)

else ifeq ($(ver), watchapp)
all:
	$(CC) $(CFLAGS) $(EXE_WATCH).c -o ../$(EXE_WATCH)
else

all:	
	$(CC) $(CFLAGS) $(EXE).c -o ../$(EXE)
	$(CC) $(CFLAGS) $(EXE_WATCH).c -o ../$(EXE_WATCH)
endif

clean:
	rm -rf *.o ../$(EXE)
	rm -rf *.o ../$(EXE_WATCH)
