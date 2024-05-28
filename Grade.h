#pragma once
#include "StudentCourseInfo.h"

class Grade:public  StudentCourseInfo
{
public:
	Grade();
	Grade(int grade_id, int course_id,int std_id,string grde);
	void set_grade(string grde);
	string get_grade() const;
private:
	string grade;
};

inline Grade::Grade():StudentCourseInfo()
{
	grade = "";
}

inline Grade::Grade(int grade_id, int course_id, int std_id, string grde):StudentCourseInfo(grade_id,course_id,std_id)
{
}

inline void Grade::set_grade(string grde)
{
	grade = grde;
}
inline string Grade::get_grade() const
{
	return grade;
}






