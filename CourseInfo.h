#pragma once


#include<iostream>
#include<string>
#include"MySQL_Conn.h"
using namespace std;
class CourseInfo
{
public:
	CourseInfo();
	CourseInfo(int ID, int corse_id);
	void set_id(int ID);
	void set_course_id(int corse_id);
	int get_id() const;
	int get_course_id() const;
	~CourseInfo();

private:
	int id;
	int course_id;

protected:
	MySQL_Conn SQL;

};

inline CourseInfo::CourseInfo() :id(0), course_id(0)
{
}

inline CourseInfo::CourseInfo(int ID, int corse_id) :id(ID), course_id(corse_id)
{
}

inline void CourseInfo::set_id(int ID)
{
	this->id = ID;
}

inline void CourseInfo::set_course_id(int corse_id)
{
	this->course_id = corse_id;
}

inline int CourseInfo::get_id() const
{
	return this->id;
}

inline int CourseInfo::get_course_id() const
{
	return this->course_id;
}

inline CourseInfo::~CourseInfo()
{
	cout << endl << "Id :" << id << " Student id : " << course_id;
}