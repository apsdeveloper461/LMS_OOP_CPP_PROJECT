#pragma once

#include<iostream>
#include<vector>
#include<conio.h>
#include<cstdlib>
#include<windows.h>
//#include<mysql.h>
#include<string>
#include<cstring>
#include"Student.h"
#include"Faculty.h"
#include"Admin.h"
#include"MySQL_Conn.h"
//LMS class for accessing all Syster and there is only one function starter menu. IT protect from all Unautherized people.
class LMS
{
private:
	int logInId;
	bool LogInFlag=false;
	MySQL_Conn SQL;
	void LogIn(char& choice);
	char validation_choice(char max);
	void admin_menu(Admin& P);
	void faculty_menu(Faculty& P);
	void student_menu(Student& P);
public:
	void starter_menu();
};

