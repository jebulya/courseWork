#include "Student.h"
#include <iostream>

using namespace std;

Student::Student()
{
	this->yearOfGraduate = 2022;
	this->faculty = "Институт кибербезопасности и цифровых технологий";
	this->department = "КБ-1";
	this->group = "БАСО-05-22";
	this->numGradeBook = "22Б1111";
	this->amount = 3;
	sessions.resize(this->amount);
	sessions.clear();
	for (int i = 0; i < this->amount; i++)
	{
		sessions.push_back(Session());
	}
}
struct StudentsForSorting
{
	Student stud;
	float keyForSorting;

	void setStudent(Student& stud)
	{
		this->stud = stud;
	}

	void setKeyForSorting(float& key)
	{
		this->keyForSorting = key;
	}

	bool operator>(const StudentsForSorting& value)
	{
		if (this->keyForSorting > value.keyForSorting)
			return true;
		else
			return false;
	}

	bool operator<(const StudentsForSorting& value)
	{
		if (this->keyForSorting < value.keyForSorting)
			return true;
		else
			return false;
	}
};

void Student::editSession()
{

	//cout << "Введите номер семестра" << endl;
	cout << ">";
	string flag;
	string temp;
	int iChoice = -1;
	for (; iChoice != 0;)
	{
		cout << "Режим редактирования сессий" << endl;
		cout << "1 - Добавить сессию" << endl;
		cout << "2 - Редактировать сессию" << endl;
		cout << "3 - Удалить сессию" << endl;
		cout << "4 - Распечатать информацию о сессиях" << endl;
		cout << "0 - Выйти из режима редактирования сессий" << endl;
		string temp;
		do {
			cin >> temp;
			iChoice = stoi(temp);
			//cin.ignore(numeric_limits<streamsize>::max(), '\n');
		} while (iChoice > 5);
		int handler;
		string flag;
		Session sess;
		switch (iChoice)
		{
		case 1:
			cout << "Сколько сессий добавить? Доступно еще " << 10 - sessions.size() << endl;
			cin >> temp;
			handler = stoi(temp);
			for (int i = 0; i < handler; i++)
			{
				cout << "Введите информацию о сессии:" << endl;
				cin >> sess;
				sessions.push_back(sess);
				cout << "Введите +, чтобы перейти в режим редактирования предметов." << endl;
				cin >> flag;
				system("cls");
				//cout << ">";
				//cin.ignore(numeric_limits<streamsize>::max(), '\n');
				if (flag == "+") {
					sessions[i].editSubjects();
				}
				cout << "Успех!" << endl;
				system("cls");
				//cout << ">";
				cin.ignore(numeric_limits<streamsize>::max(), '\n');
			}
			break;
		case 2:
			cout << "Какую сессию по счету хотите изменить? Доступно " << sessions.size() << endl;
			do {
				cin >> temp;
				handler = stoi(temp);
			} while (handler > sessions.size());
			try
			{
				cout << "Введите +, чтобы перейти в режим редактирования предметов" << endl;
				cout << "Введите другой символ, чтобы ввести данные о сессии с нуля" << endl; //////////
				cin >> flag;
				if (flag == "+") {
					sessions[handler - 1].editSubjects();
				}
				else {
					cout << "Введите новую информацию" << endl;
					cin >> sess;
					sessions[handler - 1] = sess;
				}
				cout << "Успех!" << endl;
				system("cls");
				cin.ignore(numeric_limits<streamsize>::max(), '\n');
			}
			catch (std::out_of_range e)
			{
				cerr << "Ай!Неверный номер" << endl;
			}
			break;
		case 3:
			cout << "Сессию под каким номером желаете удалить? Доступно " << sessions.size() << endl;
			do {
				cin >> temp;
				handler = stoi(temp);
			} while (handler > sessions.size());
			try
			{
				auto iter = sessions.cbegin();
				sessions.erase((iter + handler) - 1);
				cout << "Успех!" << endl;
				system("cls");
				cin.ignore(numeric_limits<streamsize>::max(), '\n');
			}
			catch (std::out_of_range e)
			{
				cerr << "Ай!Неверный индекс" << endl;
			}
			break;
		case 4:
			for (int i = 0; i < sessions.size(); i++)
			{
				cout << "ПОРЯДКОВЫЙ НОМЕР " << i + 1 << endl << sessions[i] << endl;
			}
			system("pause");
			system("cls");
			break;
		case 5:
			system("cls");
			break;
		}
	}
}

