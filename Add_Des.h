#pragma once // Club , Event & Research classes Here....

#include "Std_db.h"


class Add_Des:public Std_db
{
public:
	Add_Des();
	Add_Des(int id, string title, string desc);
	void set_descrption(string desc);
	string get_description() const;
	void print_data() const;

private:
	string description;

};

inline Add_Des::Add_Des():Std_db()
{
	description = "";
}

inline Add_Des::Add_Des(int id,string title,string desc):Std_db(id,title),description(desc)
{
}

inline void Add_Des::set_descrption(string desc)
{
	this->description = desc;
}

inline string Add_Des::get_description() const
{
	return this->description;
}
inline void Add_Des::print_data() const
{
	cout << endl << "==> Id ::  " << get_id()
		<< endl << "==> Title/Name ::  " << get_name_or_title()
		<< endl << "==> Descrption ::  " << description << endl;
}


