
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <mysql/mysql.h>

#define DATABASE_NAME  "raspberrydb"
#define DATABASE_USERNAME "pi"
#define DATABASE_PASSWORD "luky_luke8"

void mysql_connect(MYSQL *mysql1);
void mysql_disconnect(MYSQL *mysql1);
void mysql_write_something(MYSQL *mysql1);
