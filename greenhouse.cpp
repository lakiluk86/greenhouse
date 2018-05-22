
#include "dht22.h"
#include "mysql.h"

#define DATABASE_NAME  "raspberrydb"
#define DATABASE_USERNAME "pi"
#define DATABASE_PASSWORD "luky_luke8"

static int tries = 50;

int setup(MysqlConn *mysqlConn)
{
	if(mysqlConn->connect()){
		return 1;
	}
	
	if (wiringPiSetup() == -1){
		cerr << "Error wiring pi setup";
		return 1;
	}

	if (setuid(getuid()) < 0){
		cerr << "Dropping privileges failed";
		return 1;
	}

	return 0;
}

int main(int argc, char *argv[])
{
	MysqlConn mysqlConn(DATABASE_NAME, DATABASE_USERNAME, DATABASE_PASSWORD);
	DHT22 dht22(7);
	float temp, humidity;
	
	if(setup(&mysqlConn)){
		exit(EXIT_FAILURE);
	}

	while (dht22.readData(&temp, &humidity) && tries--){
		delay(1000);
	}

	printf("Temperature: %3.1f°, Humidity: %3.1f%%", temp, humidity);
	mysqlConn.query("");
	
	return 0;
}
