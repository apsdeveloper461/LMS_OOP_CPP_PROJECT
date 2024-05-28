#include"Date.h"
#include "Faculty.h"

//read data of all relational member varaible from mysql
void Faculty::read_data()
{
	teach_course.clear();
	string Query = "SELECT C.course_id,C.name,C.credits,C.Semester FROM Course C, CourseFacultyAllocation CFA	WHERE C.course_id=CFA.course_id AND CFA.faculty_id =" + to_string(get_id()) + ";";
	if (mysql_query(SQL.conn, Query.c_str())) {
		cout << "Error executing query: " << mysql_error(SQL.conn) << endl;
		exit(0);
	}
	MYSQL_RES* RES = mysql_store_result(SQL.conn);
	MYSQL_ROW ROW;
	while (ROW = mysql_fetch_row(RES)) {
		teach_course.push_back(new Course(stoi(ROW[0]), ROW[1], ROW[2], stoi(ROW[3])));
	}
}

Faculty::Faculty():Person()
{
	read_data();
}


Faculty::Faculty(int faculty_id, string Name, string Email, string PhoneNo) :Person(faculty_id, Name, Email, PhoneNo)
{
	cout << "\nFaculty Constructor\n";
	read_data();
}

void Faculty::print() const
{
	print_data();
	cout << "\n\t <============= Course which i teach ==================>\n";
	for (int i = 0; i < teach_course.size(); i++)
	{
		teach_course[i]->print();
	}
}

void Faculty::display_AllocaionCourse() const
{
	//get Allocation data from mysqland display on screen whcih allocate only this faculty 
	string Query = "SELECT cfa.enrollment_id,cfa.course_id,c.Name AS course_name FROM CourseFacultyAllocation cfa  JOIN Course c ON cfa.course_id = c.course_id  WHERE cfa.faculty_id=" +to_string(get_id()) + "; ";
	if (mysql_query(SQL.conn,Query.c_str()) ){
		cout << "Error executing query: " << mysql_error(SQL.conn) << endl;
		exit(0);
	}
	MYSQL_RES* RES = mysql_store_result(SQL.conn);
	MYSQL_ROW ROW;
	//check data of Allocation is available or not
	if (mysql_num_rows(RES)) {
		cout << "\n+---------------+-----------+---------------------------------+" << endl;
		cout << "| allocation_id | course_id | course_name                     |" << endl;
		cout << "+---------------+-----------+---------------------------------+" << endl;

		while (ROW = mysql_fetch_row(RES)) {
			cout << "| " << setw(13) << ROW[0] << " | " << setw(9) << ROW[1] << " | " << setw(31) << ROW[2] << " |" << endl;
		}
		mysql_free_result(RES);
		cout << "+---------------+-----------+---------------------------------+" << endl;
	}
	else {
		cout << "\n\t <--------------- no record Available ----------------------->\n";
	}
}


