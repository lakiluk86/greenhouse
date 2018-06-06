
#include <wiringPi.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <sys/types.h>
#include <unistd.h>

static const int MAXTIMINGS = 85;
static const float MAX_TEMP = 50.0f;
static const float MIN_TEMP = -50.0f;
static const float MAX_HUMIDITY = 100.0f;
static const float MIN_HUMIDITY = 0.0f;

using namespace std;

class DHT22 {
		int pin;
		uint8_t sizecvt(const int read);
	public:
		DHT22(int pin);
		int readData(float *temp, float *humi);
		int readData(float *temp, float *humi, int tries);
};
