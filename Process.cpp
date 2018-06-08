#include "Process.h"
#include "Student.h"
#include "Teacher.h"
#include "DBHelper.h"
#include "Admin.h"
#include <iostream>
#include <string>
#include <sstream>

using namespace std;

bool startProgram(User& random_user, UserList user_list) {
	cout << "\t\t\t" << "+++++++++++++++++++++++++++++++++++++|\n\n";
	cout << "\t\t\t" << "|   Welcome to student manager site  |\n\n";
	cout << "\t\t\t" << "+++++++++++++++++++++++++++++++++++++|\n\n\n";
	while (true) {

		cout << "Username (Type q to exit): ";
		cin >> random_user.username;
		cout << "Password (Type q to exit): ";
		cin >> random_user.password;
		cin.ignore(INT_MAX, '\n');
		if (random_user.username == "q" && random_user.password == "q") {
			return false;
		}
		if (user_list.authentication(random_user)) {
			return true;
		}
		else {
			cout << "===================" << endl;
			cout << "Login Failed" << endl;
			bool rep = true;
			do {
				char option;
				cout << "Continue? (Y/N) ";
				cin >> option;
				cin.ignore(INT_MAX, '\n');
				switch (option) {
				case 'Y':rep = false; break;
				case 'N':return false;
				default: {
							 cout << "Error: option must be Y or N " << endl;
							 break;
				}
				}
				system("cls");
			} while (rep);
		}
	}
}
bool studentMenu(Student& st, StudentCourseList db_st_course_list, CourseList db_course_list, UserList user_list) {
	while (st.isLogin() == true) {
		cout << setfill('-') << setw(50) << "-" << "Student: " << st.st_number << setw(50) << "-" << endl;
		cout << setfill(' ') << setw(30) << left << "1. Change Password [cp]" << setw(30) << left << "2. View my courses [vc]" << setw(30) << left << "3. Search courses[sc]" << setw(30) << left << "4. Join course [jc]" << endl;
		cout << setw(30) << left << "5. Cancel course [xc]" << setw(30) << left << "6. Log out [lo]" << setw(30) << left << "7. Help [h]" << endl;
		cout << "Your command (press [e] to quit program): ";
		string command;
		stringstream ss;
		string agv;
		arrayList<string> agvList;
		getline(cin, command);
		ss.str(command);
		do{
			ss >> agv;
			if (ss.fail() || agv == "") {
				break;
			}
			else agvList.addToList(agv);
		} while (true);
		if (agvList.list[0] == "e" && agvList.size == 1) return false;
		if (studentProcess(st, user_list, db_st_course_list, db_course_list, agvList) == true) {

		}
		else {
			cout << "Error: command not found" << endl;
		}
	}
	return true;
}
bool teacherMenu(Teacher& tc, StudentCourseList& db_st_course_list, CourseList& db_course_list, UserList user_list){

	while (tc.isLogin() == true){

		cout << setfill('-') << setw(30) << "-" << "Lecturer: " << tc.tc_name << setw(50) << "-" << endl;

		cout << "1. Change Password [cp (new password) ]\n";
		cout << "2. Open a course [oc]\n";
		cout << "3. Grading student's course [gc]\n";
		//cout << "4. Modify grade [mg]\n";
		cout << "4. Log out [lo]\n";
		cout << "5. Help [h]" << endl;
		cout << "Your command (press [e] to quit program): ";
		string command;
		stringstream ss;
		string agv;
		arrayList<string> agvList;
		getline(cin, command);
		ss.str(command);
		do{
			ss >> agv;
			if (ss.fail() || agv == "") {
				break;
			}
			else agvList.addToList(agv);
		} while (true);
		if (agvList.list[0] == "e" && agvList.size == 1) return false;
		if (teacherProcess(tc, user_list, db_st_course_list, db_course_list, agvList) == true) {

		}
		else {
			cout << "Error: command not found" << endl;
		}
	}
	//system("cls"); // xoa console menu sau moi lan xong 1 thao tac
	return true;
}

