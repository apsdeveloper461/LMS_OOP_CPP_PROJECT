#include "Admin.h"
#include"Date.h"
#include<iomanip>


Admin::Admin(int admin_id, string Name, string Email, string PhoneNo) :Person(admin_id,Name,Email,PhoneNo) {
	cout << "\nAdmin Constructor\n";
}
//Function to add Student
void Admin::add_Student() const
{
	//Display all student through this function
	display_Students();
	//Data of student get from Mysql
	if(mysql_query(SQL.conn,"SELECT email FROM Student")){
	   cout << "Error executing query: " << mysql_error(SQL.conn) << endl;
	   exit(0);
	}
	MYSQL_RES* RES = mysql_store_result(SQL.conn);
	MYSQL_ROW ROW;
	vector <string> email_s;
	while (ROW = mysql_fetch_row(RES)) {
		email_s.push_back(ROW[0]);
	}
	mysql_free_result(RES);
	//Get data of department for validation
	vector <string> dept_name;
	vector <int> dept_id;
	if (mysql_query(SQL.conn, "SELECT * from department;")) {
		cout << "Error executing query: " << mysql_error(SQL.conn) << endl;
		exit(0);
	}
	RES = mysql_store_result(SQL.conn);
	while (ROW = mysql_fetch_row(RES)) {
		dept_id.push_back(stoi(ROW[0]));
		dept_name.push_back(ROW[1]);
	}
	mysql_free_result(RES);
	bool found = false;
	string Name, Email, phone_no;
		cin.ignore(256,'\n');
		//Now get data from admin and validate same data is not available on mysql
	do {
		cout << "\t --> Enter Email of new Student :: ";

		getline(cin, Email);;
		for (int i = 0; i < email_s.size(); i++) {
			if (Email == email_s[i]) {
				found = true;
				break;
			}
			else {
				found = false;
			}
		}
		if (found) cout << "\n\t--( Student with this Email is also Exist . Plz ! Select another Email )--\n";
	} while (found);
	cout << "\n\t--> Enter Name of new Student :: ";
	getline(cin, Name);
	cout << "\n\t--> Enter phone no of Student :: ";
	getline(cin, phone_no);
	int deptId;
	//Display department data and validate the enter department id is available on mysql department table.
		display_department();
		bool dept_id_exist = false;
		do
		{
			cout << "\n\t --> Enter dept id :: ";
			cin >> deptId;
			for (int i = 0; i < dept_id.size(); i++) {
				if (deptId == dept_id[i]) {
					dept_id_exist = true;
					break;
				}
				else {
					dept_id_exist = false;
				}
			}
			if (!dept_id_exist) cout << "\n    ---- Invalid depaartment id ..............\n";
			else break;
		} while (true);
		//get semester from admin with validation
		int Smester;
		do {
			cout << "\n\t --> Enter Semster No of Student (1--8) :: ";
			cin >> Smester;
			if (Smester >= 1 && Smester <= 8) break;
			else cout << "\n  ------ Invalid Data!\n";
		} while (true);
		//Now store the Data on mysql through query, after passing through all type of validation
	string Query = "INSERT INTO Student(name,email,phone_no,department_id,Semester) values(\'" + Name + "\',\'" + Email + "\',\'" + phone_no + "\'," + to_string(deptId) + "," + to_string(Smester) + "); ";
	if (mysql_query(SQL.conn, Query.c_str())) {
		cout << "Error executing query: " << mysql_error(SQL.conn) << endl;
	}
	else {
	  cout << "\n\t\t  <------------------- INSERT NEW STUDENT SUCCESSFULLY -------------->";
	}

}

