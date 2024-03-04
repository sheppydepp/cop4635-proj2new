CXX = g++
CXXFLAGS = -std=c++17 -g -Wall

OBJECTS = Server.o 

server: $(OBJECTS) server_main.cpp
	$(CXX) $(CXXFLAGS) $^ -o $@

client: $(OBJECTS) client_main.cpp
	$(CXX) $(CXXFLAGS) $^ -o $@

clean:
	$(RM) *.o main