void Student::sorter(MyList<Student>& studBase)
{
	const int sizeOfBase = studBase.size();
	float keyForSort = 0;
	int amountOfMarks;
	int commonAmountOfMarks = 0;
	int amountOfSessions;
	StudentsForSorting studes;
	vector <StudentsForSorting> menArray;
	vector <StudentsForSorting> womenArray;
	MyList<Student> sortedStudents;
	for (int j = 0; j < sizeOfBase; j++)
	{
		if (studBase[j].sessions.size() > 1) {
			if (studBase[j].sessions[0].semester == 1 && studBase[j].sessions[1].semester == 2) {
				commonAmountOfMarks = studBase[j].sessions[0].subjects.size() + studBase[j].sessions[1].subjects.size();
				amountOfSessions = 2;
			}
			else if (studBase[j].sessions[0].semester == 1 && studBase[j].sessions[1].semester != 2) {
				commonAmountOfMarks = studBase[j].sessions[1].subjects.size();
				amountOfSessions = 1;
			}
			else
				commonAmountOfMarks = -1;
		}
		else if (studBase[j].sessions.size() == 1) {
			if (studBase[j].sessions[0].semester == 2) {
				commonAmountOfMarks = studBase[j].sessions[0].subjects.size();
				amountOfSessions = 1;
			}
			else if (studBase[j].sessions[0].semester == 1) {
				commonAmountOfMarks = studBase[j].sessions[0].subjects.size();
				amountOfSessions = 1;
			}
			else
				commonAmountOfMarks = -1;
		}
		amountOfMarks = 0;
		for (int i = 0; i < amountOfSessions; i++)
		{
			for (int k = 0; k < studBase[j].sessions[i].subjects.size(); k++)
			{
				if (studBase[j].sessions[i].subjects[k].mark == "Удовл") {
					//amountOfMarks = 0;
					amountOfMarks++;
				}
				keyForSort = (float(amountOfMarks) / float(commonAmountOfMarks));
			}
		}
		studes.setStudent(studBase[j]);
		studes.setKeyForSorting(keyForSort);
		if (studBase[j].floor == "Женский") {
			womenArray.push_back(studes);
		}
		else {
			menArray.push_back(studes);
		}
	}
	cout << "Кого вы хотите отсортировать?" << endl;
	cout << "1 - Девушек" << endl;
	cout << "2 - Юношей" << endl;
	cout << "3 - И девушек, и юношей" << endl;
	cout << "0 - Выход из режима" << endl;
	int switcher;
	cin >> switcher;
	int d;
	switch (switcher)
	{
	case 1:
		d = 0;
		for (int i = 0; i < womenArray.size(); i++)
		{
			StudentsForSorting temp = womenArray[i];
			int j = i - 1;
			while (j >= 0 && womenArray[j] < temp)
			{
				womenArray[j + 1] = womenArray[j];
				j--;
			}
			womenArray[j + 1] = temp;
		}
		for (int j = 0; j < womenArray.size(); j++)
		{
			studBase[j] = womenArray[j].stud;
		}

		for (int j = womenArray.size(); j < studBase.size(); j++)
		{
			studBase[j] = menArray[d].stud;
			d++;
		}
		break;
	case 2:
		d = 0;
		for (int i = 0; i < menArray.size(); i++)
		{
			StudentsForSorting temp = menArray[i];
			int j = i - 1;
			while (j >= 0 && menArray[j] < temp)
			{
				menArray[j + 1] = menArray[j];
				j--;
			}
			menArray[j + 1] = temp;
		}
		for (int j = 0; j < menArray.size(); j++)
		{
			studBase[j] = menArray[j].stud;
		}
		for (int j = menArray.size(); j < studBase.size(); j++)
		{
			studBase[j] = womenArray[d].stud;
			d++;
		}
		break;
	case 3:
		d = 0;
		for (int i = 0; i < womenArray.size(); i++)
		{
			StudentsForSorting temp = womenArray[i];
			int j = i - 1;
			while (j >= 0 && womenArray[j] < temp)
			{
				womenArray[j + 1] = womenArray[j];
				j--;
			}
			womenArray[j + 1] = temp;
		}
		for (int i = 0; i < menArray.size(); i++)
		{
			StudentsForSorting temp = menArray[i];
			int j = i - 1;
			while (j >= 0 && menArray[j] < temp)
			{
				menArray[j + 1] = menArray[j];
				j--;
			}
			menArray[j + 1] = temp;
		}
		for (int j = 0; j < womenArray.size(); j++)
		{
			studBase[j] = womenArray[j].stud;
		}
		for (int j = womenArray.size(); j < studBase.size(); j++)
		{
			studBase[j] = menArray[d].stud;
			d++;
		}
		break;
	}
}