void Admin::Update_Student() const
{
	//Display all Student data
	display_Students();
	//get all email and ids of student from mysql for validation
	vector <int> id_s;
	vector <string> email_s;
	if (mysql_query(SQL.conn, "SELECT student_id,email from student;")) {
		cout << "Error executing query: " << mysql_error(SQL.conn) << endl;
		exit(0);
	}
	MYSQL_RES* RES = mysql_store_result(SQL.conn);
	MYSQL_ROW ROW;
	//check if the res from mysql is not zero, then we  able to update data of any student because we have data
	if (mysql_num_rows(RES)) {
		//Now get data from mysql aand store in vector
		while (ROW = mysql_fetch_row(RES)) {
			id_s.push_back(stoi(ROW[0]));
			email_s.push_back(ROW[1]);
		}
		mysql_free_result(RES);
		//Now get data of department for update, it means student study in which department
		vector <string> dept_name;
		vector <int> dept_id;
		if (mysql_query(SQL.conn, "SELECT * from department;")) {
			cout << "Error executing query: " << mysql_error(SQL.conn) << endl;
			exit(0);
		}
		RES = mysql_store_result(SQL.conn);
		while (ROW = mysql_fetch_row(RES)) {
			dept_id.push_back(stoi(ROW[0]));
			dept_name.push_back(ROW[1]);
		}
		mysql_free_result(RES);
		//Now get and validate all data , 
		int id, deptId, Smester;
		bool found = false;
		string Name, Email, phone_no;
		//get student id whci student i want to change data
		do {
			cout << "\t --> Enter Id of Student which you want to Update :: ";
			cin >> id;
			for (int i = 0; i < id_s.size(); i++) {
				if (id == id_s[i]) {
					found = true;
					break;
				}
				else
					found = false;
			}
			if (!found) cout << "\n\t--(Student with this student_id is not Exist.Plz !Select another )--\n";
		} while (!found);
		//changing Email
		char ch;
		//i make query in part according to user want to update 
		string Query = "Update Student SET student_id=" + to_string(id);
		//get confirmation you want to update data after any change
		cout << "\n\t-->Enter 'y' for changing Email (otherwise any one else) -->";
		ch = _getche();
		cin.ignore(256, '\n');
		if (ch == 'y' || ch == 'Y') {
			bool emailFound = false;
			do
			{
				emailFound = false;
				cout << "\n\t --> Enter new Email of Student :: ";
				getline(cin, Email);
				for (int i = 0; i < email_s.size(); i++) {
					if (Email == email_s[i]) {
						if (id == id_s[i]) emailFound = false;
						else emailFound = true;
						break;
					}
				}
				if (emailFound) cout << "\n\t ----( This Email is already Exist select another )------\n";
				else break;
			} while (true);
			Query += ",email= \'" + Email + "\'";
		}
		// Changing Name
		cout << "\n\t-->Enter 'y' for changing Name (otherwise any one else) -->";
		ch = _getche();
		if (ch == 'y' || ch == 'Y') {
			cout << "\n\t --> Enter Name :: ";
			getline(cin, Name);
			//add in query if user change name 
			Query += ",name= \'" + Name + "\'";
		}
		//Changing Phone _no
		cout << "\n\t-->Enter 'y' for changing phone_no (otherwise any one else) -->";
		ch = _getche();
		if (ch == 'y' || ch == 'Y') {
			cout << "\n\t --> Enter phone_no of Student :: ";
			getline(cin, phone_no);
			//also add in qquery
			Query += ",phone_no= \'" + phone_no + "\'";
		}
		//Changing Department
		cout << "\n\t-->Enter 'y' for changing Departmant (otherwise any one else) -->";
		ch = _getche();
		if (ch == 'y' || ch == 'Y') {
			display_department();
			bool dept_id_exist = false;
			do
			{
				cout << "\n\t --> Enter dept id :: ";
				cin >> deptId;
				for (int i = 0; i < dept_id.size(); i++) {
					if (deptId == dept_id[i]) {
						dept_id_exist = true;
						break;
					}
					else {
						dept_id_exist = false;
					}
				}
				if (!dept_id_exist) cout << "\n Invalid depaartment id ..............\n";
				else break;
			} while (true);
			Query += ",department_id= \'" + to_string(deptId) + "\'";
		}
		cout << "\n\t-->Enter 'y' for changing Smester (otherwise any one else) -->";
		ch = _getche();
		//Changing Smester....
		if (ch == 'y' || ch == 'Y') {
			do {
				cout << "\n\t --> Enter Semster No of Student (1--8) :: ";
				cin >> Smester;
				if (Smester >= 1 && Smester <= 8) break;
				else cout << "\n  ---- Invalid Data!\n";
			} while (true);
			Query += ",Semester= \'" + to_string(Smester) + "\'";
		}
		//also add query
		Query += " where student_id=" + to_string(id) + " ;";
		//All query which i make in function run of mysql
		if (mysql_query(SQL.conn, Query.c_str()))
			cout << "Error executing query: " << mysql_error(SQL.conn) << endl;
		else
			cout << "\n\t\t <------------- UPDATE STUDENT SUCCESSFULLY ---------------->\n";
	}
	else {
		cout << "\n\t <--------------- no record Available ----------------------->\n";
	}
}

void Admin::display_Students() const
{
	//Get all data of student from mysql
	if (mysql_query(SQL.conn, "SELECT s.student_id,s.Email,s.Name,s.phone_no,d.Name,s.Semester,d.department_id FROM Student s,Department d  where s.department_id=d.department_id;")) {
		cout << "Error executing query: " << mysql_error(SQL.conn) << endl;
     	exit(0);
	}
	MYSQL_RES* RES = mysql_store_result(SQL.conn);
	MYSQL_ROW ROW;
	//check data is get from mysql means data of student available or not
	if (mysql_num_rows(RES)) {

		cout << "\n+==========================================================================================================================+"
			<< "\n| Student _id  |     Email ID               |     Name             |    phone_no     |  Department_Name         | Semester |"
			<< "\n+--------------+----------------------------+----------------------+-----------------+--------------------------+----------+";
		while (ROW = mysql_fetch_row(RES)) {
			cout << left << "\n|  " << setw(12) << ROW[0] << "|   " << setw(24) << ROW[1] << " | " << setw(20) << ROW[2] << " | " << setw(15) << ROW[3] << " | " << setw(24) << ROW[4] << setw(10) << left << " |   " << ROW[5] << " |";
		}
		mysql_free_result(RES);
		cout << "\n+==========================================================================================================================+\n\n";
	}
	else {
		cout << "\n\t <--------------- no record Available ----------------------->\n";
	}
}

void Admin::add_department() const
{
	//Display deparment 
	display_department();
	//get data from mysql whcih i donot set same whcih is department name
	if (mysql_query(SQL.conn, "SELECT Name FROM department")) {
		cout << "Error executing query: " << mysql_error(SQL.conn) << endl;
		exit(0);
	}
	MYSQL_RES* RES = mysql_store_result(SQL.conn);
	MYSQL_ROW ROW;
	vector <string> name_s;
	while (ROW = mysql_fetch_row(RES)) {
		name_s.push_back(ROW[0]);
	}
	mysql_free_result(RES);
	bool found = false;
	string Name,hd_of_dept;
	cin.ignore(256, '\n');
	do {
		cout << "\t --> Enter the Name of new Department :: ";
		getline(cin, Name);
		for (int i = 0; i < name_s.size(); i++) {
			if (Name == name_s[i]) {
				found = true;
				break;
			}
			else {
				found = false;
			}
		}
		if (found) cout << "\n\t--( Department with Name is also Exist . Plz ! Select another Name )--\n";
	} while (found);
	cout << "\t --> Enter Name of Department  head :: ";
	getline(cin, hd_of_dept);
	string Query = "INSERT INTO Department(Name,head_of_department) values(\'" + Name + "\',\'" + hd_of_dept + "\'); ";
	if (mysql_query(SQL.conn, Query.c_str())) {
		cout << "Error executing query: " << mysql_error(SQL.conn) << endl;
	}
	else {
		cout << "\n\t\t  <------------------- INSERT NEW DEPARTMENT SUCCESSFULLY -------------->";
	}
}

