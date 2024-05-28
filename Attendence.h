#pragma once
#include "StudentCourseInfo.h"

class Attendence:public StudentCourseInfo
{
public:
	Attendence();
	Attendence(int attendence_id, int std_id, int course_id, int smes, float attendence_per);
	void set_semester(int semester);
	void set_attendence_status(int att_status);
	int get_semester() const;
	int get_attendece_status() const;
	~Attendence();

private:
	float attendece_percentage;	
	int semester;
};

inline Attendence::Attendence() :StudentCourseInfo() {
	attendece_percentage = 0;
	semester = 0;
}
inline Attendence::Attendence(int attendence_id, int std_id, int course_id,int smes, float attendence_per): StudentCourseInfo(attendence_id,course_id,std_id), attendece_percentage(attendence_per),semester(smes)
{
}



inline void Attendence::set_semester(int semester)
{
	this->semester = semester;
}

inline void Attendence::set_attendence_status(int att_status)
{
	attendece_percentage = att_status;
}


inline int Attendence::get_semester() const
{
	return semester;
}

inline int Attendence::get_attendece_status() const
{
	return attendece_percentage;	
}

inline Attendence::~Attendence()
{
	cout << endl << "Attendence id " << get_id() << " Course Id " << get_course_id();
}
