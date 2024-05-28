#include "Student.h"


//function to set the values of ember varaible
void Student::read_data() 
{
	
	string Query = "SELECT C.course_id,C.name,C.credits,C.Semester FROM Course C,enrollment E	WHERE C.course_id=E.course_id AND E.student_id =" + to_string(get_id()) + ";";
	if (mysql_query(SQL.conn, Query.c_str())) {
		cout << "Error executing query: " << mysql_error(SQL.conn) << endl;
		exit(0);
	}
	MYSQL_RES* RES = mysql_store_result(SQL.conn);
	MYSQL_ROW ROW;
	while (ROW = mysql_fetch_row(RES)) {
			enroll_courses.push_back(new Course(stoi(ROW[0]), ROW[1], ROW[2], stoi(ROW[3])));
		}
	mysql_free_result(RES);
	Query="SELECT C.club_id,C.name,C.description FROM Club C,club_joined CJ WHERE CJ.club_id=C.club_id AND CJ.student_id =" + to_string(get_id()) + ";";
	if (mysql_query(SQL.conn, Query.c_str())) {
		cout << "Error executing query: " << mysql_error(SQL.conn) << endl;
		exit(0);
	}
	RES = mysql_store_result(SQL.conn);
	while (ROW = mysql_fetch_row(RES)) {
		join_clubs.push_back(new Club(stoi(ROW[0]), ROW[1], ROW[2]));
	}
	mysql_free_result(RES);
}


Student::Student() :Person(), department_id(0), semester(0)
{
	read_data();
}



Student::Student(int Student_id, string Name, string Email, string PhoneNo, int dept_id, int semsr) : Person(Student_id, Name, Email, PhoneNo), department_id(dept_id), semester(semsr)
{
	//cout << "\nStudent Constructor\n";
	read_data();
}
void Student::set_department_id(int dept_id)
{
	this->department_id = dept_id;

}
void Student::set_semester(int semester)
{
	this->semester = semester;
}
int Student::get_department_id() const
{
	return this->department_id;
}
int Student::get_semester() const
{
	return this->semester;
}
void Student::enrollment_in_course() 
{
	//get all courses from mysql whci offer in the semester
	string Query = "SELECT * FROM Course WHERE Semester=" + to_string(semester) + " AND course_id NOT IN(SELECT course_id 	FROM enrollment	WHERE student_id =" + to_string(get_id()) + ");";
	if (mysql_query(SQL.conn, Query.c_str())) {
		cout << "Error executing query: " << mysql_error(SQL.conn) << endl;
		exit(0);
	}
	MYSQL_RES* RES = mysql_store_result(SQL.conn);
	MYSQL_ROW ROW;
	//check data of Course is available or not
	if (mysql_num_rows(RES)) {
		vector <int> ids;
		//display on screen
		cout << "\n+==============================================================+"
			<< "\n| Course_id    |     Name                        |   Credits   |"
			<< "\n+--------------+---------------------------------+-------------+";
		while (ROW = mysql_fetch_row(RES)) {
			ids.push_back(stoi(ROW[0]));
			cout << left << "\n|  " << setw(12) << ROW[0] << "| " << setw(31) << ROW[1] << " |   " << setw(9) << ROW[2] << " |   ";
		}
		mysql_free_result(RES);
		cout << "\n+==============================================================+\n\n";
		int id;
		bool found = false;
		do {
			//enter the course whcih you want to enroll
			cout << "Enter the id of the course to enroll: ";
			cin >> id;
			for (int i = 0; i < ids.size(); i++) {
				//cout << ids[i] << " ";
				if (id == ids[i]) {
					found = true;
					break;
				}
				else {
					found = false;
				}
			}
			if (!found)cout << "\n\t--(Course with this course_id is not Exist.Plz !Select another )--\n";
		} while (!found);
		string query = "INSERT INTO Enrollment(student_id,course_id,enrollment_date) values (" + to_string(get_id()) + "," + to_string(id) + ",curdate());";
		if (mysql_query(SQL.conn, query.c_str())) {
			cout << "Error executing query: " << mysql_error(SQL.conn) << endl;
		}
		else {
			cout << "\n\t\t <------------- Course Enrolled Successfully ---------------->\n";
			read_data();
		}
	}else{
		cout << "\n\t <--------------- no record Available ----------------------->\n";
	}
}