void Admin::update_department() const
{
	//Display department
	display_department();
	//Now get all depaartment id from department
	if (mysql_query(SQL.conn, "SELECT department_id,Name FROM department;")) {
		cout << "Error executing query: " << mysql_error(SQL.conn) << endl;
		exit(0);
	}
	MYSQL_RES* RES = mysql_store_result(SQL.conn);
	MYSQL_ROW ROW;
	//check data of department is available or not
	if (mysql_num_rows(RES)) {
		vector <int> id_s;
		vector <string> name_s;
		while (ROW = mysql_fetch_row(RES)) {
			id_s.push_back(stoi(ROW[0]));
			name_s.push_back(ROW[1]);
		}
		mysql_free_result(RES);
		int id;
		bool found = false;
		string Name, hd_of_dept;
		//now get the department id where i update data 
		do {
			cout << "\t --> Enter Id of Department which you want to Update :: ";
			cin >> id;
			for (int i = 0; i < id_s.size(); i++) {
				if (id == id_s[i]) {
					found = true;
					break;
				}
				else
					found = false;
			}
			if (!found) cout << "\n\t--(Department with this department_id is not Exist.Plz !Select another )--\n";
		} while (!found);
		//changing Name
		char ch;
		//Making query in part according to changing in data
		string Query = "Update department SET department_id=" + to_string(id);
		cout << "\n\t-->Enter 'y' for changing Name (otherwise any one else) -->";
		ch = _getche();
		cin.ignore(256, '\n');
		if (ch == 'y' || ch == 'Y') {
			bool nameFound;
			do
			{
				nameFound = false;
				cout << "\n\t --> Enter new Email Faculty :: ";
				getline(cin, Name);
				for (int i = 0; i < name_s.size(); i++) {
					if (Name == name_s[i]) {
						cout << endl << name_s[i] << endl;
						if (id == id_s[i]) nameFound = false;
						else nameFound = true;
						break;
					}
					else nameFound = false;
				}
				if (nameFound) cout << "\n\t ----( This Name is already Exist select another )------\n";
				else break;
			} while (true);
			Query += ",name= \'" + Name + "\'";
		}
		// Changing Name of head
		cout << "\n\t-->Enter 'y' for changing head_of_dept (otherwise any one else) -->";
		ch = _getche();
		if (ch == 'y' || ch == 'Y') {
			cout << "\n\t --> Enter Name of Department head :: ";
			getline(cin, hd_of_dept);
			Query += ",head_of_department= \'" + hd_of_dept + "\'";
		}
		Query += " where department_id=" + to_string(id) + " ;";
		if (mysql_query(SQL.conn, Query.c_str()))
			cout << "Error executing query: " << mysql_error(SQL.conn) << endl;
		else
			cout << "\n\t\t <------------- UPDATE FACULTY SUCCESSFULLY ---------------->\n";
	}
	else {

		cout << "\n\t <--------------- no record Available ----------------------->\n";
	}
}

void Admin::display_department() const
{
	//Get all data from mysql
	if (mysql_query(SQL.conn, "SELECT s.student_id,s.Email,s.Name,s.phone_no,d.Name,s.Semester,d.department_id FROM Student s,Department d  where s.department_id=d.department_id;")) {
		cout << "Error executing query: " << mysql_error(SQL.conn) << endl;
		exit(0);
	}
	MYSQL_RES* RES = mysql_store_result(SQL.conn);
	MYSQL_ROW ROW;
	//check data of department is available or not
	if (mysql_num_rows(RES)) {
		//Get and sispaly all data
		if (mysql_query(SQL.conn, "SELECT * from department;")) {
			cout << "Error executing query: " << mysql_error(SQL.conn) << endl;
			exit(0);
		}
		RES = mysql_store_result(SQL.conn);
		cout << "\n\n+----------+---------------------------+----------------------+\n"
			<< "| Dept_id  |   Name                    |   Head_of_department |\n"
			<< "+----------+---------------------------+----------------------+\n";
		while (ROW = mysql_fetch_row(RES)) {
			cout << "|   " << left << setw(5) << ROW[0] << "  | " << setw(26) << ROW[1] << "|  " << setw(20) << ROW[2] << "|\n";
		}
		cout << "+----------+---------------------------+----------------------+\n";
	}
	else {
		cout << "\n\t <--------------- no record Available ----------------------->\n";
	}
}

void Admin::add_faculty() const
{
	//display faculty data
	display_faculty();
	//Get data from mysql
	if (mysql_query(SQL.conn, "SELECT email FROM faculty")) {
		cout << "Error executing query: " << mysql_error(SQL.conn) << endl;
		exit(0);
	}
	MYSQL_RES* RES = mysql_store_result(SQL.conn);
	MYSQL_ROW ROW;
	vector <string> email_s;
	while (ROW = mysql_fetch_row(RES)) {
		email_s.push_back(ROW[0]);
	}
	mysql_free_result(RES);
	bool found = false;
	string Name, Email, phone_no;
	//Get add of faculty which admin want to add faculty(email is not match)
	cin.ignore(256, '\n');
	do {
		cout << "\t --> Enter Email of new faculty Member :: ";
		getline(cin, Email);;
		for (int i = 0; i < email_s.size(); i++) {
			if (Email == email_s[i]) {
				found = true;
				break;
			}
			else {
				found = false;
			}
		}
		if (found) cout << "\n\t--( Faculty with this Email is also Exist . Plz ! Select another Email )--\n";
	} while (found);
	cout << "\n\t--> Enter Name of Faculty :: ";
	getline(cin, Name);
	cout << "\n\t--> Enter phone no  :: ";
	getline(cin, phone_no);
	//Insert data in mysql
	string Query = "INSERT INTO Faculty(Name,Email,phone_no) values(\'" + Name + "\',\'" + Email + "\',\'" + phone_no + "\'); ";
	if (mysql_query(SQL.conn, Query.c_str())) {
		cout << "Error executing query: " << mysql_error(SQL.conn) << endl;
	}
	else {
		cout << "\n\t\t  <------------------- INSERT NEW Facult Member SUCCESSFULLY -------------->";
	}
}

