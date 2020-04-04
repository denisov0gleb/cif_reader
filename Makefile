CC = gcc
CFLAGS = -o

EXECUTABLE = cif_reader


ifeq ($(OS),Windows_NT) 
	REMOVE = del /s /q
	REMOVE_DIR = rmdir /s /q
else
	REMOVE = rm -rf
endif


all: $(EXECUTABLE) test_cif


$(EXECUTABLE):
	mkdir build
	$(CC) $(CFLAGS) ./build/$(EXECUTABLE).exe ./src/$(EXECUTABLE).c

test_cif:
	./build/$(EXECUTABLE).exe ./examples/AL2001.cif

clean:
	$(REMOVE) *.exe *.o *.txt
	$(REMOVE_DIR) build
