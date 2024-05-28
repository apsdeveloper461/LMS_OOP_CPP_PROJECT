#pragma once
#include"Assignment.h"

#include "Std_db.h"

class Course:public Std_db
{
public:
	Course();
	Course(int id, string name, string crdts, int sem);
	void set_credits(string crdts);
	void set_semester(int sem);
	int get_semester();	
	string get_credits() const;
	void print_data() const;
	void print() const;
	~Course();
	void read_data();

private:
	string credits;
	int semester;
	vector <Assignment> course_Assignment;

};


inline Course::Course():Std_db()
{
	credits = "";
	semester = 0;
}

inline Course::Course(int id, string name, string crdts, int sem) :Std_db(id, name), credits(crdts), semester(sem) {
	read_data();
}
inline void Course::set_credits(string crdts)
{
	this->credits = crdts;

}

inline void Course::set_semester(int sem)
{
	this->semester = sem;
}

inline int Course::get_semester()
{
	return semester;
}

inline string Course::get_credits() const
{
	return this->credits;
}

inline void Course::print_data() const
{
	cout << endl << "==> Course_Id ::  " << get_id()
		<< endl << "==> Name ::  " << get_name_or_title()
		<< endl << "==> Credits of Course ::  " << credits
		<< endl << "==> Semsester :: " << semester << endl;
}

inline void Course::print() const
{
	cout << endl << "==> Course_Id ::  " << get_id()
		<< endl << "==> Name ::  " << get_name_or_title()
		<< endl << "==> Credits of Course ::  " << credits;
	if (course_Assignment.size()) {
		cout << "\n\t<============ Assignment of this Course =============================>\n";
		for (int i = 0; i < course_Assignment.size(); i++)
		{
			course_Assignment[i].print_data();
		}
	}
}

inline Course::~Course()
{
	cout << "Object of Course id " << get_id() <<"is removed from memory";
}

inline void Course::read_data()
{
	string Query = "SELECT * FROM Assignment WHERE course_id=" + to_string(get_id()) + ";";
	if (mysql_query(SQL.conn, Query.c_str())) {
		cout << "Error executing query: " << mysql_error(SQL.conn) << endl;
		exit(0);
	}
	MYSQL_RES* RES = mysql_store_result(SQL.conn);
	MYSQL_ROW ROW;
	while (ROW = mysql_fetch_row(RES)) {
		course_Assignment.push_back(Assignment(stoi(ROW[0]),stoi(ROW[1]), ROW[2],ROW[3]));
	}
	mysql_free_result(RES);
}