void Admin::update_faculty() const
{
	//display faculty data
	display_faculty();
	//get data from mysql
	if (mysql_query(SQL.conn, "SELECT faculty_id,email FROM Faculty")) {
		cout << "Error executing query: " << mysql_error(SQL.conn) << endl;
		exit(0);
	}
	MYSQL_RES* RES = mysql_store_result(SQL.conn);
	MYSQL_ROW ROW;
	//check data of faculty is available or not
	if (mysql_num_rows(RES)) {
		//Store data
		vector <int> id_s;
		vector <string> email_s;
		while (ROW = mysql_fetch_row(RES)) {
			id_s.push_back(stoi(ROW[0]));
			email_s.push_back(ROW[1]);
		}
		mysql_free_result(RES);
		//Get id where data is update 
		int id;
		bool found = false;
		string Name, Email, phone_no;
		do {
			cout << "\t --> Enter Id of Student which you want to Update :: ";
			cin >> id;
			for (int i = 0; i < id_s.size(); i++) {
				if (id == id_s[i]) {
					found = true;
					break;
				}
				else
					found = false;
			}
			if (!found) cout << "\n\t--(Student with this student_id is not Exist.Plz !Select another )--\n";
		} while (!found);
		//changing Email
		char ch;
		//make query according to admin where data change in part through this function
		string Query = "Update faculty SET faculty_id=" + to_string(id);
		//Updating email
		cout << "\n\t-->Enter 'y' for changing Email (otherwise any one else) -->";
		ch = _getche();
		cin.ignore(256, '\n');
		if (ch == 'y' || ch == 'Y') {
			bool emailFound;
			do
			{
				emailFound = false;
				cout << "\n\t --> Enter new Email Faculty :: ";
				getline(cin, Email);
				for (int i = 0; i < email_s.size(); i++) {
					if (Email == email_s[i]) {
						cout << endl << email_s[i] << endl;
						if (id == id_s[i]) emailFound = false;
						else emailFound = true;
						break;
					}
					else emailFound = false;
				}
				if (emailFound) cout << "\n\t ----( This Email is already Exist select another )------\n";
				else break;
			} while (true);
			Query += ",email= \'" + Email + "\'";
		}
		// Changing Name
		cout << "\n\t-->Enter 'y' for changing Name (otherwise any one else) -->";
		ch = _getche();
		if (ch == 'y' || ch == 'Y') {
			cout << "\n\t --> Enter Name :: ";
			getline(cin, Name);
			Query += ",name= \'" + Name + "\'";
		}
		//Changing Phone _no
		cout << "\n\t-->Enter 'y' for changing phone_no (otherwise any one else) -->";
		ch = _getche();
		if (ch == 'y' || ch == 'Y') {
			cout << "\n\t --> Enter phone_no :: ";
			getline(cin, phone_no);
			Query += ",phone_no= \'" + phone_no + "\'";
		}
		//add to query
		Query += " where faculty_id=" + to_string(id) + " ;";
		//run query
		if (mysql_query(SQL.conn, Query.c_str()))
			cout << "Error executing query: " << mysql_error(SQL.conn) << endl;
		else
			cout << "\n\t\t <------------- UPDATE FACULTY SUCCESSFULLY ---------------->\n";
	}
	else {
		cout << "\n\t <--------------- no record Available ----------------------->\n";
	}
}

void Admin::display_faculty() const
{
	//data get from mysql
	if (mysql_query(SQL.conn, "SELECT * FROM Faculty;")) {
		cout << "Error executing query: " << mysql_error(SQL.conn) << endl;
		exit(0);
	}
	MYSQL_RES* RES = mysql_store_result(SQL.conn);
	MYSQL_ROW ROW;
	//check data of faculty is available or not
	if (mysql_num_rows(RES)) {
		cout << "\n+==========================================================================================+"
			<< "\n| faculty_id   |     Email ID                    |     Name              |    phone_no     |"
			<< "\n+--------------+---------------------------------+-----------------------+-----------------+";
		while (ROW = mysql_fetch_row(RES)) {
			cout << left << "\n|  " << setw(12) << ROW[0] << "|   " << setw(29) << ROW[2] << " | " << setw(21) << ROW[1] << " | " << setw(15) << ROW[3] << " |";
		}
		mysql_free_result(RES);
		cout << "\n+==========================================================================================+\n\n";
	}
	else {
		cout << "\n\t <--------------- no record Available ----------------------->\n";
	}
}

void Admin::add_course() const
{
	//display courses
	display_course();
	//add courses
	int smester,credit;
	bool found = false;
	string Name;
	cin.ignore(256, '\n');
	//get data from user
		cout << "\t --> Enter Name of new Course :: ";
		getline(cin, Name);;
		do
		{
	      cout << "\n\t--> Enter Credits of this Course --( 1--4) --> :: ";
		  cin >> credit;
		  if (credit >= 1 && credit <= 4) break;
		  else cout << "\n\t -- Invalid Credits hour only b\\w 1 to 4\n";
		} while (true);
		do
		{
			cout << "\n\t--> Enter Semester of this Course --( 1--8) --> :: ";
			cin >> smester;
			if (smester >= 1 && smester <= 8) break;
			else cout << "\n\t -- Invalid semester hour only b\\w 1 to 8\n";
		} while (true);
		//added in myql
	string Query = "INSERT INTO Course(Name,credits,Semester) values(\'" + Name + "\',\'" + to_string(credit) + "\',\'" + to_string(smester) + "\'); ";
	if (mysql_query(SQL.conn, Query.c_str())) {
		cout << "Error executing query: " << mysql_error(SQL.conn) << endl;
	}
	else {
		cout << "\n\t\t  <------------------- INSERT NEW COURSE SUCCESSFULLY -------------->";
	}
}

