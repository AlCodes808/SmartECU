CC=gcc
CFLAGS=-Iinclude
SRC=src/main.c src/SensorReader.c src/DataProcessor.c src/DataLogger.c
OBJ=$(SRC:.c=.o)
EXEC=SmartECU.exe

all: $(EXEC)

$(EXEC): $(OBJ)
	$(CC) $(CFLAGS) -o $@ $(OBJ)

clean:
	rm -f $(OBJ) $(EXEC)