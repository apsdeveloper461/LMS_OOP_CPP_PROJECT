#pragma once
#include"StudentCourseInfo.h"
#include"Student.h"
#include"Course.h"

class Enrollement:public StudentCourseInfo
{
public:
	Enrollement();
	Enrollement(int enrollment_id, int course_id, int std_id, string enrol_date);
	void set_date(string d);
	string get_date() const;
	void print_data() const;
private:
	string enroll_date;
	Student* std;
	Course* Cour;
	void read_data();
};

inline Enrollement::Enrollement():StudentCourseInfo()
{
	enroll_date = "";
	read_data();
}

inline Enrollement::Enrollement(int enrollment_id, int course_id, int std_id, string enrol_date) : StudentCourseInfo(enrollment_id, course_id,std_id), enroll_date(enrol_date) {
	read_data();
}

inline void Enrollement::set_date(string d)
{
	enroll_date = d;
}
inline string Enrollement::get_date() const
{
	return enroll_date;
}

inline void Enrollement::print_data() const
{
	cout << endl << "==> Enrollement Id :: " << get_id()
		<< endl << "==> Course_id :: " << get_course_id()
		<< endl << "==> Student Id :; " << get_student_id()
		<< endl << "==> Enrollement Data :: " << enroll_date
		<< endl << "\t <======= Student Info which enroll with this enrollment_id =====>\n";
	std->print_data();
	cout << "\t <========= Course Info in student enroll =======>";
	Cour->print_data();
}

inline void Enrollement::read_data()
{
	string Query = "SELECT S.student_id,S.name,S.email,S.phone_no,S.department_id,S.semester,C.course_id,C.name,C.credits,C.semester FROM Student S,Course C,Enrollment E WHERE S.student_id=E.student_id AND C.course_id=E.course_id AND E.enrollment_id=" + to_string(get_id()) + ";";
	if (mysql_query(SQL.conn, Query.c_str())) {
		cout << "Error executing query: " << mysql_error(SQL.conn) << endl;
		exit(0);
	}
	MYSQL_RES* RES = mysql_store_result(SQL.conn);
	MYSQL_ROW ROW = mysql_fetch_row(RES);
	std->set_id(stoi(ROW[0]));
	std->set_name_or_title(ROW[1]);
	std->set_email(ROW[2]);
	std->set_phone_no(ROW[3]);
	std->set_department_id(stoi(ROW[4]));
	std->set_semester(stoi(ROW[5]));
	Cour->set_id(stoi(ROW[6]));
	Cour->set_name_or_title(ROW[7]);
	Cour->set_credits(ROW[8]);
	Cour->set_semester(stoi(ROW[9]));
	mysql_free_result(RES);
}

