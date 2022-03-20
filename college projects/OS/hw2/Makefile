CC = g++
OBJ = program1 program2 program3
CXXFLAGS = --std=c++11

main:: $(OBJ)
program1:
	$(CC) $(CXXFLAGS) -o program1 p1.cpp

program2:
	$(CC) $(CXXFLAGS) -o program2 p2.cpp

program3:
	$(CC) $(CXXFLAGS) -o program3 p3.cpp -lpthread

clean:
	rm -f $(OBJ)