bool studentProcess(Student&st, UserList& user_list, StudentCourseList&db_st_course_list, CourseList db_course_list, arrayList<string> agvList) {
	if (agvList.list[0] == "cp") {
		if (agvList.size == 2) {
			string newPassword = agvList.list[1];
			st.changePassword(newPassword);
			user_list.updateList(st);
			return true;
		}
		else if (agvList.size == 1){
			string newPassword;
			cout << "Your new password: ";
			cin >> newPassword;
			cin.ignore(INT_MAX, '\n');
			st.changePassword(newPassword);
			user_list.updateList(st);
			cout << "CHANGE PASSWORD SUCCESSFULLY" << endl;
			return true;
		}
	}
	else if (agvList.list[0] == "vc") {
		system("cls");
		studentCourse enrolledCourse;
		st.getStudentCourse(db_st_course_list, enrolledCourse);
		st.showStudentCourse(&db_course_list, enrolledCourse);
		return true;
	}
	else if (agvList.list[0] == "sc") {
		if (agvList.list[1] == "-n") {
			if (agvList.size > 2) {
				agvList.removeFromList(0);
				agvList.removeFromList(0);
				CourseList* cList = db_course_list.findAllCourseByName(agvList);
				if (cList->size == 0) {
					cout << "Error: Failed to find data" << endl;
				}
				else {
					system("cls");
					cList->printCourse();
				}
			}
			else if (agvList.size == 2) {
				cout << "Course to search: ";
				string course_name;
				getline(cin, course_name);
				CourseList* cList = db_course_list.findCourseByName(course_name);
				if (cList->size == 0) {
					cout << "Error: Failed to find data" << endl;
				}
				else {
					system("cls");
					cList->printCourse();
				}
			}
			return true;
		}
		else if (agvList.list[1] == "-f") {
			if (agvList.size > 2) {
				agvList.removeFromList(0);
				agvList.removeFromList(0);
				CourseList* cList = db_course_list.findAllCourseByFalcuty(agvList);
				cList->printCourse();
			}
			else if (agvList.size == 2) {
				cout << "Falcuty to search: ";
				string fal_name;
				getline(cin, fal_name);
				CourseList* cList = db_course_list.findCourseByFacuty(fal_name);
				cList->printCourse();
			}
			return true;
		}
	}
	else if (agvList.list[0] == "jc") {
		studentCourse enrolledCourse;
		st.getStudentCourse(db_st_course_list, enrolledCourse);
		if (agvList.size > 1) {
			agvList.removeFromList(0);
			if (st.joinCourse(enrolledCourse, agvList, db_st_course_list, db_course_list) == false) {
				if (agvList.size != 0) {
					cout << "Error: Failed to join in ";
					for (size_t i = 0; i < agvList.size; i++) {
						cout << "'" << agvList.list[i] << "'";
					}
					cout << ". You has already joined the course or it is not opened." << endl;
				}
			}
			else {
				cout << "Your have successfully joined the courses." << endl;
			}
		}
		else if (agvList.size == 1) {
			string courseId;
			arrayList<string> join_course;
			cout << "Course to join: ";
			cin >> courseId;
			cin.ignore(INT_MAX, '\n');
			join_course.addToList(courseId);
			if (st.joinCourse(enrolledCourse, join_course, db_st_course_list, db_course_list) == false) {
				cout << "Error: Failed to join in ";
				for (size_t i = 0; i < join_course.size; i++) {
					cout << join_course.list[i] << " | ";
				}
				cout << ". You has already joined the course or it is not opened." << endl;
			}
			else {
				cout << "Your have successfully joined the courses." << endl;
			}
		}
		return true;
	}
	else if (agvList.list[0] == "xc") {
		studentCourse enrolledCourse;
		st.getStudentCourse(db_st_course_list, enrolledCourse);
		if (agvList.size > 1) {
			agvList.removeFromList(0);
			for (size_t i = 0; i < agvList.size; i++) {
				if (enrolledCourse.hasEnrolled(agvList.list[i]) == false) {
					cout << "Error: You have not joined " << agvList.list[i] << endl;
					cout << endl;
				}
				else {
					cout << "You have canceled join " << agvList.list[i] << endl;
				}
			}
			st.cancelCourse(enrolledCourse, agvList, db_st_course_list, db_course_list);
		}
		else if (agvList.size == 1) {
			string courseId;
			arrayList<string> cancel_course;
			cout << "Course to cancel: ";
			cin >> courseId;
			cin.ignore(INT_MAX, '\n');
			cancel_course.addToList(courseId);
			for (size_t i = 0; i < agvList.size; i++) {
				if (enrolledCourse.hasEnrolled(cancel_course.list[i]) == false) {
					cout << "Error: You have not joined " << agvList.list[i] << endl;
					cout << endl;
				}
				else {
					cout << "You have canceled join " << agvList.list[i] << endl;
				}
			}
			st.cancelCourse(enrolledCourse, cancel_course, db_st_course_list, db_course_list);
		}
		return true;
	}
	else if (agvList.list[0] == "lo") {
		st.logout();
		system("cls");
		return true;
	}
	else if (agvList.list[0] == "h") {
		if (agvList.size == 1) {
			system("cls");
			cout << setw(40) << left << "Description " << setw(10) << left << "Command" << setw(10) << left << "Argument list" << endl;
			cout << setw(100) << setfill('-') << "-" << setfill(' ') << endl;
			cout << setw(40) << left << "Change password" << setw(10) << left << "cp" << setw(10) << left << "<new password> (optional)" << endl;
			cout << setw(40) << left << "View all course" << setw(10) << left << "vc" << setw(10) << left << "none" << endl;
			cout << setw(40) << left << "Search coures by keyword" << setw(10) << left << "sc -n" << setw(10) << left << "<list of course's name> (optional)" << endl;
			cout << setw(40) << left << "Search coures by falcuty" << setw(10) << left << "sc -f" << setw(10) << left << "<list of falcuty's name> (optional)" << endl;
			cout << setw(40) << left << "Cancel course" << setw(10) << left << "xc" << setw(10) << left << "<list of course id> (optional)" << endl;
			cout << setw(40) << left << "Join course" << setw(10) << left << "jc" << setw(10) << left << "<list of course id> (optional)" << endl;
			cout << setw(100) << setfill('=') << "=" << setfill(' ') << endl;
			cout << "Press any key to exit." << endl;
			getchar();
			system("cls");
			return true;
		}
	}
	return false;
}
bool teacherProcess(Teacher& tc, UserList& user_list, StudentCourseList& db_st_course_list, CourseList& db_course_list, arrayList<string> agvList) {

#pragma region ChangePass
	if (agvList.list[0] == "cp"){
		string newPassword;
		if (agvList.size == 2){
			newPassword = agvList.list[1];
		}
		else if (agvList.size == 1){
			cout << "Input your new password: ";
			cin >> newPassword;
			cin.ignore(INT_MAX, '\n');
		}
		tc.changePassword(newPassword);
		user_list.updateList(tc);
		cout << "CHANGE PASSWORD SUCCESSFULLY\n";
		return true;
	}
#pragma endregion
	
#pragma region OpenCourse
	else if (agvList.list[0] == "oc"){
		CourseList* temp = new CourseList();
		temp = db_course_list.findCourseByFacuty(tc.tc_name);
		if (temp->size > 5){
			cout << "You has open 5 courses for  this term so you cannot open more course.\n";
			return true;
		}
		else{
			string newCourse_sub_id; //ms viet tat mon hoc
			string newCourse_class_id; //nhom lop
			string newCourse_id; //ms mon hoc
			string newCourse_name; //ten mon hoc
			int newCourse_max; //so luong sv toi da
			int newCourse_ncredit; //tin chi
			do{
				cout << "Input new sub_course ID you want to open: ";
				cin >> newCourse_sub_id;
				cin.ignore(INT_MAX, '\n');
				cout << "Input class group: ";
				cin >> newCourse_class_id;
				cin.ignore(INT_MAX, '\n');
				//newCourse_sub_id=toUpperCase(newCourse_sub_id);
				//newCourse_class_id = toUpperCase(newCourse_class_id);
				newCourse_id = newCourse_sub_id + "_" + newCourse_class_id;
				if (db_course_list.isCourseExist(newCourse_id)){
					cout << "You can not open an existed course. Try again! \n";
				}
			} while (db_course_list.isCourseExist(newCourse_id));
			cout << "Input new course details.\n";
			cout << "Input course name: "; getline(cin, newCourse_name);

			do{
				cout << "Input student number limitation (at least 10) : "; cin >> newCourse_max;
				cin.clear();
				cin.ignore(INT_MAX, '\n');
				if (newCourse_max < 10 || cin.bad() || newCourse_max != (int)newCourse_max){
					cout << "Invalid input.Try again!\n";
				}
			} while (cin.bad() || newCourse_max < 10 || newCourse_max != (int)newCourse_max);
			do{
				cout << "Input course's credit number (1-6): "; cin >> newCourse_ncredit;
				cin.clear();
				cin.ignore(INT_MAX, '\n');

				if (!cin.good() || newCourse_ncredit<1 || newCourse_ncredit>6 || newCourse_ncredit != (int)newCourse_ncredit){
					cout << "Invalid input.Try again!\n";
				}
			} while (cin.bad() || newCourse_ncredit < 1 || newCourse_ncredit != (int)newCourse_ncredit);

			Course newCourse(newCourse_sub_id, newCourse_name, tc.tc_name);
			newCourse.course_id = newCourse_id;
			newCourse.total_st = 0;
			newCourse.max_st = newCourse_max;
			newCourse.credit = newCourse_ncredit;

			
			cout << "SUCESSFULLY OPEN A NEW COURSE : \n";
			newCourse.printCourseInfo();

			cout << "Date created: " << endl;
			std::time_t t = std::time(0);   // get time now
			std::tm* now = std::localtime(&t);
			std::cout << (now->tm_year + 1900) << '-' << (now->tm_mon + 1) << '-' << now->tm_mday << "\n";
			cin.ignore(INT_MAX, '\n');
			db_course_list.addToCourseList(newCourse);
			return true;

		}//else right

	}//end br

#pragma endregion

#pragma region Grading

	else if (agvList.list[0] == "gc"){
		CourseList* tc_open_course = new CourseList();
		tc_open_course = tc.teacherCourse(db_course_list); //lay danh sach nhung course ma teacher da mo
		StudentCourseList* data = new StudentCourseList();
		cout << "\nYour opened course: \n";
		tc.showTeacherCouser(tc_open_course);
		if (tc_open_course->size == 0){
			cout << "Try opening a course in main menu ! \n";
			return true;
		}
		int option;
		cout << "\n\nChose course to grade or press 0  to exit: ";
		cin >> option;
		cin.ignore(INT_MAX, '\n');
		if (option == 0){
			return true;
		}
		else if (option != 0){
			for (size_t i = 0; i < tc_open_course->size; i++){
				if (option == i + 1){
					data = db_st_course_list.findStudentJoinCourse(tc_open_course->list[i].course_id); //lay danh sach sinh vien + diem ma sinh vien tham gia course;
					cout << endl;
					cout << setw(40) << right << "__Danh Sach Sinh Vien Da Dang Ky__\n" << endl;
					cout << setw(5) << left << "STT";
					cout << setw(30) << left << "MSSV";
					cout << setw(20) << right << "Diem\n";
					cout << setfill('-');
					cout << setw(55) << "-" << endl;
					cout << setfill(' ');
					for (size_t j = 0; j < data->size; j++){
						cout << setw(5) << left << j + 1;
						cout << setw(30) << left << data->list[j].st_num;
						cout << setw(20) << right << data->list[j].st_point.list[0] << endl;
					}
					tc.gradingCourse(*data);
					db_st_course_list.updatePoint(*data);

					cout << "Successfully modify student's grade!\n";
					cout << "Changes preview: \n";
					//*data = db_st_course_list.findStudentJoinCourse(tc_open_course->list[i].course_id); //lay danh sach sinh vien + diem ma sinh vien tham gia course;
					cout << endl;
					//cout << setw(40) << right << "__Danh Sach Sinh Vien Da Dang Ky__\n" << endl;
					cout << setw(5) << left << "STT";
					cout << setw(30) << left << "MSSV";
					cout << setw(20) << right << "Diem\n";
					cout << setfill('-');
					cout << setw(55) << "-" << endl;
					cout << setfill(' ');
					for (size_t j = 0; j < data->size; j++){
						cout << setw(5) << left << j + 1;
						cout << setw(30) << left << data->list[j].st_num;
						cout << setw(20) << right << data->list[j].st_point.list[0] << endl;
					}
				}
			}
			return true;
		}

	} //end else if

#pragma endregion

#pragma region logout
	else if (agvList.list[0] == "lo") {
		tc.logout();
		system("cls");
		return true;
	}
#pragma endregion

#pragma region help
	else if (agvList.list[0] == "h") {
		if (agvList.size == 1) {
			system("cls");
			cout << setw(40) << left << "Description " << setw(10) << left << "Command" << setw(10) << left << "Argument list" << endl;
			cout << setw(100) << setfill('-') << "-" << setfill(' ') << endl;
			cout << setw(40) << left << "Change password" << setw(10) << left << "cp" << setw(10) << left << "<new password> (optional)" << endl;
			cout << setw(40) << left << "Opent a course" << setw(10) << left << "oc" << setw(10) << left << "none" << endl;
			cout << setw(40) << left << "Grading a course" << setw(10) << left << "gc" << setw(10) << left << "<list of course's name> (optional)" << endl;
			//cout << setw(40) << left << "Modify grade" << setw(10) << left << "mg" << setw(10) << left << "<list of course's name> (optional)" << endl;
			cout << setw(100) << setfill('=') << "=" << setfill(' ') << endl;
			cout << "Press any key to exit." << endl;
			getchar();
			system("cls");
			return true;
		}
	}
#pragma endregion

}

