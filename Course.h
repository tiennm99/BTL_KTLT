#ifndef _COURSE_
#define _COURSE_

#include<string>
#include "Helper.h"
using namespace std;

string toUpperCase(string&input);

struct Course{
	string course_id;
	string sub_id;
	string falcuty;
	string sub_name;
	int total_st;
	int max_st;
	int credit;

	Course() {};
	Course(string sub_id, string sub_name, string falcuty) {
		this->sub_id = sub_id;
		this->sub_name = sub_name;
		this->falcuty = falcuty;
	};
	~Course() {};

	void isCourseFull() {
		if (total_st > max_st) {
			this->max_st++;
		}
	}
	void CreateNewCourse(string sub_id, string sub_name, string falcuty, int total_st, int max_st, int credit){
		this->sub_id = sub_id;
		this->sub_name = sub_name;
		this->falcuty = falcuty;
		this->total_st = total_st;
		this->max_st = max_st;
		this->credit = credit;
	}
	void printCourseInfo(); // dung de ghi ra thong tin mot course ma teacher vua mo
};

//----------------------THIS IS FOR COURSE LIST--------------------
class CourseList : public arrayList<Course> {
public:
	CourseList() {};
	~CourseList() {};

	Course* findCourseById(string id);
	CourseList* findCourseByName(string name);
	CourseList* findAllCourseById(arrayList<string> id_list);
	CourseList* findAllCourseByName(arrayList<string> name_list);
	CourseList* findCourseByFacuty(string fal);
	CourseList* findAllCourseByFalcuty(arrayList<string> fal_list);
	bool isCourseExist(string id);
	bool addToCourseList(Course newCourse); // add a opened course to courseList ( course.csv )
	void addStudentToCourse(string course_id);
	void removeStudentToCourse(string course_id);
	void printCourse();
};
#endif // !_COURSE_

