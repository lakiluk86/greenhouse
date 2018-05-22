
#include <wiringPi.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <sys/types.h>
#include <unistd.h>

#define MAXTIMINGS 85

using namespace std;

class DHT22 {
		int dht22_dat[5] = {0,0,0,0,0};
		int pin;
		uint8_t sizecvt(const int read);
	public:
		DHT22(int pin);
		int readData(float *temp, float *humi);
};