CXX = g++
CXXFLAGS = `mysql_config --cflags`
LIBS = -lwiringPi `mysql_config --libs`

debug: CXXFLAGS += -Wall -g
debug: greenhouse-debug

all: greenhouse

greenhouse: greenhouse.o dht22.o mysql.o
	$(CXX) $(LIBS) -o greenhouse greenhouse.o dht22.o mysql.o

greenhouse-debug: greenhouse.o dht22.o mysql.o
	$(CXX) $(LIBS) -o greenhouse-debug greenhouse.o dht22.o mysql.o
	
%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $<

clean:
	rm -f greenhouse *.o
