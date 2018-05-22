
#include "mysql.h"

using namespace std;

MysqlConn::MysqlConn(string database, string username, string password)
{
	this->database = database;
	this->username = username;
	this->password = password;
}

MysqlConn::~MysqlConn()
{
	mysql_close(mysql);
}

int MysqlConn::connect()
{
	mysql = mysql_init(NULL);

	if(mysql == NULL) {
		cerr << mysql_error(mysql);
		return 1;
	}

	if(mysql_real_connect(mysql, "localhost", username.c_str(), password.c_str(), database.c_str(), 0, NULL, 0) == NULL){
		cerr << mysql_error(mysql);
		return 1;
	}
	
	return 0;
}

int MysqlConn::query(string sql)
{
	 if(mysql != NULL) {
		 if (mysql_query(mysql, "INSERT INTO temp_sens (   \
			 temperature,   \
			 humidity   \
			) VALUES (   \
			 19.6,   \
			 '61.3'   \
			) \
			"))
		 { 
			  cerr << mysql_error(mysql);
			  return 1;
		 }
	 }
	 else {
		 cerr << "No connection to database";
		 return 1;
	 }
	 
	 return 0;
}
