#include "LMS.h"


void LMS::LogIn(char& choice) {
    MYSQL_RES* res; // Define a MySQL result set object
    MYSQL_ROW row; // Define a MySQL row object
    //Log in from selection table  
    string Query, table;
    //i get choice from user i serter menu function and select table according to choice
    switch (choice) {
    case '1':
        table = "Student";
        break;
    case '2':
        table = "Faculty";
        break;
    case '3':
        table = "Admin";
        break;
    default:
        cout << "\n --> Exit Successfully";
        exit(1);
    }
    // get data from mysql
    Query = "SELECT * FROM " + table;
    if (mysql_query(SQL.conn, Query.c_str())) {
        cout << "Error executing query: " << mysql_error(SQL.conn) << endl;
        exit(0);
    }
    //vector for storing ids and email to validate with entered data
    vector <int> id_s;
    vector <string> emails;
    res = mysql_store_result(SQL.conn);
    // Fetch and display the rows of the result set and store in ids and email vectors
    while ((row = mysql_fetch_row(res))) {
        id_s.push_back(stoi(row[0]));
        emails.push_back(row[2]);
    }
    //Free the result set
    mysql_free_result(res);
    int id, chance = 3;
    string email;
    cout << "\nYou are going to Log in Page ..............";
    Sleep(2000);
    system("cls");
    Sleep(1500);
    cout << "\n\n                       ------------------ ( LOGIN PAGE )-------------------             \n\n";
    // A user have only 3 chance to login LMS , whcih i store in chance variable and decrease after each loop iteration
    do
    {
        if (chance == 0) {
            cout << "\n  --( You are Unautherized Person ! You cannot log In again Now )-- ";
            Sleep(2000);
            exit(0);
        }
        cout << "    --> Enter your Email ID )---- ";
        getline(cin, email);
        cout << "    --> Enter your Id )----   ";
        cin >> id;
        cin.ignore(256, '\n');
        //cout << email << " " << id << endl;
        // Get the result set
        for (int i = 0; i < id_s.size(); i++)
        {
            cout << id_s[i] << "  " << emails[i] << endl;
            if (id == id_s[i] && email == emails[i]) {
                LogInFlag = true;
                break;
            }
        }
        if (!LogInFlag) cout << "\nUnauthorized access! You have only " << --chance << " Chance to prove your are authorized person....\n";
        else { cout << "\n --> log In Id : \n"; }
    } while (!LogInFlag);
    //after successfully log , i store id in member varaible LOgInId
    logInId = id;
    cout << "Log In Successfully !";
    //After logIn Succesfully select data from the desired table and where id is  matcch with LogIn Id 
    Query = "SELECT * FROM " + table + " WHERE " + table + "_id= " + to_string(id);
    if (mysql_query(SQL.conn, Query.c_str())) {
        cerr << "Error executing query: " << mysql_error(SQL.conn) << endl;
        exit(0);
    }
    res = mysql_store_result(SQL.conn);
    // Fetch and display the rows of the result set
    row = mysql_fetch_row(res);
    //Free the result set
    mysql_free_result(res);
    //Now acccording to choice  create Object of Classes
    if (choice == '1') {
        Student S(stoi(row[0]), row[1], row[2], row[3], stoi(row[4]), stoi(row[5]));
        student_menu(S);
    }
    else if (choice == '2') {
        Faculty F(stoi(row[0]), row[1], row[2], row[3]);
        faculty_menu(F);
    }
    else {
        Admin A(stoi(row[0]), row[1], row[2], row[3]);
        admin_menu(A);
    }

    mysql_free_result(res);
}

