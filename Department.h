#pragma once

#include "Std_db.h"

class Department:public Std_db
{
public:
	Department();
	Department(int Dept_id,string name,string head_f_dept);
	void set_head_of_dept(string head_f_dept);
	string get_head_of_dept() const;
	void print_data() const;
	~Department();

private:
	string head_of_department;

};

inline Department::Department():Std_db()
{
	head_of_department = "";
}

inline Department::Department(int Dept_id, string name, string head_f_dept):Std_db(Dept_id,name),head_of_department(head_f_dept)
{
}

inline void Department::set_head_of_dept(string head_f_dept)
{
	this->head_of_department = head_f_dept;
}

inline string Department::get_head_of_dept() const
{
	return this->head_of_department;
}

inline void Department::print_data() const
{
	cout << endl << "==> Department Id ::  " << get_id()
		<< endl << "==> Name ::  " << get_name_or_title()
		<< endl << "==> Head of Department ::  " << head_of_department << endl;

}

inline Department::~Department()
{
	cout << endl << "Department with id " << get_id() << " is remove from memeory ";
}




