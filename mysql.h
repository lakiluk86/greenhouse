
#include <stdio.h>
#include <string>
#include <stdlib.h>
#include <mysql/mysql.h>
#include <iostream>

using namespace std;

class MysqlConn {
		string database, username, password;
		MYSQL *mysql;
	public:
		MysqlConn(string database, string username, string password);
		~MysqlConn();
		int connect();
		int query(string sql);
};
