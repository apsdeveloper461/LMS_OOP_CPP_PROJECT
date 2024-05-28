#pragma once

#include"Person.h"
#include"Course.h"

class Faculty :public Person{
private :
	vector <Course*> teach_course;
	void read_data();
	
public:
	Faculty();
	Faculty(int faculty_id, string Name, string Email, string PhoneNo);
	void print() const;
	void display_AllocaionCourse() const;
	void display_assignment() const;

	int get_course_id_from_Allocation() const;
	int get_student_id_from_enrollment(int& cour_id) const;

	void add_assignment() const;
	void update_assignment() const;
	void add_attendance() const;
	void update_attendance() const;
	void display_attendance() const;
	void add_grade() const;
	void update_grade() const;
	void display_grade() const;
	void add_project() const;
	void add_student_to_project() const;
	void display_only_project(int& project_id) const;
	void display_project_details() const;
};



