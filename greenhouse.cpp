
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

#define DHT22_PIN 7
#define DHT22_TRIES 20

#define MOISTURE_PIN 0

#define MCP3008_SPI_CHAN 0
#define MCP3008_PIN_BASE 12345
#define MCP3008_CHAN_BRIGHTNESS 0
#define MCP3008_CHAN_MOISTURE 1

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
	if(mcp3004Setup(MCP3008_PIN_BASE, MCP3008_SPI_CHAN) == -1){
		cerr << "Error MCP3008 setup";
		return 1;
	}
	return 0;
}

int readMoisture()
{
	int moisture;
	
	pinMode(MOISTURE_PIN, OUTPUT);
	digitalWrite(MOISTURE_PIN, HIGH);
	delay(1000);
	moisture = analogRead(MCP3008_PIN_BASE + MCP3008_CHAN_MOISTURE);
	digitalWrite(MOISTURE_PIN, LOW);
	
	return moisture;
}

int main(int argc, char *argv[])
{
	MysqlConn mysqlConn(DB_NAME, DB_USERNAME, DB_PASSWORD);
	stringstream sql_query;
	DHT22 dht22(DHT22_PIN);
	float temperature, humidity;
	int brightness, moisture;
	
	if(setup(&mysqlConn)){
		exit(EXIT_FAILURE);
	}

	//read DHT22 sensor
	if(dht22.readData(&temperature, &humidity, DHT22_TRIES)){
		cerr << "Unable to read sensor data";
		exit(EXIT_FAILURE);
	}
	
	//read channel brightness of adc
	brightness = analogRead(MCP3008_PIN_BASE + MCP3008_CHAN_BRIGHTNESS);
	
	//read channel moisture of adc
	moisture = readMoisture();
	
	printf("Temperature: %3.1f°, Humidity: %3.1f%%, Brightness: %d, Moisture: %d", temperature, humidity, brightness, moisture);
	
	//insert sensordata to db
	sql_query << "INSERT INTO sensor_data (temperature, humidity, brightness, moisture) \
		VALUES (" << temperature << ", " << humidity << ", " << brightness << ", " << moisture << ")";
	mysqlConn.query(sql_query.str());
	
	return 0;
}
