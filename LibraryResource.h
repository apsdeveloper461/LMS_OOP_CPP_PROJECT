#pragma once

#include"Std_db.h"

class LibraryResource:public Std_db
{
public:
	LibraryResource();
	LibraryResource(int resource_id, string name, string author, bool avaailabilty);
	void set_author(string auth);
	void set_availability(bool ava);
	string get_author() const;
	bool get_availability() const;
	~LibraryResource();

private:
	string author;
	bool availabilty;
};



inline LibraryResource::LibraryResource():Std_db()
{
	author = "";
	availabilty = true;
}

inline LibraryResource::LibraryResource(int resource_id, string name, string author, bool avaailabilty):Std_db(resource_id,name),author(author),availabilty(avaailabilty)
{
}

inline void LibraryResource::set_author(string auth)
{
	author = auth;
}

inline void LibraryResource::set_availability(bool ava)
{
	availabilty = ava;
}

inline string LibraryResource::get_author() const
{
	return author;
}

inline bool LibraryResource::get_availability() const
{
	return availabilty;
}

inline LibraryResource::~LibraryResource()
{
	cout << "LibraryResource destructor called" << endl;
}