void Student::enrolled_course() const
{
	//get data in whcih student enroll
	string Query = "Select E.course_id, C.name ,E.enrollment_date  from Enrollment as E, Course as C Where E.course_id=C.course_id AND student_id=" + to_string(get_id());
	if (mysql_query(SQL.conn, Query.c_str())) {
		cout << "Error executing query: " << mysql_error(SQL.conn) << endl;
		exit(0);
	}
	MYSQL_RES* RES = mysql_store_result(SQL.conn);
	MYSQL_ROW ROW;
	//check data of courses in whcih is available or not
	if (mysql_num_rows(RES)) {
		cout << "\n+==============================================================+"
			<< "\n| Course_id    |     Course Name                 |  Enroll Date |"
			<< "\n+--------------+---------------------------------+-------------+";
		while (ROW = mysql_fetch_row(RES)) {
			cout << left << "\n|  " << setw(12) << ROW[0] << "| " << setw(31) << ROW[1] << " |   " << setw(9) << ROW[2] << " |   ";
		}
		mysql_free_result(RES);

		cout << "\n+==============================================================+\n\n";
	}
	else {
		cout << "\n\t <--------------- no record Available ----------------------->\n";
	}
}

void Student::join_club() 
{
	//get data of club
	string Query = "SELECT * FROM Club WHERE club_id NOT IN(SELECT club_id FROM Club_Joined WHERE student_id=" + to_string(get_id()) + " );";
	if (mysql_query(SQL.conn, Query.c_str())) {
		cout << "Error executing query: " << mysql_error(SQL.conn) << endl;
		exit(0);
	}
	MYSQL_RES* RES = mysql_store_result(SQL.conn);
	MYSQL_ROW ROW;
	//check data of club is available or not
	if (mysql_num_rows(RES)) {
		vector <int> ids;
		cout << "\n+==================================================+"
			<< "\n| Club_id      |    Club Name                      |"
			<< "\n+--------------+-----------------------------------+";
		while (ROW = mysql_fetch_row(RES)) {
			ids.push_back(stoi(ROW[0]));
			cout << left << "\n|  " << setw(12) << ROW[0] << "| " << setw(33) << ROW[1] << " |   ";
		}
		mysql_free_result(RES);
		cout << "\n+==================================================+\n\n";
		//get club id whcih want to join
		int id;
		bool found = false;
		do {
			cout << "Enter the id of the club to join: ";
			cin >> id;
			for (int i = 0; i < ids.size(); i++) {
				//cout << ids[i] << " ";
				if (id == ids[i]) {
					found = true;
					break;
				}
				else {
					found = false;
				}
			}
			if (!found)cout << "\n\t--(Club with this club_id is not Exist.Plz !Select another )--\n";
		} while (!found);
		string query = "INSERT INTO Club_Joined(student_id,club_id,joining_date) values (" + to_string(get_id()) + "," + to_string(id) + ",curdate());";
		if (mysql_query(SQL.conn, query.c_str())) {
			cout << "Error executing query: " << mysql_error(SQL.conn) << endl;
		}
		else {
			cout << "\n\t\t <------------- Club joined Successfully ---------------->\n";
			read_data();
		}
	}else{
		cout << "\n\t <--------------- no record Available ----------------------->\n";
	}
}

void Student::display_joined_club() const
{
	//get data of club which join
	string Query = "Select C.club_id, C.name , JC.joining_date  from club_joined as JC, Club as C Where C.club_id=JC.club_id AND student_id=" + to_string(get_id());
	if (mysql_query(SQL.conn, Query.c_str())) {
		cout << "Error executing query: " << mysql_error(SQL.conn) << endl;
		exit(0);
	}
	MYSQL_RES* RES = mysql_store_result(SQL.conn);
	MYSQL_ROW ROW;	
	//check data of club joining is available or not
	if (mysql_num_rows(RES)) {
		cout << "\n+==============================================================+"
			<< "\n| Club_id      |     Club Name                   | Joined Date |"
			<< "\n+--------------+---------------------------------+-------------+";
		while (ROW = mysql_fetch_row(RES)) {
			cout << left << "\n|  " << setw(12) << ROW[0] << "| " << setw(31) << ROW[1] << " |   " << setw(8) << ROW[2] << " |   ";
		}
		mysql_free_result(RES);
		cout << "\n+==============================================================+\n\n";
	}else{
		cout << "\n\t <--------------- no record Available ----------------------->\n";
	}
}

