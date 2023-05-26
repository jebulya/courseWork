#pragma once
#include <string>
#include <vector>
#include "Human.h"
#include "MyList.hpp"

using namespace std;
class Student : public Human
{
protected:
	int yearOfGraduate;
	string faculty;
	string department;
	string group;
	string numGradeBook;
	vector<Session> sessions;
	int amount;
public:
	Student();

	void editInfo();
	void editSession();

	void sorter(MyList<Student>&);

	string convertForFile();
	void fillStudFromString(const string&, Student&, const char);


	bool correctGradeInput(string&);
	bool correctGroup(string&);

	bool setAmount(int& amount);

	int getYearOfGraduate();
	bool setYearOfGraduate(int&);

	string getFaculty();
	bool setFaculty(string&);

	string getDepartment();
	bool setDepartment(string&);

	string getGroup();
	bool setGroup(string&);

	string getNumGradeBook();
	bool setNumGradeBook(string&);

	friend std::ostream& operator<<(std::ostream&, Student&);
	friend std::istream& operator>>(std::istream&, Student&);
};


