CXX = g++
CXXFLAGS = `mysql_config --cflags`
LIBS = -lwiringPi `mysql_config --libs`

debug: CXXFLAGS += -Wall -g
debug: greenhouse

all: greenhouse

greenhouse: greenhouse.o dht22.o mysql.o
	$(CXX) $(LIBS) -o greenhouse greenhouse.o dht22.o mysql.o

%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $<

clean:
	rm -f greenhouse *.o
