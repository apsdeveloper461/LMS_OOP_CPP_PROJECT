
#pragma once

#include "Std_db.h"
#include "Course.h"
#include"Add_Des.h"
#include<iomanip>
#include<string>
#include<conio.h>

class Person:public Std_db
{
public:
	Person();
	Person(int ID,string Name,string Email,string PhoneNo);
	void set_email(string Email);
	void set_phone_no(string phoneNo);
	string get_email() const;
	string get_phone_no() const;
	virtual void print_data() const;

	void display_club() const;
	void display_library_resource() const;
	void display_event()const;
private:
	string email;
	string phone_no;
};

inline Person::Person():Std_db(),email(""),phone_no("")
{
}

inline Person::Person(int ID, string Name, string Email, string PhoneNo) :Std_db(ID, Name), email(Email), phone_no(PhoneNo)
{
}
inline void Person::set_email(string Email)
{
	this->email = Email;
}
inline void Person::set_phone_no(string phoneNo)
{
	this->phone_no = phoneNo;
}
inline string Person::get_email() const
{
	return this->email;
}
inline string Person::get_phone_no() const
{
	return this->phone_no;
}

inline void Person::print_data() const
{
	cout << endl << "==> Id ::  " << get_id()
		<< endl << "==> Name ::  " << get_name_or_title()
		<< endl << "==> Email ::  " << email
		<< endl << "==> Phone Number ::  " << phone_no << endl;
}
inline void Person::display_club() const
{
	if (mysql_query(SQL.conn, "SELECT * from Club;")) {
		cout << "\nError executing query " << mysql_error(SQL.conn);
		exit(0);
	}
	MYSQL_RES* RES = mysql_store_result(SQL.conn);
	MYSQL_ROW ROW;
	if (mysql_num_rows(RES)) {
		cout << "\n+---------+----------------------+------------------------------------------------------------------------------------+" << endl;
		cout << "| Club ID |        Name          |               Description                                                          |" << endl;
		cout << "+---------+----------------------+------------------------------------------------------------------------------------+" << endl;
		while (ROW = mysql_fetch_row(RES)) {
			cout << "| " << setw(7) << ROW[0] << " | " << setw(20) << ROW[1] << " | " << setw(82) << ROW[2] << " |" << endl;
		}
		cout << "+---------+----------------------+------------------------------------------------------------------------------------+" << endl;
		cout << endl;
		mysql_free_result(RES);
	}else{
		cout << "\n\t <--------------- no record Available ----------------------->\n";
	}

}
inline void Person::display_library_resource() const
{
	if (mysql_query(SQL.conn, "SELECT * from LibraryResource;")) {
		cout << "\nError executing query " << mysql_error(SQL.conn);
		exit(0);
	}
	MYSQL_RES* RES = mysql_store_result(SQL.conn); 
    MYSQL_ROW ROW;
	if (mysql_num_rows(RES)) {
		cout << "\n+-------------+------------------------------------------+------------------------------------------+--------------+" << endl;
		cout << "| resource_id | title                                    | author                                   | availability |" << endl;
		cout << "+-------------+------------------------------------------+------------------------------------------+--------------+" << endl;

		while (ROW = mysql_fetch_row(RES)) {
			cout << "| " << setw(11) << ROW[0] << " | " << setw(40) << ROW[1] << " | " << setw(40) << ROW[2] << " | " << setw(12) << ROW[3] << " |" << endl;
		}
		cout << "+-------------+------------------------------------------+------------------------------------------+--------------+" << endl;

		mysql_free_result(RES);
	}else{
		cout << "\n\t <--------------- no record Available ----------------------->\n";
	}
}
inline void Person::display_event() const
{
	if (mysql_query(SQL.conn, "SELECT * from Event;")) {
		cout << "Error executing query: " << mysql_error(SQL.conn) << endl;
		exit(0);
	}
	MYSQL_RES* RES = mysql_store_result(SQL.conn);
	MYSQL_ROW ROW;
	if (mysql_num_rows(RES)) {
		cout << "\n+---------+--------------------------------+------------------------------------------------------+--------------+---------------------------+" << endl;
		cout << "| event_id| title                          | description                                          |  event_date  | venue                     |" << endl;
		cout << "+---------+--------------------------------+------------------------------------------------------+--------------+---------------------------+" << endl;
		while (ROW = mysql_fetch_row(RES)) {
			cout << "| " << setw(7) << ROW[0] << " | " << setw(30) << ROW[1] << " | " << setw(52) << ROW[2] << " | " << setw(12) << ROW[3] << " | " << setw(25) << ROW[4] << " |" << endl;
		}
		cout << "+---------+--------------------------------+------------------------------------------------------+--------------+---------------------------+" << endl;
		mysql_free_result(RES);
	}else{
		cout << "\n\t <--------------- no record Available ----------------------->\n";
	}
}