#pragma region Tien

bool adminMenu(Admin& ad, StudentList& db_st_list, TeacherList& db_tc_list, UserList& user_list)
{
	while (ad.isLogin() == true) {
		cout << setw(40) << setfill('-') << "-" << "ADMIN" << setw(40) << setfill('-') << "-" << endl;
		cout << setw(40) << setfill(' ') << left << "Change password" << "[cp]" << endl;
		cout << setw(40) << setfill(' ') << left << "Show teacher" << "[t]" << endl;
		cout << setw(40) << setfill(' ') << left << "Show student" << "[s]" << endl;
		cout << setw(40) << setfill(' ') << left << "Add Teacher" << "[at]" << endl;
		cout << setw(40) << setfill(' ') << left << "Add Student" << "[as]" << endl;
		cout << setw(40) << setfill(' ') << left << "Remove User" << "[ru]" << endl;
		cout << setw(40) << setfill(' ') << left << "Search Teacher by name" << "[st]" << endl;
		cout << setw(40) << setfill(' ') << left << "Search Student by name" << "[ss]" << endl;
		cout << setw(40) << setfill(' ') << left << "Log out" << "[lo]" << endl;
		cout << setw(40) << setfill(' ') << left << "Help" << "[h]" << endl;
		cout << "Your command (press [e] to quit program): ";
		string command;
		stringstream ss;
		string agv;
		arrayList<string> agvList;
		getline(cin, command);
		ss.str(command);
		do {
			ss >> agv;
			if (ss.fail() || agv == "") {
				break;
			}
			else agvList.addToList(agv);
		} while (true);
		if (agvList.list[0] == "e" && agvList.size == 1) return false;
		if (adminProcess(ad, user_list, db_st_list, db_tc_list, agvList) == true) {

		}
		else {
			cout << "Error: command not found" << endl;
		}
	}
	return true;
}

