CXX = g++
CXXFLAGS = `mysql_config --cflags` -Wall -g
LIBS = -lwiringPi `mysql_config --libs`

greenhouse: dht22.o mysql.o greenhouse.o
	$(CXX) $(LIBS) $? -o greenhouse

%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $<

clean:
	rm -f greenhouse %.o
