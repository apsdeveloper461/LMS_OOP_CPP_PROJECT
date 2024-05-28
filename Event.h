#pragma once
// Class Event
#include"Add_Des.h"

class Event:public Add_Des
{
public:
	Event();
	Event(int event_id, string title, string desc,string Date,string vnue);
	void set_date(string Date);
	void set_venue(string vnue);
	string get_date() const;
	string get_venue() const;
	void print_data() const;
	~Event();

private:
	string date;
	string venue;

};

inline Event::Event():Add_Des()
{
	date = "";
	venue = "";
}

inline Event::Event(int event_id, string title, string desc, string Date, string vnue):Add_Des(event_id, title, desc),date(Date),venue(vnue)
{
}
inline void Event::set_date(string Date)
{
	this->date = Date;
}
inline void Event::set_venue(string vnue)
{
	this->venue = vnue;
}
inline string Event::get_date() const
{
	return this->date;
}
inline string Event::get_venue() const
{
	return this->venue;
}
inline void Event::print_data() const
{
	cout << endl << "==> Event_Id ::  " << get_id()
		<< endl << "==> Title ::  " << get_name_or_title()
		<< endl << "==> Descrption ::  " << get_description()
		<< endl << "==> Date of Event ::  " << date
		<< endl << "==> Venue ::  " << venue << endl;
}

inline Event::~Event()
{
	cout << endl << "Event with id " << get_id() << " is remove from memeory ";
}