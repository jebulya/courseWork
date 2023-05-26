#include "Human.h"

using namespace std;

Human::Human()
{
	this->name = "Прокопий";
	this->surname = "Прокопьев";
	this->patronymic = "Прокопьевич";
	this->dateOfBirth = {18, 04, 2004};
	this->floor = "Мужской";
}

Date& Human::stringToDate(string& str)
{
	Date date;
	string temp;
	stringstream ss(str);
	const char delimiter = '.';
	getline(ss, temp, delimiter);
	date.day = stringToInt(temp);
	getline(ss, temp, delimiter);
	date.month = stringToInt(temp);
	getline(ss, temp, delimiter);
	date.year = stringToInt(temp);
	return date;
}

string Human::dateToString(Date& date)
{
	string result{ to_string(date.day) + '.' + to_string(date.month) + '.' + to_string(date.year) };
	return result;
}

int& Human::stringToInt(string& str)
{
	int result = stoi(str);
	return result;
}

bool Human::correctInput(string input)
{
	const string evilSyms = "0123456789,./|¹;:?!@#$%^&*()_+==*-<>`~{}[]";
	for (char c : input)
	{
		if (evilSyms.find(c) != evilSyms.npos)
		{
			return false;
		}
	}
	return true;
}

bool Human::correctGenger(string& fl)
{
	if (fl == "Женский"|| fl == "Мужской")
		return true;
	else
		return false;
}

bool Human::setGender(string& fl)
{
	if (correctGenger(fl)) {
		this->floor = fl;
		return true;
	}
	else
	{
		cout << "Ай! Неверный пол\n";
		return false;
	}
	
}

bool Human::setDateOfBirth(Date& date)
{
	if ((date.month > 0 && date.month < 13) && (date.year >= 1900 && date.year < 2100))
	{
		int maxDay;
		switch (date.month)
		{
		case 2:
			if (date.year % 4 == 0)
				maxDay = 29;
			else
				maxDay = 28;
			break;
		case 1:
		case 3:
		case 5:
		case 7:
		case 8:
		case 10:
		case 12:
			maxDay = 31;
			break;
		default:
			maxDay = 30;
			break;
		}
		if (date.day > 0 && date.day <= maxDay)
		{
			this->dateOfBirth = date;
			return true;
		}
	}
	else
	{
		cout << "Ай! Неверная дата\n";
		return false;
	}
}

string Human::getGender()
{
	return this->floor;
}

bool Human::setName(string& name)
{
	if (correctInput(name)) {
		this->name = name;
		return true;
	}
	else
	{
		cout << "Ай!Неверное имя\n";
		return false;
	}
}

string Human::getName()
{
	return this->name;
}

bool Human::setSurname(string& sname)
{
	if (correctInput(sname)) {
		this->surname = sname;
		return true;
	}
	else
	{
		cout << "Ай!Неверная фамилия\n";
		return false;
	}
}

 string Human::getSurname()
{
	return this->surname;
}

bool Human::setPatronymic(string& patr)
{
	if (correctInput(patr)) {
		this->patronymic = patr;
		return true;
	}
	else
	{
		cout << "Ай! Неверное отчество\n";
		return false;
	}
}

string Human::getPatronymic()
{
	return this->patronymic;
}

Date Human:: GetDateOfBirth()
{
	return this->dateOfBirth;
};

int Human::GetDayOfBirth()
{
	return GetDateOfBirth().day;
};

int Human::GetMonthOfBirth()
{
	return GetDateOfBirth().month;
};

int Human::GetYearOfBirth()
{
	return GetDateOfBirth().year;
};