//this function is used ro get allocation id from allocate course faculty (if the not course allocate faculty return 0)
int Faculty::get_course_id_from_Allocation() const
{
	display_AllocaionCourse();//display Allocation
	string Query = "SELECT cfa.course_id AS course_name FROM CourseFacultyAllocation cfa  JOIN Course c ON cfa.course_id = c.course_id  WHERE cfa.faculty_id=" + to_string(get_id()) + "; ";
	if (mysql_query(SQL.conn, Query.c_str())) {
		cout << "Error executing query: " << mysql_error(SQL.conn) << endl;
		exit(0);
	}
	MYSQL_RES* RES = mysql_store_result(SQL.conn);
	MYSQL_ROW ROW;
	//check data of course infromation whci alllocate you is available or not
	if (mysql_num_rows(RES)) {
		vector <int> id_s;
		while (ROW = mysql_fetch_row(RES)) {
			id_s.push_back(stoi(ROW[0]));
		}
		int id;
		bool found = false;
		do {
			cout << "\t --> Enter Id of Course :: ";
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

		return id;
	}
	else {
		return 0;
	}
}
//function to get student from enroll in course which you teach (if not astudent is study in allocate course return 0 this function
int Faculty::get_student_id_from_enrollment(int &cour_id) const
{
	//get data from mysql
	string Query = "SELECT e.student_id,s.name  FROM Enrollment e, Student s Where s.student_id = e.student_id  AND e.course_id=" + to_string(cour_id) + "; ";
	if (mysql_query(SQL.conn, Query.c_str())) {
		cout << "Error executing query: " << mysql_error(SQL.conn) << endl;
		exit(0);
	}
	MYSQL_RES* RES = mysql_store_result(SQL.conn);
	MYSQL_ROW ROW;
	//check data of Student whcih study of course whcih faculty teach is available or not
	if (mysql_num_rows(RES)) {
		vector <int> id_s;
		cout << "\n+------------+---------------------------------+" << endl;
		cout << "| Student_id | Student Name                    |" << endl;
		cout << "+------------+---------------------------------+" << endl;
		while (ROW = mysql_fetch_row(RES)) {
			cout << "| " << setw(10) << ROW[0] << " | " << setw(31) << ROW[1] << " |" << endl;
			id_s.push_back(stoi(ROW[0]));
		}
		cout << "+------------+---------------------------------+" << endl;
		int id;
		bool found = false;
		do {
			cout << "\t --> Enter Id of Student :: ";
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
		return id;
	}
	else {
		return 0;
	}
}

void Faculty::add_assignment() const
{
	int id=get_course_id_from_Allocation();
	//get from courses whcih allocate the faculty if 0 it means no curse allocate faculty
	if (id != 0) {
		//add assignment data 
		Date due_date;
		string d, description;
		cout << "\n\t-->Enter the due date of Assignment in in form <Year is greater than 2000 and less then 2050>(DDMMYYYY) ";
		cin >> d;
		due_date.set_date(d);
		cin.ignore(256, '\n');
		cout << "\n\t-->Enter the description of Assignment : ";
		getline(cin, description);
		string Query = "INSERT INTO Assignment (course_id,due_date,description) VALUES(" + to_string(id) + ",\'" + due_date.get_date() + "\',\'" + description + "\');";
		if (mysql_query(SQL.conn, Query.c_str())) {
			cout << "\n Error in query : " << mysql_error(SQL.conn);
			exit(0);
		}
		else {
			cout << "\n\t\t ---------- ADD ASSIGNMENT SUCCESSFULLY -------------------\n";
		}
	}
	else {
		cout << "\n\t<------------------ No Course Available ---------------------->\n";
	}
}

void Faculty::update_assignment() const
{
	int cour_id = get_course_id_from_Allocation();
	//get from courses whcih allocate the faculty if 0 it means no curse allocate faculty
	if (cour_id != 0) {
		display_assignment();//display assignment
		vector <int> ass_id_s;//get data from mysql
		string Query = "SELECT assignment_id FROM Assignment WHERE course_id=" + to_string(cour_id) + ";";
		if (mysql_query(SQL.conn, Query.c_str())) {
			cout << "Error executing query: " << mysql_error(SQL.conn) << endl;
			exit(0);
		}
		MYSQL_RES* RES = mysql_store_result(SQL.conn);
		MYSQL_ROW ROW;
		//check data of Assignment is available or not
		if (mysql_num_rows(RES)) {
			while (ROW = mysql_fetch_row(RES)) {
				ass_id_s.push_back(stoi(ROW[0]));
			}
			int ass_id;
			string descr, d;
			Date due_date;
			bool found = false;
			do {
				cout << "\t --> Enter Id of Assignment :: ";
				cin >> ass_id;
				for (int i = 0; i < ass_id_s.size(); i++) {
					if (ass_id == ass_id_s[i]) {
						found = true;
						break;
					}
					else
						found = false;
				}
				if (!found) cout << "\n\t--(Assignment with this assignment_id is not Exist.Plz !Select another )--\n";
			} while (!found);
			Query = "UPDATE Assignment SET assignment_id=" + to_string(ass_id);
			char ch;
			cout << "\n\t--> Enter 'y' fro changing description of Assignment (if not then press anyone else)-- >";
			ch = _getche();

			if (ch == 'y' || ch == 'Y') {
				cin.ignore(256, '\n');
				cout << "\n\t-->Enter the description of Assignment : ";
				getline(cin, descr);
				Query += ",description = \'" + descr + "\'";
			}
			cout << "\n\t--> Enter 'y' fro changing due_date of Assignment (if not then press anyone else)-- >";
			ch = _getche();
			if (ch == 'y' || ch == 'Y') {
				cout << "\n\t-->Enter the due date of Assignment in in form <Year is greater than 2000 and less then 2050>(DDMMYYYY) ";
				cin >> d;
				due_date.set_date(d);
				Query += ", due_date = \'" + due_date.get_date() + "\'";
			}
			Query += " Where assignment_id=" + to_string(ass_id) + ";";
			if (mysql_query(SQL.conn, Query.c_str())) {
				cout << "\n Error in query : " << mysql_error(SQL.conn);
				exit(0);
			}
			else {
				cout << "\n\t\t ---------- UPDATE ASSIGNMENT SUCCESSFULLY -------------------\n";
			}
		}else{
			cout << "\n\t <--------------- no record Available ----------------------->\n";
		}
	}
	else {
		cout << "\n\t<---------------- No Course I teach ------------------->\n";
	}
}
void Faculty::display_assignment() const 
{
	int cour_id = get_course_id_from_Allocation();
	//get from courses whcih allocate the faculty if 0 it means no curse allocate faculty
	if (cour_id != 0) {
		string Query = "SELECT a.assignment_id,description,a.due_date FROM Assignment a WHERE a.course_id=" + to_string(cour_id) + "; ";
		if (mysql_query(SQL.conn, Query.c_str())) {
			cout << "Error executing query: " << mysql_error(SQL.conn) << endl;
			exit(0);
		}
		MYSQL_RES* RES = mysql_store_result(SQL.conn);
		MYSQL_ROW ROW;
		//check data of assignment is available or not
		if (mysql_num_rows(RES)) {
			cout << "\n+---------------+-----------------------------------------------------------------------------------------+----------------------+" << endl;
			cout << "| assignment_id |           assignment_description                                                        |  assignment_deadline |" << endl;
			cout << "+---------------+-----------------------------------------------------------------------------------------+----------------------+" << endl;
			while (ROW = mysql_fetch_row(RES)) {
				cout << "| " << setw(13) << ROW[0] << " | " << setw(87) << ROW[1] << " | " << setw(20) << ROW[2] << " |" << endl;
			}
			mysql_free_result(RES);
			cout << "+---------------+-----------------------------------------------------------------------------------------+----------------------+" << endl;
		}
		else {
			cout << "\n\t <--------------- no record Available ----------------------->\n";
		}
	}
	else {
		cout << "\n\t<---------------- No Course I teach ------------------->\n";
	}
}

void Faculty::add_attendance() const
{
	int cour_id = get_course_id_from_Allocation();
	//get from courses whcih allocate the faculty if 0 it means no curse allocate faculty
	if (cour_id != 0) {
		int std_id = get_student_id_from_enrollment(cour_id);
		//get from student which teach the faculty if 0 it means no student teach by faculty
		if (std_id != 0) {
			string Query = "SELECT student_id from  Attendance WHERE course_id=" + to_string(cour_id) + ";";
			if (mysql_query(SQL.conn, Query.c_str())) {
				cout << "\n Error in query : " << mysql_error(SQL.conn);
				exit(0);
			}
			bool std_id_exist = false;
			MYSQL_RES* RES = mysql_store_result(SQL.conn);
			MYSQL_ROW ROW;
			while (ROW = mysql_fetch_row(RES)) {
				if (std_id == stoi(ROW[0])) {
					std_id_exist = true;
					break;
				}
			}
			if (std_id_exist) {
				cout << "\n\t\t <------------------------ Already add attendence -------------------------------->\n\n";
			}
			else {
				double attendance;
				do {
					cout << "\n\t-->Enter the attendance ---(1%--100%)--- : ";
					cin >> attendance;
					if (attendance < 1 || attendance>100) cout << "\n\t -- ( Invalid attendance percentage )-----\n";
					else break;
				} while (true);
				Query = "INSERT INTO attendance (course_id,student_id,attendance_percentage) VALUES(" + to_string(cour_id) + "," + to_string(std_id) + ", " + to_string(attendance) + ");";
				if (mysql_query(SQL.conn, Query.c_str())) {
					cout << "\n Error in query : " << mysql_error(SQL.conn);
					exit(0);
				}
				else {
					cout << "\n\t\t ---------- ADD Attendenece SUCCESSFULLY -------------------\n";
				}
			}
		}
		else {
			cout << "\n\t<----------- No Student enroll in this course--------------------->\n";
		}
	}
	else {
		cout << "\n\t<----------- No course i teach--------------------->\n";
	}
}

void Faculty::update_attendance() const
{
	int cour_id = get_course_id_from_Allocation();
	//get from courses whcih allocate the faculty if 0 it means no curse allocate faculty
	if (cour_id != 0) {
		int std_id = get_student_id_from_enrollment(cour_id);
		//get from student which teach the faculty if 0 it means no student teach by faculty
		if (std_id != 0) {
			double attendance;
			do {
				cout << "\n\t-->Enter the attendance ---(1%--100%)--- : ";
				cin >> attendance;
				if (attendance < 1 || attendance>100) cout << "\n\t -- ( Invalid attendance percentage )-----\n";
				else break;
			} while (true);
			string Query = "UPDATE attendance SET attendance_percentage=" + to_string(attendance) + " WHERE course_id=" + to_string(cour_id) + " AND student_id=" + to_string(std_id) + ";";
			if (mysql_query(SQL.conn, Query.c_str())) {
				cout << "\n Error in query : " << mysql_error(SQL.conn);
				exit(0);
			}
			else {
				cout << "\n\t\t ---------- Update Attendenece SUCCESSFULLY -------------------\n";
			}
		}
		else {
			cout << "\n\t<----------- No Student enroll in this course --------------------->\n";

		}
	}
	else {
		cout << "\n\t<----------- No course i teach--------------------->\n";
	}

}
void Faculty::display_attendance() const
{
	int cour_id = get_course_id_from_Allocation();
	//get from courses whcih allocate the faculty if 0 it means no curse allocate faculty
	if (cour_id != 0) {
		string Query = "SELECT a.attendance_id,s.student_id,s.name,a.attendance_percentage FROM Attendance a join Student s ON a.student_id=s.student_id WHERE a.course_id=" + to_string(cour_id) + "; ";
		if (mysql_query(SQL.conn, Query.c_str())) {
			cout << "Error executing query: " << mysql_error(SQL.conn) << endl;
			exit(0);
		}
		MYSQL_RES* RES = mysql_store_result(SQL.conn);
		MYSQL_ROW ROW;
		if (mysql_num_rows(RES)) {
			cout << "\n+----------------+--------------+------------------------------------+----------------+" << endl;
			cout << "| atttendance_id | student_id   |  Student Name                      | attendance_per |" << endl;
			cout << "+----------------+--------------+------------------------------------+----------------+" << endl;
			while (ROW = mysql_fetch_row(RES)) {
				cout << "| " << setw(14) << ROW[0] << " | " << setw(12) << ROW[1] << " | " << setw(34) << ROW[2] << " | " << setw(14) << ROW[3] << " |" << endl;
			}
			mysql_free_result(RES);
			cout << "+----------------+--------------+------------------------------------+----------------+" << endl;
		}
		else {
			cout << "\n\t <--------------- no record Available ----------------------->\n";
		}
	}
	else {
		cout << "\n\t<---------------- No Course I teach ------------------->\n";
	}
}



void Faculty::add_grade() const
{
	int cour_id = get_course_id_from_Allocation();
	//get from courses whcih allocate the faculty if 0 it means no curse allocate faculty
	if (cour_id != 0) {
		int std_id = get_student_id_from_enrollment(cour_id);
		//get from student which teach the faculty if 0 it means no student teach by faculty
		if (std_id != 0) {
			string Query = "SELECT student_id from  grade WHERE course_id=" + to_string(cour_id) + ";";
			if (mysql_query(SQL.conn, Query.c_str())) {
				cout << "\n Error in query : " << mysql_error(SQL.conn);
				exit(0);
			}
			bool std_id_exist = false;
			MYSQL_RES* RES = mysql_store_result(SQL.conn);
			MYSQL_ROW ROW;
			while (ROW = mysql_fetch_row(RES)) {
				if (std_id == stoi(ROW[0])) {
					std_id_exist = true;
					break;
				}
			}
			if (std_id_exist) {
				cout << "\n\t\t <------------------------ Already add grade -------------------------------->\n\n";
			}
			else {
				string grade;
				do {
					cout << "\n\t-->Enter the grade ---(A+ to F)--- : ";
					cin >> grade;
					if (grade == "A+" || grade == "A" || grade == "B+" || grade == "B" || grade == "C+" || grade == "C" || grade == "D" || grade == "F") break;
					else  cout << "\n\t -- ( Invalid Grade Status )-----\n";
				} while (true);
				Query = "INSERT INTO grade (course_id,student_id,grade_status) VALUES(" + to_string(cour_id) + "," + to_string(std_id) + ",\'" + grade + "\');";
				if (mysql_query(SQL.conn, Query.c_str())) {
					cout << "\n Error in query : " << mysql_error(SQL.conn);
					exit(0);
				}
				else {
					cout << "\n\t\t ---------- ADD Grade SUCCESSFULLY -------------------\n";
				}
			}
		}
		else {
			cout << "\n\t<----------- No Student enroll in this course--------------------->\n";

		}
	}
	else {
		cout << "\n\t<----------- No course i teach--------------------->\n";

	}
}

void Faculty::update_grade() const
{
	int cour_id = get_course_id_from_Allocation();
	//get from courses whcih allocate the faculty if 0 it means no curse allocate faculty
	if (cour_id != 0) {
		int std_id = get_student_id_from_enrollment(cour_id);
		//get from student which teach the faculty if 0 it means no student teach by faculty
		if (std_id != 0) {
			string grade;
			do {
				cout << "\n\t-->Enter the Grade ---(A+--F)--- : ";
				cin >> grade;
				if (grade == "A+" || grade == "A" || grade == "B+" || grade == "B" || grade == "C+" || grade == "C" || grade == "D" || grade == "F") break;
				else  cout << "\n\t -- ( Invalid Grade status)-----\n";
			} while (true);
			string Query = "UPDATE grade SET grade_status=\'" + grade + "\' WHERE course_id=" + to_string(cour_id) + " AND student_id=" + to_string(std_id) + ";";
			if (mysql_query(SQL.conn, Query.c_str())) {
				cout << "\n Error in query : " << mysql_error(SQL.conn);
				exit(0);
			}
			else {
				cout << "\n\t\t ---------- Update Grade SUCCESSFULLY -------------------\n";
			}
		}
		else {
			cout << "\n\t<----------- No Student enroll in this Course --------------------->\n";

		}
	}
	else {
		cout << "\n\t<----------- No course i teach--------------------->\n";
	}
}
void Faculty::display_grade() const
{
	int cour_id = get_course_id_from_Allocation();
	//get from courses whcih allocate the faculty if 0 it means no curse allocate faculty
	if (cour_id != 0) {
		string Query = "SELECT g.grade_id,s.student_id,s.name,g.grade_status FROM grade g join Student s ON g.student_id=s.student_id WHERE g.course_id=" + to_string(cour_id) + "; ";
		if (mysql_query(SQL.conn, Query.c_str())) {
			cout << "Error executing query: " << mysql_error(SQL.conn) << endl;
			exit(0);
		}
		MYSQL_RES* RES = mysql_store_result(SQL.conn);
		MYSQL_ROW ROW;
		if (mysql_num_rows(RES)) {
			cout << "\n+----------------+--------------+------------------------------------+----------------+" << endl;
			cout << "|    grade_id    | student_id   |  Student Name                      | grade_Status   |" << endl;
			cout << "+----------------+--------------+------------------------------------+----------------+" << endl;
			while (ROW = mysql_fetch_row(RES)) {
				cout << "| " << setw(14) << ROW[0] << " | " << setw(12) << ROW[1] << " | " << setw(34) << ROW[2] << " | " << setw(14) << ROW[3] << " |" << endl;
			}
			mysql_free_result(RES);
			cout << "+----------------+--------------+------------------------------------+----------------+" << endl;
		}
		else {
			cout << "\n\t <--------------- no record Available ----------------------->\n";
		}
	}
	else {
		cout << "\n\t<---------------- No Course I teach ------------------->\n";
	}
}

void Faculty::add_project() const
{
	string title, desc;
	cin.ignore(256, '\n');
	cout << "\n\t--> Enter the title of Project : ";
	getline(cin, title);
	cout << "\n\t--> Enter the description of description of Project : ";
	getline(cin, desc);
	string Query = "INSERT INTO Project (project_title,description,faculty_id) VALUES(\'" + title + "\',\'" + desc + "\'," + to_string(get_id()) + ");";
	if (mysql_query(SQL.conn, Query.c_str())) {
		cout << "\n Error in query : " << mysql_error(SQL.conn);
		exit(0);
	}
	else {
		cout << "\n\t\t ---------- Added PROJECT SUCCESSFULLY -------------------\n";
	}
}

void Faculty::add_student_to_project() const
{
	int id=0;
	display_only_project(id);
	//get from project project id(if no project is available the return 0)
	if (id != 0) {
		vector <int> id_s;
		if (mysql_query(SQL.conn, "SELECT s.student_id,s.Email,s.Name,s.phone_no,d.Name,s.Semester,d.department_id FROM Student s,Department d  where s.department_id=d.department_id;")) {
			cout << "Error executing query: " << mysql_error(SQL.conn) << endl;
			exit(0);
		}
		MYSQL_RES* RES = mysql_store_result(SQL.conn);
		MYSQL_ROW ROW;
		//check data of project is available or not
		if (mysql_num_rows(RES)) {
			cout << "\n+==========================================================================================================================+"
				<< "\n| Student _id  |     Email ID               |     Name             |    phone_no     |  Department_Name         | Semester |"
				<< "\n+--------------+----------------------------+----------------------+-----------------+--------------------------+----------+";
			while (ROW = mysql_fetch_row(RES)) {
				id_s.push_back(stoi(ROW[0]));
				cout << left << "\n|  " << setw(12) << ROW[0] << "|   " << setw(24) << ROW[1] << " | " << setw(20) << ROW[2] << " | " << setw(15) << ROW[3] << " | " << setw(24) << ROW[4] << setw(10) << left << " |   " << ROW[5] << " |";
			}
			mysql_free_result(RES);
			cout << "\n+==========================================================================================================================+\n\n";
			bool found = false;
			int std_id;
			do {
				cout << "\t --> Enter Id of Student in which you want to add :: ";
				cin >> std_id;
				for (int i = 0; i < id_s.size(); i++) {
					if (std_id == id_s[i]) {
						found = true;
						break;
					}
					else
						found = false;
				}
				if (!found) cout << "\n\t--(Student with this student_id is not Exist.Plz !Select another )--\n";
			} while (!found);
			string Query = "INSERT INTO Project_assign_to_Student(student_id,project_id) VALUES(" + to_string(std_id) + "," + to_string(id) + ");";
			if (mysql_query(SQL.conn, Query.c_str())) {
				cout << "\n Error in query : " << mysql_error(SQL.conn);
				exit(0);
			}
			else {
				cout << "\n\t\t ---------- ASSIGN PROJECT STUdent SUCCESSFULLY -------------------\n";
			}
		}
		else {
			cout << "\n\t <--------------- no record Available ----------------------->\n";
		}
	}
	else {
		cout << "\n\t<------------ PRoject not Available for assigning ------------------->\n";
	}
}

void Faculty::display_only_project(int& project_id) const 
{
	string Query = "SELECT * FROM Project where faculty_id=" + to_string(get_id()) + ";";
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
		bool found = false;
		do {
			cout << "\t --> Enter Id of Project in which you want to add :: ";
			cin >> project_id;
			for (int i = 0; i < id_s.size(); i++) {
				if (project_id == id_s[i]) {
					found = true;
					break;
				}
				else
					found = false;
			}
			if (!found) cout << "\n\t--(Project with this project_id is not Exist.Plz !Select another )--\n";
		} while (!found);
	}else{
		project_id = 0;
		cout << "\n\t <--------------- no record Available ----------------------->\n";
	}
}

void Faculty::display_project_details() const
{
	int id = 0;
	display_only_project(id);
	string Query="SELECT S.student_id,S.name from Project_assign_to_student PS,Student S WHERE S.student_id=PS.student_id AND PS.project_id="+to_string(id)+";";
	if (mysql_query(SQL.conn, Query.c_str())) {
		cout << "Error executing query: " << mysql_error(SQL.conn) << endl;
		exit(0);
	}
	MYSQL_RES* RES= mysql_store_result(SQL.conn);
	MYSQL_ROW ROW;
	if (mysql_num_rows(RES)) {
		cout << "\n+====================================================+"
			<< "\n| Student _id  |     Name                            |"
			<< "\n+--------------+-------------------------------------+";
		while (ROW = mysql_fetch_row(RES)) {
			cout << left << "\n|  " << setw(12) << ROW[0] << "|   " << setw(34) << ROW[1] << " | ";
		}
		mysql_free_result(RES);
		cout << "\n+====================================================+\n\n";
	}else{
		cout << "\n\t <--------------- no record Available ----------------------->\n";
	}
}

