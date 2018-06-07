#ifndef _ADMIN_
#define _ADMIN_

#include<string>
#include<iostream>
#include<iomanip>
#include<sstream>
#include "Helper.h"
#include "User.h"

using namespace std;

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
	bool removeUser(string username, UserList &db_user_list, StudentList &db_st_list, TeacherList &db_tc_list) {
		int index = db_user_list.findUserByUsername(username);
		if (index == -1 || db_user_list.list[index].role == "admin") {
			return 0;
		}
		else {
			string s = db_user_list.list[index].role;
			db_user_list.removeFromList(index);
			if (s == "student") {
				stringstream ss;
				ss.str(username);
				int id;
				ss >> id;
				for (int i = 0; i < db_st_list.size; i++) {
					if (db_st_list.list[i].st_number == id) {
						db_st_list.removeFromList(i);
						return 1;
					}
				}
			}
			else {
				for (int i = 0; i < db_tc_list.size; i++) {
					if (db_tc_list.list[i].tc_identify == username) {
						db_tc_list.removeFromList(i);
						return 1;
					}
				}
			}
		}
	}

	bool addStudent(StudentList &db_st_list, UserList &db_user_list) {
		Student st;
		User student;
		student.role = "student";
		cout << "Input number, name, birthday, \"hometown\": (separate by comma)" << endl;
		string s;
		getline(cin, s, ',');
		student.username = student.password = s;
		istringstream(s) >> st.st_number;
		getline(cin, s, ',');
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
		tc.tc_identify = teacher.username = teacher.password = s;
		getline(cin, s, ',');
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
