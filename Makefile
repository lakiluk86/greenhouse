CXX = g++
CXXFLAGS = `mysql_config --cflags` -Wall -g
LIBS = -lwiringPi `mysql_config --libs`

greenhouse: greenhouse.o dht22.o mysql.o
	$(CXX) $(LIBS) -o greenhouse greenhouse.o dht22.o mysql.o

%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $<

clean:
	rm -f greenhouse %.o