void Admin::update_course() const
{
	//display courses
	display_course();
	if (mysql_query(SQL.conn, "SELECT course_id FROM Course")) {
		cout << "Error executing query: " << mysql_error(SQL.conn) << endl;
		exit(0);
	}
	MYSQL_RES* RES = mysql_store_result(SQL.conn);
	MYSQL_ROW ROW;
	//check data of course is available or not
	if (mysql_num_rows(RES)) {
		vector <int> id_s;
		while (ROW = mysql_fetch_row(RES)) {
			id_s.push_back(stoi(ROW[0]));
		}
		mysql_free_result(RES);

		int id, credit, smester;
		bool found = false;
		string Name;
		// get id of course where update
		do {
			cout << "\t --> Enter Id of Course which you want to Update :: ";
			cin >> id;
			for (int i = 0; i < id_s.size(); i++) {
				if (id == id_s[i]) {
					found = true;
					break;
				}
				else
					found = false;
			}
			if (!found) cout << "\n\t--(Course with this course_id is not Exist.Plz !Select another )--\n";
		} while (!found);
		//changing Email
		char ch;
		//starting to make query according to change
		string Query = "Update Course SET course_id=" + to_string(id);
		cout << "\n\t-->Enter 'y' for changing Name (otherwise any one else) -->";
		ch = _getche();
		cin.ignore(256, '\n');
		if (ch == 'y' || ch == 'Y') {
			cout << "\n\t --> Enter new Name Faculty :: ";
			getline(cin, Name);
			Query += " ,Name= \'" + Name + "\'";
		}
		// Changing Credits
		cout << "\n\t-->Enter 'y' for changing Credit (otherwise any one else) -->";
		ch = _getche();
		if (ch == 'y' || ch == 'Y') {
			do
			{
				cout << "\n\t--> Enter Credits of this Course --( 1--4) --> :: ";
				cin >> credit;
				if (credit >= 1 && credit <= 4) break;
				else cout << "\n\t -- Invalid Credits hour only b\\w 1 to 4\n";
			} while (true);
			Query += ",credits= \'" + to_string(credit) + "\'";
		}
		//Changing Semester
		cout << "\n\t-->Enter 'y' for changing semester of Course i which it teach (otherwise any one else) -->";
		ch = _getche();
		if (ch == 'y' || ch == 'Y') {
			do
			{
				cout << "\n\t--> Enter Semester of this Course --( 1--8) --> :: ";
				cin >> smester;
				if (smester >= 1 && smester <= 8) break;
				else cout << "\n\t -- Invalid semester hour only b\\w 1 to 8\n";
			} while (true);
			Query += ",Semester= \'" + to_string(smester) + "\'";
		}
		Query += " where course_id=" + to_string(id) + " ;";
		//Update with query on mysql
		if (mysql_query(SQL.conn, Query.c_str()))
			cout << "Error executing query: " << mysql_error(SQL.conn) << endl;
		else
			cout << "\n\t\t <------------- UPDATE FACULTY SUCCESSFULLY ---------------->\n";
	}
	else {
		cout << "\n\t <--------------- no record Available ----------------------->\n";
	}
}

void Admin::display_course() const
{
	//Get data of courses from mysql
	if (mysql_query(SQL.conn, "SELECT * FROM Course;")) {
		cout << "Error executing query: " << mysql_error(SQL.conn) << endl;
		exit(0);
	}
	MYSQL_RES* RES = mysql_store_result(SQL.conn);
	MYSQL_ROW ROW;
	//check data of course is available or not
	if (mysql_num_rows(RES)) {
		cout << mysql_num_rows(RES) << endl;

		cout << "\n+============================================================================+"
			<< "\n| Course_id    |     Name                        |   Credits   |   Semester  |"
			<< "\n+--------------+---------------------------------+-------------+-------------+";
		while (ROW = mysql_fetch_row(RES)) {
			cout << left << "\n|  " << setw(12) << ROW[0] << "| " << setw(31) << ROW[1] << " |   " << setw(9) << ROW[2] << " |   " << setw(9) << ROW[3] << " |";
		}
		mysql_free_result(RES);
		cout << "\n+============================================================================+\n\n";
	}else{
		cout << "\n\t <--------------- no record Available ----------------------->\n";
	}
}

void Admin::course_allocate() const
{
	//display faculty
	display_faculty();
	if (mysql_query(SQL.conn, "SELECT faculty_id FROM Faculty")) {
		cout << "Error executing query: " << mysql_error(SQL.conn) << endl;
		exit(0);
	}
	MYSQL_RES* RES = mysql_store_result(SQL.conn);
	MYSQL_ROW ROW;
	//check data of facutly is available or not (if faculty is not available not allocation is done)
	if (mysql_num_rows(RES)) {
		//store data
		vector <int> id_s;
		while (ROW = mysql_fetch_row(RES)) {
			id_s.push_back(stoi(ROW[0]));
		}
		mysql_free_result(RES);
		int fac_id;
		//get facutly id to allocate course
		bool found = false;
		do {
			cout << "\t --> Enter Id of Faculty For Allocation :: ";
			cin >> fac_id;
			for (int i = 0; i < id_s.size(); i++) {
				if (fac_id == id_s[i]) {
					found = true;
					break;
				}
				else
					found = false;
			}
			if (!found) cout << "\n\t--(Faculty with this id is not Exist.Plz !Select another )--\n";
		} while (!found);
		//now get courses from mysql which no any one teach
		if (mysql_query(SQL.conn, "SELECT c.course_id, c.Name AS course_name FROM Course c	LEFT JOIN CourseFacultyAllocation cfa ON c.course_id = cfa.course_id  WHERE cfa.course_id IS NULL;")) {
			cout << "Error executing query: " << mysql_error(SQL.conn) << endl;
			exit(0);
		}
		RES = mysql_store_result(SQL.conn);
		id_s.clear();
		//show courses
		cout << "\n+-----------+-----------------------------------+" << endl;
		cout << "| course_id | course_name                       |" << endl;
		cout << "+-----------+-----------------------------------+" << endl;
		while (ROW = mysql_fetch_row(RES)) {
			cout << "| " << setw(9) << ROW[0] << " | "
				<< setw(33) << ROW[1] << " |" << endl;
			id_s.push_back(stoi(ROW[0]));
		}
		cout << "+-----------+-----------------------------------+" << endl;
		mysql_free_result(RES);
		int cour_id;
		//get course id whcih allocate to 
		found = false;
		do {
			cout << "\t --> Enter Id of Course which you want to Allocate :: ";
			cin >> cour_id;
			for (int i = 0; i < id_s.size(); i++) {
				if (cour_id == id_s[i]) {
					found = true;
					break;
				}
				else
					found = false;
			}
			if (!found) cout << "\n\t--(Course with this course_id is not Exist.Plz !Select another )--\n";
		} while (!found);
		string Query = "INSERT INTO CourseFacultyAllocation (faculty_id, course_id) VALUES ( " + to_string(fac_id) + "," + to_string(cour_id) + ")";
		if (mysql_query(SQL.conn, Query.c_str())) {
			cout << "Error executing query: " << mysql_error(SQL.conn) << endl;
			exit(0);
		}
		else {
			cout << "\n\t\t <------------- COURSE ALLOCATE TO FACULTY SUCCESSFULLY ---------------->\n";
		}
	}else{
		cout << "\n\t <--------------- no record Available ----------------------->\n";
	}
}

