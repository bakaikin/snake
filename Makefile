
CXX = g++
CXXFLAGS = -c -std=c++0x
LDFLAGS = -g

snake : main.o game.o snake.o field.o common.o io.o
	$(CXX) $(LDFLAGS) main.o game.o snake.o field.o common.o io.o -o snake

main.o : main.cpp
	$(CXX) $(CXXFLAGS) main.cpp

game.o : game.cpp
	$(CXX) $(CXXFLAGS) game.cpp

snake.o : snake.cpp
	$(CXX) $(CXXFLAGS) snake.cpp

field.o : field.cpp
	$(CXX) $(CXXFLAGS) field.cpp

common.o : common.cpp
	$(CXX) $(CXXFLAGS) common.cpp

io.o : io.cpp
	$(CXX) $(CXXFLAGS) io.cpp

clean :
	rm -f snake *.o