void Student::editInfo()
{
	int iChoice = -1;
	for (; iChoice != 0;)
	{
		cout << "Вы выбрали изменить информацию о студенте: " << name << ' ' << patronymic << ' ' << surname << endl;
		cout << "Введите цифру, чтобы изменить следующее поле:\n";
		cout << "1 - Имя студента;" << endl;
		cout << "2 - Отчество студента;" << endl;
		cout << "3 - Фамилия студента;" << endl;
		cout << "4 - Дата рождения студента;" << endl;
		cout << "5 - Пол студента;" << endl;
		cout << "6 - Название института;" << endl;
		cout << "7 - Название кафедры;" << endl;
		cout << "8 - Номер группы;" << endl;
		cout << "9 - Номер зачётной книжки;" << endl;
		cout << "10 - Год зачисления;" << endl;
		cout << "11 - Режим редактирования сессий" << endl;
		cout << "0 - Выход из режима" << endl;
		cout << ">";
	string temp;
	do {
		cin >> temp;
		iChoice = stoi(temp);
		//cin.ignore(numeric_limits<streamsize>::max(), '\n');
	} while (iChoice > 11);
		switch (iChoice)
		{
		case 1:
			cout << "Введите имя:" << endl;
			do {
				cin >> name;
			} while (!setName(name));
			cout << "Успех!" << endl;
			system("cls");
			cin.ignore(numeric_limits<streamsize>::max(), '\n');
			break;
		case 3:
			cout << "Введите фамилию:" << endl;
			do {
				cin >> surname;
			} while (!setSurname(surname));
			cout << "Успех!" << endl;
			system("cls");
			cin.ignore(numeric_limits<streamsize>::max(), '\n');
			break;
		case 2:
			cout << "Введите отчество:" << endl;
			do {
				cin >> patronymic;
			} while (!setPatronymic(patronymic));
			cout << "Успех!" << endl;
			system("cls");
			cin.ignore(numeric_limits<streamsize>::max(), '\n');
			break;
		case 4:
			cout << "Введите дату рождения (ДД-ММ-ГГГГ, разделять enter):" << endl;
			do {
				cin >> dateOfBirth;
			} while (!setDateOfBirth(dateOfBirth));
			cout << "Успех!" << endl;
			system("cls");
			//cin.ignore(numeric_limits<streamsize>::max(), '\n');
			break;
		case 5:
			cout << "Введите пол (мужской/женский):" << endl;
			do {
				cin >> floor;
			} while (!setGender(floor));
			cout << "Успех!" << endl;
			system("cls");
			cin.ignore(numeric_limits<streamsize>::max(), '\n');
			break;
		case 6:
			cout << "Введите название института:\n";
			do {
				cin >> faculty;
			} while (!setFaculty(faculty));
			cout << "Успех!" << endl;
			system("cls");
			cin.ignore(numeric_limits<streamsize>::max(), '\n');
			break;
		case 7:
			cout << "Введите название кафедры:\n";
			do {
				cin >> department;
			} while (!setDepartment(department));
			cout << "Успех!" << endl;
			system("cls");
			cin.ignore(numeric_limits<streamsize>::max(), '\n');
			break;
		case 8:
			cout << "Введите название группы:\n";
			do {
				cin >> group;
			} while (!setGroup(group));
			cout << "Успех!" << endl;
			system("cls");
			cin.ignore(numeric_limits<streamsize>::max(), '\n');
			break;
		case 9:
			cout << "Введите номер зачётной книжки:\n";
			do {
				cin >> numGradeBook;
			} while (!setNumGradeBook(numGradeBook));
			cout << "Успех!" << endl;
			system("cls");
			cin.ignore(numeric_limits<streamsize>::max(), '\n');
			break;
		case 10:
			cout << "Введите год зачисления:\n";
			do {
				cin >> yearOfGraduate;
			} while (!setYearOfGraduate(yearOfGraduate));
			cout << "Успех!" << endl;
			system("cls");
			cin.ignore(numeric_limits<streamsize>::max(), '\n');
			break;
		case 11:
			system("cls");
			editSession();
			cout << "Успех!" << endl;
			cout << ">";
			break;
		default: 
			system("cls");
			break;
		}
	}
}

