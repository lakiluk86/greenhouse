
#include "dht22.h"
#include "mysql.h"

using namespace std;

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
	float temperature, humidity;
	
	if(setup(&mysqlConn)){
		exit(EXIT_FAILURE);
	}

	if(dht22.readData(&temp, &humidity, tries)){
		cerr << "Unable to read sensor data";
		exit(EXIT_FAILURE);
	}

	printf("Temperature: %3.1f°, Humidity: %3.1f%%", temperature, humidity);
	mysqlConn.query("INSERT INTO temp_sens (temperature, humidity) VALUES (" << temperature << ", " << humidity << ")");
	
	return 0;
}
