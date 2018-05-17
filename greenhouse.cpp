
#include "dht22.h"
#include "mysql.h"

static int tries = 50;
MYSQL *mysql;

int setup()
{
  mysql_connect(mysql);
	
  if (wiringPiSetup() == -1){
    return 0;
  }
  
  if (setuid(getuid()) < 0){
    perror("Dropping privileges failed\n");
    return 0;
  }
  
  return 1;
}

int main(int argc, char *argv[])
{
  if(setup() == 0){
      exit(EXIT_FAILURE);
  }
  
  while (read_dht22_dat(7) == 0 && tries--){
     delay(1000); // wait 1sec to refresh
  }
  
  printf("Temperature: %3.1f°, Humidity: %3.1f%%", get_temp(), get_humidity());
  
  delay(1500);
  mysql_write_something(mysql);
  mysql_disconnect(mysql);
  return 0;
}
