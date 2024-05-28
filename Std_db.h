#pragma once
#include<vector>
#include<string>
#include<iostream>
#include"MySQL_Conn.h"
using namespace std;
class Std_db
{
protected:
	MySQL_Conn SQL;
public:
	Std_db();
	Std_db(int ID,string title);
	inline void set_id(int ID);
	inline void set_name_or_title(string title);
	inline int get_id() const;
	inline string get_name_or_title() const;
	virtual void print_data() const;
	virtual ~Std_db();
private:
	int id;
	string name;

};

inline Std_db::Std_db():id(0),name(""){}
inline Std_db::Std_db(int ID, string title) :id(ID), name(title)
{
}

inline void Std_db::set_id(int ID)
{
	this->id = ID;
}

inline void Std_db::set_name_or_title(string title)
{
	this->name = title;
}

inline int Std_db::get_id() const
{
	return this->id;
}
inline string Std_db::get_name_or_title() const
{
	return this->name;
}
inline void Std_db::print_data() const
{
	cout << endl << "==> Student_id ::  " << id
		<< endl << "==> Name of Student ::  " << name;
}


inline Std_db:: ~Std_db() {
	cout << "Delete object of id is :: " << id;
}