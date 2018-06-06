
#include "dht22.h"

using namespace std;

/* digitalRead() and friends from wiringpi are defined as returning a value
< 256. However, they are returned as int() types. This is a safety function */
uint8_t DHT22::sizecvt(const int read)
{
	if (read > 255 || read < 0){
		printf("Invalid data from wiringPi library\n");
		exit(EXIT_FAILURE);
	}
	
	return (uint8_t)read;
}

int DHT22::readData(float *temperature, float *humidity, int tries)
{
	int status = 1;
	
	while((status = readData(temperature, humidity)) && tries--){
		delay(1000);
	}
	
	return status;
}

int DHT22::readData(float *temperature, float *humidity)
{
	int dht22_dat[5] = {0,0,0,0,0};
	uint8_t laststate = HIGH;
	uint8_t counter = 0;
	uint8_t j = 0, i;

	// pull pin down for 18 milliseconds
	pinMode(pin, OUTPUT);
	digitalWrite(pin, HIGH);
	delay(10);
	digitalWrite(pin, LOW);
	delay(18);
	// then pull it up for 40 microseconds
	digitalWrite(pin, HIGH);
	delayMicroseconds(40);
	// prepare to read the pin
	pinMode(pin, INPUT);

	// detect change and read data
	for(i=0; i< MAXTIMINGS; i++){
		counter = 0;
		
    		while(sizecvt(digitalRead(pin)) == laststate){
			counter++;
			delayMicroseconds(2);
			if (counter == 255) break;
		}
		
		laststate = sizecvt(digitalRead(pin));
		if (counter == 255) break;

		// ignore first 3 transitions
		if ((i >= 4) && (i%2 == 0)) {
			// shove each bit into the storage bytes
			dht22_dat[j/8] <<= 1;
			if (counter > 16)
			dht22_dat[j/8] |= 1;
			j++;
		}
	}

	// check we read 40 bits (8bit x 5 ) + verify checksum in the last byte
	if ((j >= 40) && (dht22_dat[4] == ((dht22_dat[0] + dht22_dat[1] + dht22_dat[2] + dht22_dat[3]) & 0xFF))){
		float t, h;
		
		//calc temp
		t = (float)(dht22_dat[2] & 0x7F)* 256 + (float)dht22_dat[3];
		t /= 10.0;
		if ((dht22_dat[2] & 0x80) != 0)  t *= -1;
		
		//calc humidity
		h = (float)dht22_dat[0] * 256 + (float)dht22_dat[1];
		h /= 10;

		if((t > MIN_TEMP && t < MAX_TEMP) && (h > MIN_HUMIDITY && h < MAX_HUMIDITY)){
			*temperature = t;
			*humidity = h;
			return 0;
		}
	}
	
	//data not good
	return 1;
}

DHT22::DHT22(int pin)
{
	this->pin = pin;
}
