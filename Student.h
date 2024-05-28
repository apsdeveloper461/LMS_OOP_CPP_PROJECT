#pragma once
#include"Club.h"
#include"Course.h"
#include"Person.h"

class Student :public Person
{
private:
	int department_id;
	int semester;
	vector <Course*> enroll_courses;
	vector <Club*> join_clubs;
	void read_data() ;
public:
	Student();
	Student(int Student_id, string Name, string Email, string PhoneNo,int dept_id, int semsr);

	void set_department_id(int dept_id);
	void set_semester(int semester);
	int get_department_id() const;
	int get_semester() const;
	void feedback() const;
	void display_joined_club() const;
	void enrollment_in_course() ;
	void enrolled_course() const;
	void join_club() ;
	void display_attendence() const;
	void display_grade() const;
	void submit_assignment()const;
	void display_assign_project() const;
	void print_data() const;
	void print() const;
	~Student();
};