string Student::convertForFile()
{
	string result{ this->name + '$' + this->patronymic + '$' + this->surname + '$' + dateToString(this->dateOfBirth) + '$' + this->floor + '$' +
		this->faculty + '$' + this->department + '$' + this->group + '$' + this->numGradeBook + '$' + to_string(this->yearOfGraduate) + '$' + to_string(this->amount) + '$'};
	for (int i = 0; i < this->sessions.size(); i++)
	{
		result += this->sessions[i].SessionToString(this->sessions[i]);
	}
	return result;
}

void Student::fillStudFromString(const string& str, Student& stud, const char delimiter = '$')
{
	string field;
	stringstream ss(str);
	//stud.sessions.clear();
	getline(ss, field, delimiter);
	stud.setName(field);
	getline(ss, field, delimiter);
	stud.setPatronymic(field);
	getline(ss, field, delimiter);
	stud.setSurname(field);
	getline(ss, field, delimiter);
	stud.setDateOfBirth(stringToDate(field));
	getline(ss, field, delimiter);
	stud.setGender(field);
	getline(ss, field, delimiter);
	stud.setFaculty(field);
	getline(ss, field, delimiter);
	stud.setDepartment(field);
	getline(ss, field, delimiter);
	stud.setGroup(field);
	getline(ss, field, delimiter);
	stud.setNumGradeBook(field);
	getline(ss, field, delimiter);
	stud.setYearOfGraduate(stringToInt(field));
	getline(ss, field, delimiter);
	stud.setAmount(stringToInt(field));
	for (int i = 0; i < stud.amount; i++) //of sessions
	{
		getline(ss, field, delimiter);
		stud.sessions[i].setCount(stringToInt(field));
		getline(ss, field, delimiter);
		stud.sessions[i].setSemester(stringToInt(field));
		//stud.sessions[i].subjects.clear();
		for (int j = 0; j < stud.sessions[i].count; j++) //of subjects
		{
			getline(ss, field, delimiter);
			stud.sessions[i].subjects[j].setTitle(field);
			getline(ss, field, delimiter);
			stud.sessions[i].subjects[j].setMark(field);
		}
	}
}

std::ostream& operator<<(std::ostream& os, Student& stud)
{
	os << stud.name << ' ' << stud.patronymic << ' ' << stud.surname << ' ' << stud.dateOfBirth << ' ' << stud.floor << ' ' <<
		stud.faculty << ' ' << stud.department << ' ' << stud.group << ' ' << stud.numGradeBook << ' ' << stud.yearOfGraduate << endl;
	for (int i = 0; i < stud.sessions.size(); i++)
	{
		os << stud.sessions[i] << endl;
	}
	return os;
}