//validation function which get maximum value and and return only 0 to maximum value
char LMS::validation_choice(char max)
{
    char ch;
    do {
        cout << "                        --( ENTER YOUR CHIOCE HERE (0 -- " << max << ") >> > ";
        ch = _getche();
        if (ch > max || ch < '0') {
            cout << "\n  error :: Wrong Selction ! Check it and then try...\n";
            continue;
        }
        else {
            break;
        }
    } while (true);
    return ch;
}
//Menu for Admin
void LMS::admin_menu(Admin& P)
{
    P.print_data();
    do {
        cout << "\n\n                    <<< ------------------ ( AdMiN PaGe )------------------- >>>             \n\n";
        cout << "               --------( SELECT ACCORDING TO YOUR Requirement )-----------                 \n";
        cout << "  1. Manipulation in Student Information --(enter 1)--\n"
            << "   2. Manipulation in Department Information --(enter 2)--\n"
            << "   3. Manipulation Faculty Member Information --(enter 3)--\n"
            << "   4. Manipulation Course Details --(enter 4)--\n"
            << "   5. Course Allocation to Faculty Member --(enter 5)--\n"
            << "   6. Club Details --(enter 6)--\n"
            << "   7. Event Information --(enter 7)--\n"
            << "   8. Library Resource Details --(enter 8)--\n"
            << "   9. Display Feedback --(enter 9)--\n"
            << "   0. For Exit --(enter 0)--\n";
        char ch;
        ch = validation_choice('9');
        cout << "\n.............going on next page\n";
        Sleep(1500);
        system("cls");
        cout << "\n\n                     <<< ------------------ ( AdMiN PaGe )------------------- >>>            \n\n";
        switch (ch)
        {
        case '1':
            do {
                char ch2;
                cout << "\n\n               --------( Student Information )-----------                 \n";
                cout << "   1. Add Student into University --(enter 1)--\n"
                    << "   2. Update Student Data --(enter 2)--\n"
                    << "   3. Display Students --(enter 3)--\n"
                    << "   0. <<-- (For go Back)--(enter 0)\n";
                ch2 = validation_choice('3');
                if (ch2 == '1') P.add_Student();
                else if (ch2 == '2') P.Update_Student();
                else if (ch2 == '3') P.display_Students();
                else break;
            } while (true);
            break;
        case '2':
            do {
                char ch2;
                cout << "\n\n               --------( Department Information )-----------                 \n";
                cout << "   1. Add Department into University --(enter 1)--\n"
                    << "   2. Update Department Data --(enter 2)--\n"
                    << "   3. Display Department --(enter 3)--\n"
                    << "   0. <<-- (For go Back)--(enter 0)\n";
                ch2 = validation_choice('3');
                if (ch2 == '1') P.add_department();
                else if (ch2 == '2') P.update_department();
                else if (ch2 == '3') P.display_department();
                else break;
            } while (true);
            break;
        case '3':
            do {
                char ch2;
                cout << "\n\n               --------( Faculty Member Information )-----------                 \n";
                cout << "   1. Add Faculty into University --(enter 1)--\n"
                    << "   2. Update Faculty Data --(enter 2)--\n"
                    << "   3. Display Faculty --(enter 3)--\n"
                    << "   0. <<-- (For go Back)--(enter 0)\n";
                ch2 = validation_choice('3');
                if (ch2 == '1') P.add_faculty();
                else if (ch2 == '2') P.update_faculty();
                else if (ch2 == '3') P.display_faculty();
                else break;
            } while (true);
            break;
        case '4':
            do {
                char ch2;
                cout << "\n\n               --------( Course Information )-----------                 \n";
                cout << "   1. Add Course --(enter 1)--\n"
                    << "   2. Update Course Data --(enter 2)--\n"
                    << "   3. Display Course --(enter 3)--\n"
                    << "   0. <<-- (For go Back)--(enter 0)\n";
                ch2 = validation_choice('3');
                if (ch2 == '1') P.add_course();
                else if (ch2 == '2') P.update_course();
                else if (ch2 == '3') P.display_course();
                else break;
            } while (true);
            break;
        case '5':
            do {
                char ch2;
                cout << "\n\n               --------( Course Allocation to Faculty )-----------                 \n";
                cout << "   1. Course Allocation --(enter 1)--\n"
                    << "   2. Update Course Allocation Data --(enter 2)--\n"
                    << "   3. Display Course alocation --(enter 3)--\n"
                    << "   0. <<-- (For go Back)--(enter 0)\n";
                ch2 = validation_choice('3');
                if (ch2 == '1') P.course_allocate();
                else if (ch2 == '2') P.update_allocate();
                else if (ch2 == '3') P.display_allocate();
                else break;
            } while (true);
            break;
        case '6':
            do {
                char ch2;
                cout << "\n\n               --------( Club Information )-----------                 \n";
                cout << "   1. Add Club --(enter 1)--\n"
                    << "   2. Update Club Data --(enter 2)--\n"
                    << "   3. Display Club --(enter 3)--\n"
                    << "   0. <<-- (For go Back)--(enter 0)\n";
                ch2 = validation_choice('3');
                if (ch2 == '1') P.add_club();
                else if (ch2 == '2') P.update_club();
                else if (ch2 == '3') P.display_club();
                else break;
            } while (true);
            break;
        case '7':
            do {
                char ch2;
                cout << "\n\n               --------( Event Information )-----------                 \n";
                cout << "   1. Organize Event --(enter 1)--\n"
                    << "   2. Update Event Detail --(enter 2)--\n"
                    << "   3. Display Event which ocuur in future --(enter 2)--\n"
                    << "   0. <<-- (For go Back)--(enter 0)\n";
                ch2 = validation_choice('3');
                if (ch2 == '1') P.add_event();
                else if (ch2 == '2') P.update_event();
                else if (ch2 == '3') P.display_event();
                else break;
            } while (true);
            break;
        case '8':
            do {
                char ch2;
                cout << "\n\n               --------( Library Resource )-----------                 \n";
                cout << "   1. Add Library Resource  --(enter 1)--\n"
                    << "   2. Update Library Resource --(enter 2)--\n"
                    << "   3. Display Library Resource --(enter 3)--\n"
                    << "   4. Changing Library Resource Status --( enter 4)--\n"
                    << "   0. <<-- (For go Back)--(enter 0)\n";
                ch2 = validation_choice('4');
                if (ch2 == '1') P.add_library_resource();
                else if (ch2 == '2') P.update_library_resource();
                else if (ch2 == '3') P.display_library_resource();
                else if (ch2 == '4') P.change_availabilty_of_library_resource();
                else break;
            } while (true);
            break;
        case '9':
            P.display_feedback();
            break;
        default:
            exit(0);
            break;
        }
        cout << "\n";
        system("pause");
        cout << "\n--> Going to Desired Page --> .......";
        Sleep(2000);
        system("cls");
    } while (true);
}
//Menu whcih display only Faculty.
void LMS::faculty_menu(Faculty& P)
{
    P.print();
    do {
        cout << "\n\n                     <<<  ------------------ ( fAcUltY PaGe )------------------- >>>             \n\n";
        cout << "\n\n               --------( SELECT ACCORDING TO YOUR Requirement )-----------                 \n";
        cout << "   1. Display Course which I teach --(enter 1)--\n"
            << "   2. Assignment Maintanance of courses --(enter 2)-- \n"
            << "   3. Attendance Maintainance --( enter 3)--\n"
            << "   4. Grade Manage here --(enter 4)--\n"
            << "   5. Supervisor Project/Research  --(enter 5)--\n"
            << "   6. Display Events --(enter 6)--\n"
            << "   7. Deisplay Library Resources --(enter 7)--\n"
            << "   0. For Exit --(enter 0)--\n";
        char ch;
        ch = validation_choice('8');
        char ch2;
        switch (ch)
        {
        case '1':
            P.display_AllocaionCourse();
            break;
        case '2':
            cout << "\n\n               --------( Assignment Related Detail )-----------                 \n";
            cout << "   1. Add Assignment of Course --(enter 1)--\n"
                << "   2. Edit Assignment of Course --(enter 2)--\n"
                << "   3. Display all Assignment --(enter 3)-- \n"
                << "   0. For Exit --(enter 0)--\n";
            ch2 = validation_choice('3');
            if (ch2 == '1') P.add_assignment();
            else if (ch2 == '2') P.update_assignment();
            else if (ch2 == '3') P.display_assignment();
            else break;
            break;
        case '3':
            cout << "\n\n               --------( Attendeance Related Detail )-----------                 \n";
            cout << "   1. Add Attendence of Student --(enter 1)--\n"
                << "   2. Edit Attendence of Student --(enter 2)--\n"
                << "   3. Display Attendance --(enter 3)-- \n"
                << "   0. For Exit --(enter 0)--\n";
            ch2 = validation_choice('3');
            if (ch2 == '1') P.add_attendance();
            else if (ch2 == '2') P.update_attendance();
            else if (ch2 == '3') P.display_attendance();
            else break;
            break;
        case '4':
            cout << "\n\n               --------( Grade Manages Here )-----------                 \n";
            cout << "   1. Add grade of Student --(enter 1)--\n"
                << "   2. Edit grade of Student --(enter 2)--\n"
                << "   3. Display grades --(enter 3)-- \n"
                << "   0. For Exit --(enter 0)--\n";
            ch2 = validation_choice('3');
            if (ch2 == '1') P.add_grade();
            else if (ch2 == '2') P.update_grade();
            else if (ch2 == '3') P.display_grade();
            else break;
            break;
        case '5':
            cout << "\n\n               --------( Project Manages Here )-----------                 \n";
            cout << "   1. Add Project  --(enter 1)--\n"
                << "   2. ASSIGN to Student --(enter 2)--\n"
                << "   3. Display Project --(enter 3)-- \n"
                << "   0. For Exit --(enter 0)--\n";
            ch2 = validation_choice('3');
            if (ch2 == '1') P.add_project();
            else if (ch2 == '2') P.add_student_to_project();
            else if (ch2 == '3') P.display_project_details();
            else break;
            break;
        case '6':
            P.display_event();
            break;
        case '7':
            P.display_library_resource();
            break;
        default:
            exit(0);
            break;
        }        //
        cout << "\n";
        system("pause");
        cout << "\n--> Going to Desired Page --> .......";
        Sleep(2000);
        system("cls");
    } while (true);
}
//Menu which display only Student.
void LMS::student_menu(Student& P)
{
    //P.print();
    cout << "\n\n                     <<< ------------------ ( sTuDenT PaGe )------------------- >>>            \n\n";
    do {
        cout << "\n\n               --------( SELECT ACCORDING TO YOUR Requirement )-----------                 \n";
        cout << "   1. Courses Related Details --(enter 1)--\n"
            << "   2. Clubs Details --(enter 2)--\n"
            << "   3. Display Events Infromation --(enter 3)--\n"
            << "   4. Library Resources Infromation --(enter 4)--\n"
            << "   5. Project/ Research Details --(enter 5)--\n"
            << "   6. Grade of All Sibject --(enter 6)--\n"
            << "   7. Give feeback --(enter 7)--\n"
            << "   8. Print All Data --(enter 8)--\n"
            << "   0. <-- (For Go back) --(enter 0)--\n";
        char ch;
        ch = validation_choice('8');
        cout << "\n.............going on next page\n";
        Sleep(1500);
        system("cls");
        cout << "\n\n                     <<< ------------------ ( sTuDenT PaGe )------------------- >>>            \n\n";
        switch (ch)
        {
        case '1':
            do {
                char ch2;
                cout << "\n\n               --------( Courses Related Details )-----------                 \n";
                cout << "   1. Enroll in Course --(enter 1)--\n"
                    << "   2. Display Register Courses --(enter 2)--\n"
                    << "   3. Display Attendence Status --(enter 3)--\n"
                    << "   4. Submit Assignment --(enter 4)--\n"
                    << "   0. <<-- (For go Back)--(enter 0)\n";
                ch2 = validation_choice('4');
                if (ch2 == '1') P.enrollment_in_course();
                else if (ch2 == '2') P.enrolled_course();
                else if (ch2 == '3') P.display_attendence();
                else if (ch2 == '4') P.submit_assignment();
                else break;
            } while (true);
            break;
        case '2':
            do {
                char ch2;
                cout << "\n\n               --------( Clubs Details )-----------                 \n";
                cout << "   1. Join Club --(enter 1)--\n"
                    << "   2. Display Join Club --(enter 2)--\n"
                    << "   3. Display All Club list --(enter 3)--\n"
                    << "   0. <<-- (For go Back)--(enter 0)\n";
                ch2 = validation_choice('3');
                if (ch2 == '1') P.join_club();
                else if (ch2 == '2') P.display_joined_club();
                else if (ch2 == '3') P.display_club();
                else break;
            } while (true);
            break;
        case '3':
            P.display_event();
            break;
        case '4':
            P.display_library_resource();
            break;
        case '5':
            do {
                char ch2;
                cout << "\n\n               --------( Project / Research Details )-----------                 \n"
                    << "   1. Display Assign Project/Research --(enter 2)--\n"
                    << "   0. <<-- (For go Back)--(enter 0)\n";
                ch2 = validation_choice('1');
                if (ch2 == '1') P.display_assign_project();
                else break;
            } while (true);
            break;
        case '6':
            P.display_grade();
            break;
        case '7':
            P.feedback();
            break;
        case '8':
            P.print();
            break;
        default:
            exit(0);
            break;
        }
        cout << "\n";
        system("pause");
        cout << "\n--> Going to Desired Page --> .......";
        Sleep(2000);
        system("cls");
    } while (true);
}

