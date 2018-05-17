
#include <wiringPi.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <sys/types.h>
#include <unistd.h>

#define MAXTIMINGS 85

static int dht22_dat[5] = {0,0,0,0,0};

uint8_t sizecvt(const int read);
int read_dht22_dat(int pin);
float get_temp();
float get_humidity();
