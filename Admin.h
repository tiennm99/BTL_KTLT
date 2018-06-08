#ifndef _ADMIN_
#define _ADMIN_

#include <iostream>
#include <iomanip>
#include <sstream>
#include <string>
#include <cctype>
#include "Helper.h"
#include "User.h"

using namespace std;

inline void to_upper(string &s) {
	for (size_t i = 0; i < s.length(); i++) {
		s[i] = toupper(s[i]);
	}
}

class Admin : public User {
public:
	Admin() {};
	~Admin() {};
	bool addUser(User user, UserList &db_user_list) {
		if (db_user_list.findUserByUsername(user.username) != -1) {
			return 0;
		}
		else {
			db_user_list.addToList(user);
			return 1;
		}
	}

	bool removeUser(string username, UserList &db_user_list, StudentList &db_st_list, TeacherList &db_tc_list, CourseList &db_course_list, StudentCourseList &db_st_course_list) {
		int index = db_user_list.findUserByUsername(username);
		if (index == -1 || db_user_list.list[index].role == "admin") {
			return 0;
		}
		else {
			string s = db_user_list.list[index].role;
			if (s == "student") {
				stringstream ss;
				ss.str(username);
				int id;
				ss >> id;
				for (size_t i = 0; i < db_st_list.size; i++) {
					if (db_st_list.list[i].st_number == id) {
						db_st_list.removeFromList(i);
						break;
					}
				}
				for (size_t i = 0; i < db_st_course_list.size; i++) {
					if (db_st_course_list.list[i].st_num == id) {
						db_st_course_list.removeFromList(i);
						break;
					}
				}
			}
			else {
				string name;
				for (size_t i = 0; i < db_tc_list.size; i++) {
					if (db_tc_list.list[i].tc_identify == username) {
						name = db_tc_list.list[i].tc_name;
						db_tc_list.removeFromList(i);
						break;
					}
				}
				for (size_t i = 0; i < db_course_list.size; i++) {
					while (db_course_list.list[i].falcuty == name) {
						db_course_list.removeFromList(i);
					}
				}
			}
			db_user_list.removeFromList(index);
			return 1;
		}
	}

	bool addStudent(StudentList &db_st_list, UserList &db_user_list) {
		Student st;
		User student;
		student.role = "student";
		cout << "Input number, name, birthday, \"hometown\": (separate by comma)" << endl;
		string s;
		getline(cin, s, ',');
		if (s == "q") {
			return 0;
		}
		student.username = student.password = s;
		istringstream iss;
		iss.str(s);
		iss >> st.st_number;
		if (iss.fail()) {
			cin.clear();
			cin.ignore(INT_MAX, '\n');
			return 0;
		}
		getline(cin, s, ',');
		to_upper(s);
		st.st_name = s;
		getline(cin, s, ',');
		st.st_birthday = s;
		getline(cin, s);
		st.st_home_town = s;
		if (addUser(student, db_user_list)) {
			db_st_list.addToList(st);
			return 1;
		}
		else {
			return 0;
		}
	}

	bool addTeacher(TeacherList &db_tc_list, UserList &db_user_list) {
		Teacher tc;
		User teacher;
		teacher.role = "teacher";
		cout << "Input identify, name, birthday, \"phone number\", \"hometown\": (separate by comma)" << endl;
		string s;
		getline(cin, s, ',');
		if (s == "q") {
			return 0;
		}
		tc.tc_identify = teacher.username = teacher.password = s;
		getline(cin, s, ',');
		to_upper(s);
		tc.tc_name = s;
		getline(cin, s, ',');
		tc.tc_birthday = s;
		getline(cin, s, ',');
		tc.tc_phone_number = s;
		getline(cin, s);
		tc.tc_home_town = s;
		if (addUser(teacher, db_user_list)) {
			db_tc_list.addToList(tc);
			return 1;
		}
		else {
			return 0;
		}
	}
};

#endif // !_ADMIN_