void Student::feedback() const
{
	enrolled_course();//display enrolled courses
	string Query;
	Query = "Select E.course_id from Enrollment as E, Course as C Where E.course_id=C.course_id AND student_id=" + to_string(get_id());
	if (mysql_query(SQL.conn, Query.c_str())) {
		cout << "Error executing query: " << mysql_error(SQL.conn) << endl;
		exit(0);
	}
	MYSQL_RES* RES = mysql_store_result(SQL.conn);
	MYSQL_ROW ROW;
	//check data of enrollment courses is available or not
	if (mysql_num_rows(RES)) {
		vector <int> ids;
		while (ROW = mysql_fetch_row(RES)) {
			ids.push_back(stoi(ROW[0]));
		}
		int id;
		string feedback;
		int ratings;
		//get feedback data
		bool found = false;
		do {
			cout << "\n\t-->Enter the id of the course to give feedback: ";
			cin >> id;
			for (int i = 0; i < ids.size(); i++) {
				//cout << ids[i] << " ";
				if (id == ids[i]) {
					found = true;
					break;
				}
				else {
					found = false;
				}
			}
			if (!found)cout << "\n\t--(Course with this course_id is not Exist.Plz !Select another )--\n";
		} while (!found);
		do {
			cout << "\n\t-->How many ratings you want to give this course: ";
			cin >> ratings;
			if (ratings < 0 || ratings>5) cout << "\nInvalid rating. Only give 0 to 5 stars.\n";
			else break;
		} while (true);
		cout << "\n\t-->Enter your feedback in words: ";
		cin.ignore(256, '\n');

		getline(cin, feedback);

		string query = "INSERT INTO Feedback(student_id,course_id,Rating,feedback_content) values (" + to_string(get_id()) + "," + to_string(id) + "," + to_string(ratings) + ",'" + feedback + "');";
		if (mysql_query(SQL.conn, query.c_str())) {
			cout << "Error executing query: " << mysql_error(SQL.conn) << endl;
		}
		else
			cout << "\n\t\t <------------- Feedback Given Successfully ---------------->\n";
	}else{
		cout << "\n\t <--------------- no record Available ----------------------->\n";
	}
}

void Student::display_attendence() const
{
	//get data from mysql
	string Query = "SELECT C.course_id, C.name, A.attendance_percentage FROM Attendance A, Course C WHERE A.course_id=C.course_id AND A.student_id=" + to_string(get_id()) + ";";
	if (mysql_query(SQL.conn, Query.c_str())) {
		cout << "Error excuting Query: " << mysql_error(SQL.conn) << endl;
	}
	MYSQL_RES* RES = mysql_store_result(SQL.conn);
	MYSQL_ROW ROW;
	//check data of attendenece is available or not
	if (mysql_num_rows(RES)) {
		cout << "\n+=========================================================================+"
			<< "\n| Course_id    |     Course Name                 |  Attendance Percentage |"
			<< "\n+--------------+---------------------------------+------------------------+";
		while (ROW = mysql_fetch_row(RES)) {
			cout << left << "\n|  " << setw(12) << ROW[0] << "| " << setw(31) << ROW[1] << " |   " << setw(19) << ROW[2] << " |   ";
		}
		mysql_free_result(RES);
		cout << "\n+========================================================================+\n\n";
	}else{
		cout << "\n\t <--------------- no record Available ----------------------->\n";
	}
}

void Student::display_grade() const
{
	//get grade data
	string Query = "SELECT C.course_id, C.name, G.grade_status FROM Grade G, Course C WHERE C.course_id=G.course_id AND G.student_id=" + to_string(get_id()) + ";";
	if (mysql_query(SQL.conn, Query.c_str())) {
		cout << "Error excuting Query: " << mysql_error(SQL.conn) << endl;
	}
	MYSQL_RES* RES = mysql_store_result(SQL.conn);
	MYSQL_ROW ROW;
	//check data of grade is available or not
	if (mysql_num_rows(RES)) {
		cout << "\n+=========================================================================+"
			<< "\n| Course_id    |     Course Name                 |      Grade_Status      |"
			<< "\n+--------------+---------------------------------+------------------------+";
		while (ROW = mysql_fetch_row(RES)) {
			cout << left << "\n|  " << setw(12) << ROW[0] << "| " << setw(31) << ROW[1] << " |   " << setw(19) << ROW[2] << " |   ";
		}
		mysql_free_result(RES);
		cout << "\n+========================================================================+\n\n";
	}else{
		cout << "\n\t <--------------- no record Available ----------------------->\n";
	}
}