void Admin::update_allocate() const
{
	//display allocate
	display_allocate();
	if (mysql_query(SQL.conn, "SELECT enrollment_id FROM CourseFacultyAllocation")) {
		cout << "Error executing query: " << mysql_error(SQL.conn) << endl;
		exit(0);
	}
	MYSQL_RES* RES = mysql_store_result(SQL.conn);
	MYSQL_ROW ROW;
	//check data of allocate is available or not
	if (mysql_num_rows(RES)) {
		vector <int> id_s;
		while (ROW = mysql_fetch_row(RES)) {
			id_s.push_back(stoi(ROW[0]));
		}
		mysql_free_result(RES);
		int enr_id;
		//get allocatiion id which i want to change
		bool found = false;
		do {
			cout << "\t --> Enter Id of Allocation which you want to Update :: ";
			cin >> enr_id;
			for (int i = 0; i < id_s.size(); i++) {
				if (enr_id == id_s[i]) {
					found = true;
					break;
				}
				else
					found = false;
			}
			if (!found) cout << "\n\t--(Allocation with this id is not Exist.Plz !Select another )--\n";
		} while (!found);
		// Get data of allocation which admin want to channge
		string Query = "SELECT * FROM CourseFacultyAllocation WHERE enrollment_id=" + to_string(enr_id) + ";";
		if (mysql_query(SQL.conn, Query.c_str())) {
			cout << "Error executing query: " << mysql_error(SQL.conn) << endl;
			exit(0);
		}
		RES = mysql_store_result(SQL.conn);
		ROW = mysql_fetch_row(RES);
		mysql_free_result(RES);
		char ch;
		// Changing Faculty 
		cout << "\n\t-->Enter 'y' for changing Faculty (otherwise any one else) -->";
		ch = _getche();
		if (ch == 'y' || ch == 'Y') {
			display_faculty();//display and get faculty id fro allocation
			if (mysql_query(SQL.conn, "SELECT faculty_id FROM Faculty")) {
				cout << "Error executing query: " << mysql_error(SQL.conn) << endl;
				exit(0);
			}
			RES = mysql_store_result(SQL.conn);
			id_s.clear();
			while (ROW = mysql_fetch_row(RES)) {
				id_s.push_back(stoi(ROW[0]));
			}
			mysql_free_result(RES);
			int fac_id;
			found = false;
			do {
				cout << "\t --> Enter Id of Faculty For Allocation :: ";
				cin >> fac_id;
				for (int i = 0; i < id_s.size(); i++) {
					if (fac_id == id_s[i]) {
						found = true;
						break;
					}
					else
						found = false;
				}
				if (!found) cout << "\n\t--(Faculty with this id is not Exist.Plz !Select another )--\n";
			} while (!found);
			string Query = "UPDATE CourseFacultyAllocation SET faculty_id=" + to_string(fac_id) + " WHERE enrollment_id=" + to_string(enr_id) + ";";
			if (mysql_query(SQL.conn, Query.c_str())) {
				cout << "Error executing query: " << mysql_error(SQL.conn) << endl;
				exit(0);
			}
			else {
				cout << "\n\t\t <------------- COURSE ALLOCATION UPDATE TO FACULTY SUCCESSFULLY ---------------->\n";
			}
		}
	}
	else {
		cout << "\n\t <--------------- no record Available ----------------------->\n";
	}

}

void Admin::display_allocate() const
{
	//get data of allocation
	if (mysql_query(SQL.conn, "SELECT cfa.enrollment_id,cfa.faculty_id, f.Name AS faculty_name,cfa.course_id,c.Name AS course_name FROM CourseFacultyAllocation cfa JOIN Faculty f ON cfa.faculty_id = f.faculty_id JOIN Course c ON cfa.course_id = c.course_id;")) {
		cout << "Error executing query: " << mysql_error(SQL.conn) << endl;
		exit(0);
	}
	MYSQL_RES* RES = mysql_store_result(SQL.conn);
	MYSQL_ROW ROW;
	//check data of allocation is available or not
	if (mysql_num_rows(RES)) {
		cout << "\n+---------------+------------+------------------------+-----------+---------------------------------+" << endl;
		cout << "| enrollment_id | faculty_id | faculty_name           | course_id | course_name                     |" << endl;
		cout << "+---------------+------------+------------------------+-----------+---------------------------------+" << endl;
		while (ROW = mysql_fetch_row(RES)) {
			cout << "| " << setw(13) << ROW[0] << " | " << setw(10) << ROW[1] << " | " << setw(22) << ROW[2] << " | " << setw(9) << ROW[3] << " | " << setw(31) << ROW[4] << " |" << endl;
		}

		mysql_free_result(RES);
		cout << "+---------------+------------+------------------------+-----------+---------------------------------+" << endl;
	}else{
		cout << "\n\t <--------------- no record Available ----------------------->\n";
	}
}

void Admin::add_event() const
{
	//get all data from admin about event
	string title, desc, venue, d;
	Date date;
	//display event
	display_event();
	cin.ignore(256, '\n');
	cout << "\n\t --> Enter the title of Event :: ";
	getline(cin, title);
	cout << "\n\t --> Enter the description of Event :: ";
	getline(cin, desc);
	cout << "\n\t --> Enter the venue of Event :: ";
	getline(cin, venue);
	cout << "\n\t --> Enter date in form <Year is greater than 2000 and less then 2050>(DDMMYYYY) :: ";
	cin >> d;
	date.set_date(d);
	//insert data on mysql
	string Query = "INSERT INTO Event (title, description, venue, event_date) VALUES ('" + title + "','" + desc + "','" + venue + "','" + date.get_date() + "');";
	if (mysql_query(SQL.conn, Query.c_str())) {
		cout << "\nError in query " << mysql_error(SQL.conn);
		exit(0);
	}
	else {
		cout << "\n\t\t ---------- ADD EVENT SUCCESSFULLY -------------------\n";
	}

}