std::istream& operator>>(std::istream& is, Student& stud) {
	cout << "Введите имя:" << endl;
	do {
		is >> stud.name;
	} while (!stud.setName(stud.name));
	cout << "Введите фамилию:" << endl;
	do {
		is >> stud.surname;
	} while (!stud.setSurname(stud.surname));
	cout << "Введите отчество:" << endl;
	do {
		is >> stud.patronymic;
	} while (!stud.setPatronymic(stud.patronymic));
	cout << "Введите дату рождения (ДД-ММ-ГГГГ, разделять enter):" << endl;
	do {
		is >> stud.dateOfBirth;
	} while (!stud.setDateOfBirth(stud.dateOfBirth));
	cout << "Введите пол (мужской/женский):" << endl;
	do {
		is >> stud.floor;
	} while (!stud.setGender(stud.floor));
	cout << "Введите название института:\n";
	do {
		is >> stud.faculty;
	} while (!stud.setFaculty(stud.faculty));
	cout << "Введите название кафедры:\n";
	do {
		is >> stud.department;
	} while (!stud.setDepartment(stud.department));
	cout << "Введите название группы:\n";
	do {
		is >> stud.group;
	} while (!stud.setGroup(stud.group));
	cout << "Введите номер зачётной книжки:\n";
	do {
		is >> stud.numGradeBook;
	} while (!stud.setNumGradeBook(stud.numGradeBook));
	cout << "Введите год зачисления:\n";
	do {
		is >> stud.yearOfGraduate;
	} while (!stud.setYearOfGraduate(stud.yearOfGraduate));
	cout << "Введите кол-во сессий:\n";
	do {
		is >> stud.amount;
	} while (!stud.setAmount(stud.amount));
	stud.sessions.clear();
	for (int i = 0; i < stud.amount; i++)
	{
		Session sess;
		is >> sess;
		stud.sessions.push_back(sess);
	}

	return is;
}

bool Student::correctGroup(string& input)
{
	const string evilSyms = ",./|¹;:?!@#$%^&*()_+==*<>`~{}[]";
	for (char c : input)
	{
		if (evilSyms.find(c) != evilSyms.npos)
		{
			return false;
		}
	}
	return true;
}
bool Student::setAmount(int& amount)
{
	if (amount > 0 && amount <= 10)
	{
		this->amount = amount;
		sessions.resize(amount);
		sessions.clear();
		for (int i = 0; i < this->amount; i++)
		{
			sessions.push_back(Session());
		}
		return true;
	}
	else
	{
		cout << "Ай! неверное кол-во сессий\n";
		return false;
	}
}
bool Student::correctGradeInput(string& input)
{
	const string evilSyms = "-,./|¹;:?!@#$%^&*()_+==*<>`~{}[]";
	for (char c : input)
	{
		if (evilSyms.find(c) != evilSyms.npos)
		{
			return false;
		}
	}
	return true;
}

int Student::getYearOfGraduate()
{
	return this->yearOfGraduate;
};

bool Student::setYearOfGraduate(int& y)
{
	if (y >= 1900 && y < 2100)
	{
		this->yearOfGraduate = y;
		return true;
	}
	else
		return false;
}
string Student::getFaculty()
{
	return this->faculty;
}

bool Student::setFaculty(string& fac)
{
	if (correctInput(fac)) {
		this->faculty = fac;
		return true;
	}
	else
	{
		cout << "Ай! неверный институт\n";
		return false;
	}
}

string Student::getDepartment()
{
	return this->department;
};

bool Student::setDepartment(string& dep)
{
	if (correctGroup(dep)) {
		this->department = dep;
		return true;
	}
	else
	{
		cout << "Ай! неверная кафедра\n";
		return false;
	}
};
string Student::getGroup()
{
	return this->group;
};

bool Student::setGroup(string& group)
{

	if (correctGroup(group)) {
		this->group = group;
		return true;
	}
	else
	{
		cout << "Ай! неверная группа\n";
		return false;
	}
};

string Student::getNumGradeBook()
{
	return this->numGradeBook;
};

bool Student::setNumGradeBook(string& numGrade)
{
	if (correctGradeInput(numGrade)) {
		this->numGradeBook = numGrade;
		return true;
	}
	else
	{
		cout << "Ай! неверная зачётка\n";
		return false;
	}
}