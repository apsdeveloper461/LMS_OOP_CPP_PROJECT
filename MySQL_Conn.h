#pragma once
#include"mysql.h"
#include<iostream>
using namespace std;

class MySQL_Conn
{
public:
	MySQL_Conn();
	~MySQL_Conn();
private:
    const char* SERVER = "localhost";
    const char* USER = "root";
    const char* PASSWORD = "aps123";
    const char* DB = "LMS";
public:
    MYSQL* conn;
};

inline MySQL_Conn::MySQL_Conn()
{
    conn = mysql_init(NULL);
    if (!mysql_real_connect(conn, SERVER, USER, PASSWORD, DB, 3306, NULL, 0)) {
        cout << "\nError connecting to MySQL: " << mysql_error(conn) << endl;
        exit(0);
    }
}

inline MySQL_Conn::~MySQL_Conn()
{
    // Close the MySQL connection
    mysql_close(conn);
}