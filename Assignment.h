#pragma once
#include "CourseInfo.h"

class Assignment:public CourseInfo
{
public:
	Assignment();
	Assignment(int assignment_id,int course_id,string date,string description);
	void set_due_date(string date);
	void set_description(string des);
	string get_due_date() const;
	string get_description() const;
	void print_data() const;
	~Assignment();
private:
	string due_date;
	string description;
};

inline Assignment::Assignment():CourseInfo()
{
	due_date = "";
	description = "";
}

inline Assignment::Assignment(int assignment_id, int course_id, string date, string description):CourseInfo(assignment_id,course_id),due_date(date),description(description)
{
}

 inline void Assignment::set_due_date(string date)
 {
	 this->due_date = date;
 }

 inline void Assignment::set_description(string des)
 {
	 this->description = des;
 }

 inline string Assignment::get_due_date() const
 {
	 return this->due_date;
 }

 inline string Assignment::get_description() const
 {
	 return this->description;
 }

 inline void Assignment::print_data() const
 {
	 cout << endl << "==> Assignment Id ::  " << get_id()
		 << endl << "==> Course Id ::  " << get_course_id()
		 << endl << "==> Due Date of Assignment ::  " << due_date
		 << endl << "==> Description ::  " << description << endl;
 }

inline Assignment::~Assignment()
{
	//cout<< endl << "Assignment id " << get_id() << " Course Id " << get_course_id();
}


