PRG    = rpi_mcp3208
OBJ    = main.o mcp3208.o

CC       = g++
CXXFLAGS = -Wall -O2 -std=c++11 -Iinclude
LDFLAGS  = -lwiringPi

$(PRG): $(OBJ)
	$(CC) -o $@ $^ $(CXXFLAGS) $(LDFLAGS)

main.o: main.cpp
	$(CC) -c $^ $(CXXFLAGS) $(LDFLAGS)

mcp3208.o: src/mcp3208.cpp
	$(CC) -c $^ $(CXXFLAGS) $(LDFLAGS)

.PHONY: clean
clean:
	rm -f $(PRG) $(OBJ)
