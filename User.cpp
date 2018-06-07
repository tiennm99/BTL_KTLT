#include "User.h"

using namespace std;

inline bool operator==(User &lhs, User &rhs) {
	return lhs.username == rhs.username;
}
inline bool operator==(User &lhs, string &rhs) {
	return lhs.username == rhs;
}
inline bool operator==(string &lhs, User &rhs) {
	return lhs == rhs.username;
}
inline bool operator!=(User &lhs, User &rhs) {
	return !(lhs.username == rhs.username);
}
inline bool operator!=(User &lhs, string &rhs) {
	return !(lhs.username == rhs);
}
inline bool operator!=(string &lhs, User &rhs) {
	return !(lhs == rhs.username);
}
//-----------------------USER_LIST--------------------
int UserList::findUserByUsername(string username) {
	for (size_t i = 0; i < size; i++) {
		if (this->list[i] == username)return i;
	}
	return -1;
}

bool UserList::authentication(User& random_user) {
	int index = findUserByUsername(random_user.username);
	if (index != -1) {
		if (random_user.password == this->list[index].password) {
			random_user.role = this->list[index].role;
			return true;
		}
		else return false;
	}
	else return false;
}
void UserList::updateList(User& user) {
	int index = findUserByUsername(user.username);
	if (index == -1);
	else {
		this->list[index].username = user.username;
		this->list[index].password = user.password;
	}
}
