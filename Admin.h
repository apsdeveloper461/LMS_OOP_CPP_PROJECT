#pragma once
#include "Person.h"
#include"Department.h"
class Admin : public Person
{

public:
	Admin(int admin_id, string Name, string Email, string PhoneNo);
	void add_Student() const;
	void Update_Student() const;
	 void display_Students() const;
	 void add_department() const;
	 void update_department() const;
	 void display_department() const;
	 void add_faculty() const;
	 void update_faculty() const;
	 void display_faculty() const;
	 void add_course() const;
	 void update_course() const;
	 void display_course() const;
	 void course_allocate() const;
	 void update_allocate() const;
	 void display_allocate() const;
	 void add_event() const;

	 void update_event() const;
	 void add_club() const;
	 void update_club() const;
	 
	 void add_library_resource() const;
	 void update_library_resource() const;
	 void change_availabilty_of_library_resource() const;
	 void display_feedback() const;
	 ~Admin();


};
