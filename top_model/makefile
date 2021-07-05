CC=g++
CFLAGS=-std=c++17
COMPILE_TARGET=NUCLEO_H743ZI2
FLASH_TARGET=NODE_F401RE1
EXECUTABLE_NAME=DEVS_complimentary_filter

INCLUDRT_ARM_MBED=-I ../cadmium/include
INCLUDEDESTIMES=-I ../cadmium/DESTimes/include
INCLUDEBOOST=-I /usr/include/
INCLUDEALGORITHMS=-I ../algorithms
INCLUDEATOMICS=-I ../atomics
INCLUDEDATA=-I ../data_structures

embedded:
	mbed compile --target $(COMPILE_TARGET) --toolchain GCC_ARM --profile ../cadmium.json

flash:
	sudo cp ../BUILD/$(COMPILE_TARGET)/GCC_ARM-CADMIUM/*.bin /media/$(USER)/$(FLASH_TARGET)/
	$(info *** FLASH MAKE TAKE ~10 Seconds! DO NOT RESET WHILE COM PORT LED IS FLASHING! ***)


all: main fusion 
	$(CC) -g -o $(EXECUTABLE_NAME) main.o message.o
	rm *.o

main: main.cpp
	$(CC) -g -c $(CFLAGS) $(INCLUDRT_ARM_MBED) $(INCLUDEDESTIMES) $(INCLUDEBOOST) $(INCLUDEALGORITHMS) $(INCLUDEATOMICS) $(INCLUDEDATA) main.cpp -o main.o

fusion: ../data_structures/message.cpp
	$(CC) -g -c $(CFLAGS) $(INCLUDRT_ARM_MBED) $(INCLUDEDESTIMES) $(INCLUDEBOOST) $(INCLUDEALGORITHMS) $(INCLUDEATOMICS) $(INCLUDEDATA) ../data_structures/message.cpp -o message.o

clean:
	rm -f $(EXECUTABLE_NAME) *.o *~

eclean:
	rm -rf ../BUILD