void Admin::update_event() const
{
	display_event();//dispay event
	if (mysql_query(SQL.conn, "SELECT event_id FROM Event")) {
		cout << "\nError in query " << mysql_error(SQL.conn);
	}
	MYSQL_RES* RES = mysql_store_result(SQL.conn);
	MYSQL_ROW ROW;
	//check data of department is available or not
	if (mysql_num_rows(RES)) {
		vector <int> id_s;
		while (ROW = mysql_fetch_row(RES)) {
			id_s.push_back(stoi(ROW[0]));
		}
		mysql_free_result(RES);
		int event_id;
		string title, des, date, venue, Query;
		Date D;
		bool found = false;
		do {
			cout << "\n\t --> Enter Id of Event which you want to Update :: ";
			cin >> event_id;
			for (int i = 0; i < id_s.size(); i++) {
				if (event_id == id_s[i]) {
					found = true;
					break;
				}
				else {
					found = false;
				}
			}
			if (!found) cout << "\n\t--(Event with this event_id is not Exist.Plz !Select another )--\n";
			else break;
		} while (true);
		Query = "UPDATE Event SET event_id=" + to_string(event_id);
		char ch;
		// Changing Title
		cin.ignore(256, '\n');
		cout << "\n\t-->Enter 'y' for changing Title (otherwise any one else) -->";
		ch = _getche();
		if (ch == 'y' || ch == 'Y') {
			cout << "\n\t --> Enter the title of Event :: ";
			getline(cin, title);
			Query += ",title='" + title + "'";
		}
		// Changing Description
		cout << "\n\t-->Enter 'y' for changing Description (otherwise any one else) -->";
		ch = _getche();
		if (ch == 'y' || ch == 'Y') {
			cout << "\n\t --> Enter the description of Event :: ";
			getline(cin, des);
			Query += ",description='" + des + "'";
		}
		// Changing Venue
		cout << "\n\t-->Enter 'y' for changing Venue (otherwise any one else) -->";
		ch = _getche();
		if (ch == 'y' || ch == 'Y') {
			cout << "\n\t --> Enter the venue of Event :: ";
			getline(cin, venue);
			Query += ",venue='" + venue + "'";
		}
		//Changing Date
		cout << "\n\t-->Enter 'y' for changing Date (otherwise any one else) -->";
		ch = _getche();
		if (ch == 'y' || ch == 'Y') {
			cout << "\n\t --> Enter date in form <Year is greater than 2000 and less then 2050>(DDMMYYYY) :: ";
			cin >> date;
			D.set_date(date);
			Query += ",event_date='" + D.get_date() + "'";
		}
		Query += " Where event_id=" + to_string(event_id) + ";";
		if (mysql_query(SQL.conn, Query.c_str())) {
			cout << "\nError in query " << mysql_error(SQL.conn);
		}
		else {
			cout << "\n\t\t <------------- EVENT UPDATE SUCCESSFULLY ---------------->\n";
		}


	}else{
		cout << "\n\t <--------------- no record Available ----------------------->\n";
	}
		
}

void Admin::add_club() const
{
	display_club();//display club
	string club_name,desc;//get data from admin
	cin.ignore(256, '\n');
	cout << "\n\t --> Enter the name of Club :: ";
	getline(cin, club_name);
	cout << "\n\t --> Enter the description of Club :: ";
	getline(cin, desc);
	//insert into club
	string Query = "INSERT INTO Club (name, description) VALUES ('" + club_name + "','" + desc + "');";
	if (mysql_query(SQL.conn, Query.c_str())) {
		cout << "\nError in query " << mysql_error(SQL.conn);
		exit(0);
	}
	else {
		cout << "\n\t\t ---------- ADD CLUB SUCCESSFULLY -------------------\n";
	}
}

void Admin::update_club() const
{
	display_club();//display club
	if (mysql_query(SQL.conn, "SELECT club_id FROM Club")) {
		cout << "\nError in query " << mysql_error(SQL.conn);
		exit(0);
	}
	MYSQL_RES* RES = mysql_store_result(SQL.conn);
	MYSQL_ROW ROW;
	//check data of club is available or not
	if (mysql_num_rows(RES)) {
		cout << mysql_num_rows(RES) << endl;
		vector <int> id_s;
		while (ROW = mysql_fetch_row(RES)) {
			id_s.push_back(stoi(ROW[0]));
		}
		mysql_free_result(RES);
		int club_id;
		string club_name, desc, Query;
		bool found = false;
		do {
			cout << "\n\t --> Enter Id of Club which you want to Update :: ";
			cin >> club_id;
			for (int i = 0; i < id_s.size(); i++) {
				if (club_id == id_s[i]) {
					found = true;
					break;
				}
				else {
					found = false;
				}
			}
			if (!found) cout << "\n\t--(Club with this club_id is not Exist.Plz !Select another )--\n";
			else break;
		} while (true);
		Query = "UPDATE Club SET club_id=" + to_string(club_id);
		char ch;
		// Changing Club Name
		cin.ignore(256, '\n');
		cout << "\n\t-->Enter 'y' for changing Club Name (otherwise any one else) -->";
		ch = _getche();
		if (ch == 'y' || ch == 'Y') {
			cout << "\n\t --> Enter the name of Club :: ";
			getline(cin, club_name);
			Query += ",name='" + club_name + "'";
		}
		// Changing Description
		cout << "\n\t-->Enter 'y' for changing Description (otherwise any one else) -->";
		ch = _getche();
		if (ch == 'y' || ch == 'Y') {
			cout << "\n\t --> Enter the description of Club :: ";
			getline(cin, desc);
			Query += ",description='" + desc + "'";
		}
		Query += " Where club_id=" + to_string(club_id) + ";";
		if (mysql_query(SQL.conn, Query.c_str())) {
			cout << "\nError in query " << mysql_error(SQL.conn);
			exit(0);
		}
		else {
			cout << "\n\t\t <------------- CLUB UPDATE SUCCESSFULLY ---------------->\n";
		}
	}else{
		cout << "\n\t <--------------- no record Available ----------------------->\n";
	}
}
		
