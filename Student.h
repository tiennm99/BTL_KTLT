#ifndef _STUDENT_
#define _STUDENT_
#include<string>
#include<iostream>
#include<iomanip>
#include<sstream>
#include "Course.h"
#include "Helper.h"
#include "User.h"
using namespace std;
typedef struct studentCourse {
private:
	double gpa;
public:
	int st_num;
	arrayList<string> st_course;
	arrayList<int> st_point;

	studentCourse() {
		this->st_num = 0;
		this->gpa = 13.0;
	}
	bool isExist() {
		if (st_course.size == 0) {
			return false;
		}
		return true;
	}
	int getCourseNum() {
		return this->st_course.size;
	}
	bool hasEnrolled(string courseId) {
		for (size_t i = 0; i < this->getCourseNum(); i++) {
			if (this->st_course.list[i] == courseId)return true;
		}
		return false;
	}
	bool addCourse(string courseId) {
		if (hasEnrolled(courseId) == false) {
			this->st_course.addToList(courseId);
			this->st_point.addToList(-1);
			return true;
		}
		return false;
	}
	double getGPA() { return this->gpa; }
	bool setGPA(User &user, double newGPA) {
		if (user.role == "teacher") {
			this->gpa = newGPA;
			return true;
		}
		else return false;
	}
	bool isGPAsumarized() {
		if (this->gpa == 13.0)return false;
		else return true;
	}

	studentCourse& operator=(studentCourse&data) {
		this->st_num = data.st_num;
		this->st_course = data.st_course;
		this->st_point = data.st_point;
		this->gpa = data.getGPA();
		return *this;
	}
};
class StudentCourseList :public arrayList<studentCourse> {
public:
	StudentCourseList() {};
	~StudentCourseList() {};
	StudentCourseList* findStudentJoinCourse(string courseID); //tim nhung sinh vien tham gia 1 course nhat dinh (de lay diem)
	void updatePoint(/*StudentCourseList& db_st_cl, */StudentCourseList st_join_course); //cap nhat diem vao database
	bool isGrade(); //xem course hoc da cham diem chua ( StudentCourseList.st_point.list[0->size] full =-1)
	
	studentCourse findStudentCourse(int st_num) {
		studentCourse data;
		for (size_t i = 0; i < this->size; i++) {
			if (this->list[i].st_num == st_num) {
				data = this->list[i];
			}
		}
		return data;
	}

};
class Student : public User{
public:
	int st_number;// id for student's course
	string st_name;
	string st_birthday;
	string st_home_town;

	Student(int num) {
		this->st_number = num;
	};
	Student() {}
	~Student() {};
	bool getStudentCourse(StudentCourseList db_st_course_list, studentCourse& enrolledCourse);
	bool modifyBaseStudentCourse(StudentCourseList& db_st_course_list, studentCourse enrolledCourse);
	void showStudentCourse(CourseList* db_courseList, studentCourse enrolledCourse);
	bool joinCourse(studentCourse enrolledCourse, arrayList<string>&courseId, StudentCourseList& db_st_course_list, CourseList& db_course_list);
	bool cancelCourse(studentCourse enrolledCourse, arrayList<string> courseId, StudentCourseList& db_st_course_list, CourseList& db_course_list);

	CourseList* searchForCourseByName(arrayList<string> cList, CourseList db_course_list);

	Student& operator=(User u) {
		this->username = u.username;
		this->password = u.password;
		this->role = u.role;
		return *this;
	}

};
//-------------------------THIS IS FOR STUDENT LIST----------------------------
class StudentList : public arrayList<Student>{
public:
	StudentList() {};
	~StudentList() {};

	StudentList findStudentByNameKeyWord(string keyword[], size_t n);
	bool getStudentInfo(Student& st);
	void removeStudentByNameKeyWord(string keyword[], size_t n);
	void updateStudentList(Student data);
	void print();
};
#endif // !_STUDENT_

