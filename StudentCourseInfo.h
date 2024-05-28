#pragma once

#include "CourseInfo.h"

class StudentCourseInfo:public CourseInfo
{
public:
	StudentCourseInfo();
	void set_student_id(int std_id);
	int get_student_id() const;
	StudentCourseInfo(int id, int course_id, int std_id);
	

private:
	int student_id;

};

inline StudentCourseInfo::StudentCourseInfo():CourseInfo()
{
	student_id = 0;
}

inline void StudentCourseInfo::set_student_id(int std_id)
{
	student_id = std_id;
}

inline int StudentCourseInfo::get_student_id() const
{
	return student_id;
}

inline StudentCourseInfo::StudentCourseInfo(int id, int course_id, int std_id):CourseInfo(id,course_id),student_id(std_id)
{
}