void Student::submit_assignment() const
{
	//get  assignment data
	string query = "SELECT C.course_id,C.name,A.description,A.due_date,A.assignment_id FROM enrollment AS E JOIN course AS C ON E.course_id=C.course_id JOIN assignment AS A ON C.course_id=A.course_id WHERE A.due_date>CURDATE();";
	if (mysql_query(SQL.conn, query.c_str())) {
		cout << "Error excuting Query: " << mysql_error(SQL.conn) << endl;
	}
	MYSQL_RES* RES = mysql_store_result(SQL.conn);
	MYSQL_ROW ROW;
	//check data of  assignment is available or not
	if (mysql_num_rows(RES)) {
		vector <int> ids;
		cout << "\n+==============+=================================+===========================================================+===================+==================+"
			<< "\n| Course_id    |     Course Name                 |      Assignment Discreptiption                            |     Due-Date      |  Assignment_id  |"
			<< "\n+--------------+---------------------------------+-----------------------------------------------------------+-------------------+-----------------+";
		while (ROW = mysql_fetch_row(RES)) {
			cout << left << "\n|  " << setw(12) << ROW[0] << "| " << setw(31) << ROW[1] << " |   " << setw(55) << ROW[2] << " |   " << setw(16) << ROW[3] << " | " << setw(15) << ROW[4] << " |";
			ids.push_back(stoi(ROW[4]));
		}
		mysql_free_result(RES);
		cout << "\n+==================================================================================================================================================+\n\n";

		int id;
		bool found = false;
		do {//enter assignment id which want to submit
			cout << "Enter the id of the assignment to submit: ";
			cin >> id;
			for (int i = 0; i < ids.size(); i++) {
				//cout << ids[i] << " ";
				if (id == ids[i]) {
					found = true;
					break;
				}
				else {
					found = false;
				}
			}
			if (!found)cout << "\n\t--(Assignment with this assignment_id is not Exist.Plz !Select another )--\n";
		} while (!found);
		//after submitting assignment check the assignment is already submit or not
		query = "SELECT student_id FROM submit_assignment WHERE student_id = " + to_string(get_id()) + " AND assignment_id = " + to_string(id) + ";";
		if (mysql_query(SQL.conn, query.c_str())) {
			cout << "Error excuting Query: " << mysql_error(SQL.conn) << endl;
		}
		RES = mysql_store_result(SQL.conn);
		found = false;
		while (ROW = mysql_fetch_row(RES)) {
			found = true;
		}
		if (found) cout << "\nThis assignment is already submitted..\n";
		else {
			query = "INSERT INTO submit_assignment(student_id,assignment_id,submit_date) VALUES(" + to_string(get_id()) + "," + to_string(id) + ",CURDATE());";
			if (mysql_query(SQL.conn, query.c_str())) {
				cout << "Error executing query: " << mysql_error(SQL.conn) << endl;
			}
			else {
				cout << "\n\t\t <------------- Assignment Submitted Successfully ---------------->\n";
			}
		}
	}else{
		cout << "\n\t <--------------- no record Available ----------------------->\n";
	}
}

void Student::display_assign_project() const
{
	//Get all project detail student enroll
	string Query = "SELECT P.project_id,P.project_title,P.description FROM Project P,Project_assign_to_Student PS where PS.project_id=P.project_id AND PS.Student_id=" + to_string(get_id()) + ";";
	vector <int> id_s;
	if (mysql_query(SQL.conn, Query.c_str())) {
		cout << "Error executing query: " << mysql_error(SQL.conn) << endl;
		exit(0);
	}
	MYSQL_RES* RES = mysql_store_result(SQL.conn);
	MYSQL_ROW ROW;
	//check data of project is available or not
	if (mysql_num_rows(RES)) {
		cout << "\n+-----------+-------------------------------------+----------------------------------------------------------------+" << endl;
		cout << "| project_id| title                               | description                                                    |" << endl;
		cout << "+-----------+-------------------------------------+----------------------------------------------------------------+" << endl;
		while (ROW = mysql_fetch_row(RES)) {
			id_s.push_back(stoi(ROW[0]));
			cout << "| " << setw(9) << ROW[0] << " | " << setw(35) << ROW[1] << " | " << setw(62) << ROW[2] << " |" << endl;
		}
		cout << "+-----------+-------------------------------------+----------------------------------------------------------------+" << endl;
		mysql_free_result(RES);
	}else{
		cout << "\n\t <--------------- no record Available ----------------------->\n";
	}
}

void Student::print_data() const
{
	cout << endl << "==> Id ::  " << get_id()
		<< endl << "==> Name ::  " << get_name_or_title()
		<< endl << "==> Email ::  " << get_email()
		<< endl << "==> Phone Number ::  " << get_phone_no()
		<< endl << "==> Department No :: " << department_id
		<< endl << "==> Semester :: " << semester << endl;
}

void Student::print() const
{
	print_data();
	if (enroll_courses.size() != 0) {
		cout << "\n\t<============ Enroll Courses =============================>\n";
		for (int i = 0; i < enroll_courses.size(); i++)
		{
			enroll_courses[i]->print();
		}
	}
	if (join_clubs.size() != 0) {
		cout << "\n\t<============ Joined Club =============================>\n";
		for (int i = 0; i < join_clubs.size(); i++)
		{
			join_clubs[i]->print_data();
		}
	}
}

Student::~Student()
{
	cout << endl << "Object of student Id " << get_id() << " from memory";
}