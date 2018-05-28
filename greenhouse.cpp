
#include <sstream>
#include <string>
#include <wiringPi.h>
#include <mcp3004.h>
#include "dht22.h"
#include "mysql.h"

using namespace std;

#define DB_NAME  "raspberrydb"
#define DB_USERNAME "pi"
#define DB_PASSWORD "luky_luke8"

#define SPI_CHAN_MCP3008 0
#define MCP3008_PIN_BASE 12345

static int tries = 50;

int setup(MysqlConn *mysqlConn)
{
	if(mysqlConn->connect()){
		return 1;
	}
	if(wiringPiSetup() == -1){
		cerr << "Error wiring pi setup";
		return 1;
	}
	if(setuid(getuid()) < 0){
		cerr << "Dropping privileges failed";
		return 1;
	}
	if(mcp3004Setup(MCP3008_PIN_BASE, SPI_CHAN_MCP3008) == -1){
		cerr << "Error MCP3008 setup";
		return 1;
	}
	return 0;
}

int main(int argc, char *argv[])
{
	MysqlConn mysqlConn(DB_NAME, DB_USERNAME, DB_PASSWORD);
	stringstream sql_query;
	DHT22 dht22(7);
	float temperature, humidity;
	int brightness;
	
	if(setup(&mysqlConn)){
		exit(EXIT_FAILURE);
	}

	//read DHT22 sensor
	if(dht22.readData(&temperature, &humidity, tries)){
		cerr << "Unable to read sensor data";
		exit(EXIT_FAILURE);
	}
	
	//read channel 0 of mcp3008
	brightness = analogRead(MCP3008_PIN_BASE);
	
	printf("Temperature: %3.1f°, Humidity: %3.1f%%, Light: %d", temperature, humidity, brightness);
	
	//insert sensordata to db
	sql_query << "INSERT INTO sensor_data (temperature, humidity, brightness) \
		VALUES (" << temperature << ", " << humidity << ", " << brightness << ")";
	mysqlConn.query(sql_query.str());
	
	return 0;
}