bool adminProcess(Admin& ad, UserList& user_list, StudentList& db_st_list, TeacherList& db_tc_list, arrayList<string> agvList) {
	if (agvList.list[0] == "cp") {
		if (agvList.size == 2) {
			string newPassword = agvList.list[1];
			ad.changePassword(newPassword);
			user_list.updateList(ad);
			return true;
		}
		else if (agvList.size == 1) {
			string newPassword;
			cout << "Your new password: ";
			cin >> newPassword;
			cin.ignore(INT_MAX, '\n');
			ad.changePassword(newPassword);
			user_list.updateList(ad);
			cout << "CHANGE PASSWORD SUCCESSFULLY" << endl;
			return true;
		}
	}
	else if (agvList.list[0] == "as")
	{
		if (ad.addStudent(db_st_list, user_list)) {
			cout << "Add Student successful!" << endl;
		}
		else {
			cout << "Add Student unsuccessful!\nMay be error in your input or the same username have exist." << endl;
		}
		return true;
	}
	else if (agvList.list[0] == "at")
	{
		if (ad.addTeacher(db_tc_list, user_list)) {
			cout << "Add Teacher successful!" << endl;
		}
		else {
			cout << "Add Teacher unsuccessful! May be the same username have exist." << endl;
		}
		return true;
	}
	else if (agvList.list[0] == "ss") {
		if (agvList.size > 1) {
			agvList.removeFromList(0);
			for (size_t i = 0; i < agvList.size; i++) {
				to_upper(agvList.list[i]);
			}
			StudentList sList = db_st_list.findStudentByNameKeyWord(agvList.list, agvList.size);
			if (sList.size == 0) {
				cout << "Error: Failed to find data" << endl;
			}
			else {
				system("cls");
				sList.print();
			}
		}
		else if (agvList.size == 1) {
			cout << "Students to search: ";
			string command;
			stringstream ss;
			string st_name;
			arrayList<string> st_list;
			getline(cin, command);
			ss.str(command);
			do {
				ss >> st_name;
				if (ss.fail() || st_name == "") {
					break;
				}
				else {
					to_upper(st_name);
					st_list.addToList(st_name);
				}
			} while (true);
			StudentList sList = db_st_list.findStudentByNameKeyWord(st_list.list, st_list.size);
			if (sList.size == 0) {
				cout << "Error: Failed to find data" << endl;
			}
			else {
				system("cls");
				sList.print();
			}
		}
		return true;
	}
	else if (agvList.list[0] == "st") {
		if (agvList.size > 1) {
			agvList.removeFromList(0);
			for (size_t i = 0; i < agvList.size; i++) {
				to_upper(agvList.list[i]);
			}
			TeacherList tList = db_tc_list.findTeacherByNameKeyword(agvList.list, agvList.size);
			if (tList.size == 0) {
				cout << "Error: Failed to find data" << endl;
			}
			else {
				system("cls");
				tList.print();
			}
		}
		else if (agvList.size == 1) {
			cout << "Teachers to search: ";
			string command;
			stringstream ss;
			string tc_name;
			arrayList<string> tc_list;
			getline(cin, command);
			ss.str(command);
			do {
				ss >> tc_name;
				if (ss.fail() || tc_name == "") {
					break;
				}
				else {
					to_upper(tc_name);
					tc_list.addToList(tc_name);
				}
			} while (true);
			TeacherList tList = db_tc_list.findTeacherByNameKeyword(tc_list.list, tc_list.size);
			if (tList.size == 0) {
				cout << "Error: Failed to find data" << endl;
			}
			else {
				system("cls");
				tList.print();
			}
		}
		return true;
	}
	else if (agvList.list[0] == "ru") {
		if (agvList.size == 1) {
			cout << "Input list of usernames to remove:" << endl;
			string input;
			stringstream ss;
			string username;
			arrayList<string> removeList;
			getline(cin, input);
			ss.str(input);
			do {
				ss >> username;
				if (ss.fail() || username == "") {
					break;
				}
				else removeList.addToList(username);
			} while (true);
			arrayList<string> remove_unsuccess;
			for (size_t i = 1; i < removeList.size; i++) {
				if (ad.removeUser(removeList.list[i], user_list, db_st_list, db_tc_list) == 1) {

				}
				else {
					remove_unsuccess.addToList(removeList.list[i]);
				}
			}
			if (remove_unsuccess.size == 0) {
				cout << "Remove all user successful!" << endl;
			}
			else {
				cout << "Some user remove unsuccessful! That is:" << endl;
				for (size_t j = 0; j < remove_unsuccess.size; j++) {
					cout << j + 1 << ".\t" << remove_unsuccess.list[j] << endl;
				}
				cout << "Other user remove successful!" << endl;
			}
			return true;
		}
		else
		{
			arrayList<string> remove_unsuccess;
			for (size_t i = 1; i < agvList.size; i++) {
				if (ad.removeUser(agvList.list[i], user_list, db_st_list, db_tc_list) == 1) {
					
				}
				else {
					remove_unsuccess.addToList(agvList.list[i]);
				}
			}
			if (remove_unsuccess.size == 0) {
				cout << "Remove all user successful!" << endl;
			}
			else {
				cout << "Some user remove unsuccessful! That is:" << endl;
				for (size_t j = 0; j < remove_unsuccess.size; j++) {
					cout << j + 1 << ".\t" << remove_unsuccess.list[j] << endl;
				}
				cout << "Other user remove successful!" << endl;
			}
			return true;
		}
	}
	else if (agvList.list[0] == "h") {
		if (agvList.size == 1) {
			system("cls");
			cout << setw(40) << setfill('-') << "-" << "HELP (ADMIN)" << setw(40) << setfill('-') << "-" << endl << endl;
			cout << setw(40) << setfill(' ') << left << "Change password" << "[cp]" << endl;
			cout << "Input <cp> <newpassword> to change. Or input <cp> then input <newpassword>." << endl << endl;
			cout << setw(40) << setfill(' ') << left << "Show teacher" << "[t]" << endl;
			cout << "Show all teacher in database." << endl << endl;
			cout << setw(40) << setfill(' ') << left << "Show student" << "[s]" << endl;
			cout << "Show all student in database." << endl << endl;
			cout << setw(40) << setfill(' ') << left << "Add Teacher" << "[at]" << endl;
			cout << "Input <at> then input teacher's informations." << endl << endl;
			cout << setw(40) << setfill(' ') << left << "Add Student" << "[as]" << endl;
			cout << "Input <as> then input student's informations." << endl << endl;
			cout << setw(40) << setfill(' ') << left << "Remove User" << "[ru]" << endl;
			cout << "Input <ru> then input list of usernames. Or input <ru> <list of username you want to remove (separate by space)>." << endl << endl;
			cout << setw(40) << setfill(' ') << left << "Search Teacher by name" << "[st]" << endl;
			cout << "Input <st> <list of teachers' name> to search. Or input <st> then input <name>." << endl;
			cout << "Input as this format <identify, name, birthday, \"phone number\", \"hometown\"> (separate by comma):" << endl << endl;
			cout << setw(40) << setfill(' ') << left << "Search Student by name" << "[ss] <name>" << endl;
			cout << "Input <ss> <list of students' name> to search. Or input <ss> then input <name>." << endl;
			cout << "Input as this format <number, name, birthday, \"hometown\"> (separate by comma):" << endl << endl;
			cout << setw(40) << setfill(' ') << left << "Log out" << "[lo]" << endl;
			cout << "Input <lo> to log out. (Then you can log in as another user)." << endl << endl;
			cout << "Input anything to return." << endl;
			getchar();
			cin.clear();
			cin.ignore(INT_MAX, '\n');
			system("cls");
			return true;
		}
	}
	else if (agvList.list[0] == "t") {
		db_tc_list.print();
		cout << "Input anything to return." << endl;
		getchar();
		system("cls");
		cin.clear();
		cin.ignore(INT_MAX, '\n');
		return true;
	}
	else if (agvList.list[0] == "s") {
		db_st_list.print();
		cout << "Input anything to return." << endl;
		getchar();
		system("cls");
		cin.clear();
		cin.ignore(INT_MAX, '\n');
		return true;
	}
	else if (agvList.list[0] == "lo") {
		ad.logout();
		system("cls");
		return true;
	}
	return false;
}

#pragma endregion