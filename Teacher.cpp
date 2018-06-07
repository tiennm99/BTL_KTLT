#include "Teacher.h"
using namespace std;



CourseList* Teacher::teacherCourse(CourseList db_course_list){
	return db_course_list.findCourseByFacuty(this->tc_name);
}


bool Teacher::gradingCourse(StudentCourseList& st_join_course){
	if (st_join_course.isGrade()){
		int index;
		do{

			double spoint;
			cout << "Input student's index  to modify grade (press 0) to exit: ";
			cin >> index;
			cin.ignore(INT_MAX, '\n');
			if (index == 0) break;
			cout << "Input new grade for " << st_join_course.list[index].st_num << " : ";
			cin >> spoint;
			cin.ignore(INT_MAX, '\n');
			st_join_course.list[index].st_point.list[0] = spoint;
			
		} while (index != 0||cin.bad());
	}
	else{
		cout << "Tong ket diem: \n";
		for (int i = 0; i<st_join_course.size; ++i){
			double spoint;
			cout << st_join_course.list[i].st_num << " : ";
			cin >> spoint;
			cin.ignore(INT_MAX, '\n');
			st_join_course.list[i].st_point.list[0] = spoint;
		}
	}

	return true;
}



void Teacher::showTeacherCouser(CourseList* tc_course){
	if (tc_course->size>0){
		cout << setfill('-') << setw(115) << "-" << setfill(' ') << endl;
		cout << left << setw(5) << "STT"
			<< left << setw(20) << "Ma so khoa hoc"
			<< left << setw(15) << "Ma mon hoc"
			<< left << setw(30) << "Ten mon hoc"
			<< left << setw(10) << "Tin chi"
			<< left << setw(10) << "So luong sinh vien"
			<< endl;
		cout << setfill('-') << setw(50) << setfill(' ') << endl;
		for (size_t i = 0; i<tc_course->size; i++) {
			cout << left << setw(5) << i + 1
				<< left << setw(20) << tc_course->list[i].course_id
				<< left << setw(15) << tc_course->list[i].sub_id
				<< left << setw(30) << tc_course->list[i].sub_name
				<< left << setw(10) << tc_course->list[i].credit
				<< left << setw(10) << tc_course->list[i].total_st
				<< endl;
		}
	}
	else cout << "You haven't opened in any course" << endl;
}


bool Teacher::openCourse(CourseList& db_course_list, Course newCourse){
	if (db_course_list.isCourseExist(newCourse.course_id)) return false;
	else {
		//Course newCourse;
		db_course_list.addToCourseList(newCourse);
	}

}


///Teacher_List_Modify

TeacherList TeacherList::findTeacherByNameKeyword(string keyword[], size_t n){
	TeacherList* tList = new TeacherList();
	for (size_t i = 0; i < this->size; i++) {
		for (size_t j = 0; j < n; j++) {
			if (list[i].tc_name.find(keyword[j]) != string::npos) {
				Teacher data = list[i];
				tList->addToList(data);
				break;
			}
		}
	}
	return *tList;
}

bool TeacherList::getTeacherInfo(Teacher& tc){

	for (size_t i = 0; i < size; i++) {

		if (tc.username.compare(this->list[i].tc_identify) == 0)
		{
			tc.tc_identify = this->list[i].tc_identify;
			tc.tc_name = this->list[i].tc_name;
			tc.tc_birthday = this->list[i].tc_birthday;
			tc.tc_phone_number = this->list[i].tc_phone_number;
			tc.tc_home_town = this->list[i].tc_home_town;
			return true;
		}
	}
	return false;

}

void TeacherList::removeTeacherByNameKeyword(string keyword[], size_t n){
	for (size_t i = 0; i < size; i++) {
		for (size_t j = 0; j < n; j++) {
			if (list[i].tc_name.find(keyword[j]) != string::npos) {
				removeFromList(i);
				break;
			}
		}
	}
}

void TeacherList::updateTeacherList(Teacher data){
	for (size_t i = 0; i < size; i++) {
		if (data.tc_identify == this->list[i].tc_identify) {
			this->list[i] = data;
		}
	}
}

void TeacherList::print()
{
	cout << setw(10) << "ID" << setw(30) << "Name" << setw(15) << "Birthday" << setw(15) << "Phone Number" << setw(50) << "Hometown" << endl;
	for (int i = 0; i < this->size; i++)
	{
		cout
			<< setw(10) << this->list[i].tc_identify
			<< setw(30) << this->list[i].tc_name
			<< setw(15) << this->list[i].tc_birthday
			<< setw(15) << this->list[i].tc_phone_number
			<< setw(50) << this->list[i].tc_home_town
			<< endl;
	}
}