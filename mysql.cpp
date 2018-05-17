
#include "mysql.h"

void mysql_connect(MYSQL *mysql1)
{
     //initialize MYSQL object for connections
     mysql1 = mysql_init(NULL);

     if(mysql1 == NULL)
     {
         fprintf(stderr, "ABB : %s\n", mysql_error(mysql1));
         return;
     }

     //Connect to the database
     if(mysql_real_connect(mysql1, "localhost", DATABASE_USERNAME, DATABASE_PASSWORD, DATABASE_NAME, 0, NULL, 0) == NULL)
     {
      fprintf(stderr, "%s\n", mysql_error(mysql1));
     }
     else
     {
         printf("Database connection successful.\r\n");
     }
}

void mysql_disconnect(MYSQL *mysql1)
{
     mysql_close(mysql1);
     printf( "Disconnected from database.\r\n");
}

void mysql_write_something(MYSQL *mysql1)
{
    //vector times;   //a vector of alarm times
     if(mysql1 != NULL)
     {
         //Retrieve all data from alarm_times
         if (mysql_query(mysql1, "INSERT INTO temp_sens (   \
     id,   \
     value   \
    ) VALUES (   \
     99,   \
     '50'   \
    ) \
    "))

         { 
              fprintf(stderr, "%s\n", mysql_error(mysql1));
              return;
         }
     }
}
