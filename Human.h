#pragma once
#include <string>
#include <iostream>
#include <sstream>
#include "Structures.hpp"

using namespace std;

class Human
{
protected:
	string name;
	string surname;
	string patronymic;
	Date dateOfBirth;
	string floor; //true = girl, false = boy;
public:
	Human();

	Date& stringToDate(string&);
	string dateToString(Date&);
	int& stringToInt(string&);

	bool correctInput(string);
	bool correctGenger(string&);

	bool setName(string&);
	string getName();

	bool setSurname(string&);
	string getSurname();

	bool setPatronymic(string&);
	string getPatronymic();

	bool setDateOfBirth(Date&);
	Date GetDateOfBirth();
	int GetDayOfBirth();
	int GetMonthOfBirth();
	int GetYearOfBirth();

	bool setGender(string&);
	string getGender();
};
