CC=g++ -std=c++14
CFLAGS=-c -Wall
LDFLAGS=
SOURСES=main.cpp matrix.cpp
OBJECTS=$(SOURСES:.cpp=.o)
EXECUTABLE=app

all: $(EXECUTABLE)

$(EXECUTABLE): $(OBJECTS)
	$(CC) $(LDFLAGS) $(OBJECTS) -o $@
	./$(EXECUTABLE)

test: $(OBJECTS)
	$(CC) $(LDFLAGS) $(OBJECTS) -o $(EXECUTABLE)
	./$(EXECUTABLE) test

main.o: main.cpp
	$(CC) $(OPTIMIZATION) $(CFLAGS) $< -o $@

.cpp.o:
	$(CC) $(OPTIMIZATION) $(CFLAGS) $< -o $@

clean:
	rm -rf *.o $(EXECUTABLE)

