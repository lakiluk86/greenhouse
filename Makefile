all: dht22.cpp greenhouse.cpp mysql.cpp
	g++ greenhouse.cpp dht22.cpp mysql.cpp -o greenhouse -lwiringPi `mysql_config --cflags` `mysql_config --libs`

clean:
	rm -f greenhouse