void Admin::add_library_resource() const
{
	string title,author;
	display_library_resource();//display all library resource
	cin.ignore(256, '\n');//get all data from admin about resource
	cout << "\n\t --> Enter the title of  Resource/Book:: ";
	getline(cin, title);
	cout << "\n\t --> Enter the Author of Resource/Book :: ";
	getline(cin, author);
	//insert into mysql
	string Query = "INSERT INTO LibraryResource (title, author, availability) VALUES(\'" + title + "\',\'" + author + "\',true);";
	if (mysql_query(SQL.conn, Query.c_str())) {
		cout << "\nError in query " << mysql_error(SQL.conn);
		exit(0);
	}
	else {
		cout << "\n\t\t ---------- ADD LIBRARY RESOURCE SUCCESSFULLY -------------------\n";
	}
}

void Admin::update_library_resource() const
{
	display_library_resource();//display data
	if (mysql_query(SQL.conn, "SELECT resource_id FROM LibraryResource")) {
		cout << "\nError in query " << mysql_error(SQL.conn);
	}
	MYSQL_RES* RES = mysql_store_result(SQL.conn);
	MYSQL_ROW ROW;
	//check data of library Resources is available or not
	if (mysql_num_rows(RES)) {
		cout << mysql_num_rows(RES) << endl;
		vector <int> id_s;
		while (ROW = mysql_fetch_row(RES)) {
			id_s.push_back(stoi(ROW[0]));
		}
		mysql_free_result(RES);
		int resource_id;
		string title, author, Query;
		bool found = false;
		//get library resources id
		do {
			cout << "\n\t --> Enter Id of Resource/Book which you want to Update :: ";
			cin >> resource_id;
			for (int i = 0; i < id_s.size(); i++) {
				if (resource_id == id_s[i]) {
					found = true;
					break;
				}
				else {
					found = false;
				}
			}
			if (!found) cout << "\n\t--(Resource/Book with this resource_id is not Exist.Plz !Select another )--\n";
			else break;
		} while (true);
		char ch;
		Query = "UPDATE LibraryResource SET resource_id=" + to_string(resource_id);
		// Changing Title
		cin.ignore(256, '\n');
		cout << "\n\t-->Enter 'y' for changing Title (otherwise any one else) -->";
		ch = _getche();
		if (ch == 'y' || ch == 'Y') {
			cout << "\n\t --> Enter the title of Resource/Book :: ";
			getline(cin, title);
			Query += ",title='" + title + "'";
		}
		// Changing Author
		cout << "\n\t-->Enter 'y' for changing Author (otherwise any one else) -->";
		ch = _getche();
		if (ch == 'y' || ch == 'Y') {
			cout << "\n\t --> Enter the Author of Resource/Book :: ";
			getline(cin, author);
		   Query += ",author='" + author + "'";
		}
		Query += " Where resource_id=" + to_string(resource_id) + ";";
		if (mysql_query(SQL.conn, Query.c_str())) {
			cout << "\nError in query " << mysql_error(SQL.conn);
			exit(0);
		}
		else {
			cout << "\n\t\t <------------- LIBRARY RESOURCE UPDATE SUCCESSFULLY ---------------->\n";
		}
	}else{
		cout << "\n\t <--------------- no record Available ----------------------->\n";
	}
}

void Admin::change_availabilty_of_library_resource() const
{
	display_library_resource();//display resources
	if (mysql_query(SQL.conn, "SELECT resource_id FROM LibraryResource;")) {
		cout << "\nError in query " << mysql_error(SQL.conn);
	}
	MYSQL_RES* RES = mysql_store_result(SQL.conn);
	MYSQL_ROW ROW;
	//check data of resource is available or not
	if (mysql_num_rows(RES)) {
		cout << mysql_num_rows(RES) << endl;

		vector <int> id_s;
		while (ROW = mysql_fetch_row(RES)) {
			id_s.push_back(stoi(ROW[0]));
		}
		mysql_free_result(RES);
		//get resources id fro changing availabilty
		int resource_id;
		bool found = false;
		do {
			cout << "\n\t --> Enter Id of Resource/Book which you want to Update :: ";
			cin >> resource_id;
			for (int i = 0; i < id_s.size(); i++) {
				if (resource_id == id_s[i]) {
					found = true;
					break;
				}
				else {
					found = false;
				}
			}
			if (!found) cout << "\n\t--(Resource/Book with this resource_id is not Exist.Plz !Select another )--\n";
			else break;
		} while (true);
		//change on mysql and real data
		string Query = "UPDATE LibraryResource	SET availability = CASE	WHEN availability = true THEN false	ELSE true END WHERE resource_id=" + to_string(resource_id) + "; ";
		if (mysql_query(SQL.conn, Query.c_str())) {
			cout << "\nError in query " << mysql_error(SQL.conn);
			exit(0);
		}
		else {
			cout << "\n\t\t <------------- STATUS OF LIBRARY RESOURCE UPDATE SUCCESSFULLY ---------------->\n";
		}
	}else{
		cout << "\n\t <--------------- no record Available ----------------------->\n";
	}
}

void Admin::display_feedback() const
{
	//get all feedback and display on screen
	if (mysql_query(SQL.conn, "SELECT S.student_id,S.name,C.name,F.feedback_content,F.rating FROM Feedback F join Student S ON F.student_id=S.student_id JOIN Course C ON F.course_id=C.course_id;")) {
		cout << "\nError in query " << mysql_error(SQL.conn);
	}
		MYSQL_RES* RES = mysql_store_result(SQL.conn);
		MYSQL_ROW ROW;
	if (mysql_num_rows(RES)) {
		cout << "\n+=============+==============================+=====================================+====================================================================+===========+" << endl;
		cout << "| Student_id  |  student Name                |   Course Name                       |     Feedback Content                                               | Rating    |" << endl;
		cout << "+-------------+------------------------------+-------------------------------------+--------------------------------------------------------------------+-----------+" << endl;
		while (ROW = mysql_fetch_row(RES)) {
			cout << "| " << setw(10) << ROW[0] << " | " << setw(29) << ROW[1] << " | " << setw(35) << ROW[2] << " | " << setw(66) << ROW[3] << " | " << setw(9) << ROW[4] << " |" << endl;
		}
		cout << "+=============+==============================+=====================================+====================================================================+===========+" << endl;
	}else{
		cout << "\n\t <--------------- no record Available ----------------------->\n";
	}
}

Admin::~Admin()
{
	cout << "admin_id :" << get_id();
}
