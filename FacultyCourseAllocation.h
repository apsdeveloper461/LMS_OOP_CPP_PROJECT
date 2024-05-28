#pragma once
#include"Faculty.h"
#include"Course.h"
#include"CourseInfo.h"

class FacultyCourseAllocation:public CourseInfo
{
public:
	FacultyCourseAllocation();
	FacultyCourseAllocation(int allocation_id,int faculty_id,int course_id,int smester);
	void set_faculty_id(int faclty_id);
	void set_smester(int smster);
	int get_faculty_id() const;
	int get_smester() const;
	void print_data() const;

	~FacultyCourseAllocation();

private:
	int faculty_id;
	int smester;
	Course* Cour;
	Faculty* fac;
	void read_data();
};

inline FacultyCourseAllocation::FacultyCourseAllocation():CourseInfo()
{
	faculty_id = 0;
	smester = 0;
	read_data();
}

inline FacultyCourseAllocation::FacultyCourseAllocation(int allocation_id, int faculty_id, int course_id, int smester):CourseInfo(allocation_id,course_id),faculty_id(faculty_id),smester(smester)
{
	read_data();
}

inline void FacultyCourseAllocation::set_faculty_id(int faclty_id)
{
	this->faculty_id = faclty_id;
}

inline void FacultyCourseAllocation::set_smester(int smster)
{
	this->smester = smster;
}

inline int FacultyCourseAllocation::get_faculty_id() const
{
	return this->faculty_id;
}

inline int FacultyCourseAllocation::get_smester() const
{
	return this->smester;
}

inline void FacultyCourseAllocation::print_data() const
{
	 cout << endl << "==> Allocation Id ::  " << get_id()
		 << endl << "==> Course Id ::  " << get_course_id()
		 << endl << "==> Faculty Id ::  " << faculty_id
		 << endl << "==> Smester ::  " << smester << endl;
	 cout << "\n\t<============ Faculty Info ====================>\n";
	 fac->print_data();
	 cout << "\n\t<============ Course Info ====================>\n";
	 Cour->print_data();
}

inline FacultyCourseAllocation::~FacultyCourseAllocation()
{
	cout << endl << "Allocation id " << get_id() << " Course Id " << get_course_id();
}

inline void FacultyCourseAllocation::read_data()
{
	string Query = "SELECT F.faculty_id,F.name,F.email,F.phone_no,C.course_id,C.name,C.credits,C.semester FROM Faculty F,Course C,Enrollment E WHERE S.student_id=E.student_id AND C.course_id=E.course_id AND E.enrollment_id=" + to_string(get_id()) + ";";
	if (mysql_query(SQL.conn, Query.c_str())) {
		cout << "Error executing query: " << mysql_error(SQL.conn) << endl;
		exit(0);
	}
	MYSQL_RES* RES = mysql_store_result(SQL.conn);
	MYSQL_ROW ROW = mysql_fetch_row(RES);
	fac->set_id(stoi(ROW[0]));
	fac->set_name_or_title(ROW[1]);
	fac->set_email(ROW[2]);
	fac->set_phone_no(ROW[3]);
	Cour->set_id(stoi(ROW[4]));
	Cour->set_name_or_title(ROW[5]);
	Cour->set_credits(ROW[6]);
	Cour->set_semester(stoi(ROW[7]));
	mysql_free_result(RES);
}