void LMS::starter_menu()
{
    cout << endl
        << "\t\t\t|||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||\n"
        << "\t\t\t=                                                ___                                  =\n"
        << "\t\t\t=                            |       |\\    /|   |                                     =\n"
        << "\t\t\t=                            |       | \\  / |   |__                                   =\n"
        << "\t\t\t=                            |       |  \\/  |      |                                  =\n"
        << "\t\t\t=                            |___    |      |    __|                                  =\n"
        << "\t\t\t=                     ----( Learning Managment System)----                            =\n"
        << "\t\t\t=          SUBMITTED BY::                                                             =\n"
        << "\t\t\t=                         MEHBOOB ALAM --(2023-SE_07)--                               =\n"
        << "\t\t\t=                         ABDUL RAFEH  --(2023-SE-26)--                               =\n"
        << "\t\t\t=                                                                                     =\n"
        << "\t\t\t|||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||\n" << endl << endl;
    //Show Starter menu and give choice 
    cout << "               --------( SELECT ACCORDING TO YOUR STATUS )-----------                 \n";
    cout << "   1. You are a Student --(enter 1)--\n"
        << "   2. You are a Faculty Member --(enter 2)--\n"
        << "   3. You are a admin --(enter 3)--\n"
        << "   0. For Exit --(enter 0)--\n";
    //call a validation function which get maximum value and and return only 0 to maximum value
    char ch = validation_choice('3');
    // Call LogIn Function
    LogIn(ch);
}


