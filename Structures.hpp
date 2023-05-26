#include <iostream>
#include <vector>
#pragma once

using namespace std;
struct Date
{
	int day;
	int month;
	int year;

	void setDay(int& d)
	{
		this->day = d;
	}

	void setMonth(int& d)
	{
		this->month = d;
	}

	void setYear(int& d)
	{
		this->year = d;
	}

	friend std::istream& operator>>(std::istream& os, Date& date) {
		os >> date.day >> date.month >> date.year;
		os.ignore(numeric_limits<streamsize>::max(), '\n');
		return os;
	}

	friend std::ostream& operator<<(std::ostream& os, Date const& date) {
		if (date.day > 0 && date.day < 10) cout << '0';
		os << date.day << '.';
		if (date.month > 0 && date.month < 10) cout << '0';
		os << date.month << '.' << date.year;
		return os;
	}
};

struct Subject 
{
	string title;
	string mark;

	Subject()
	{
		this->title = "Языки программирования";
		this->mark = "Отл";
	}

	string subjectToString()
	{
		string result{ title + '$' + mark };
		return result;
	}

	bool correctInputing(string& input)
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

	bool setTitle(string& tit)
	{
		if (correctInputing(tit)) {
			this->title = tit;
			return true;
		}
		else
		{
			cout << "Ай!\n";
			return false;
		}

	}

	bool setMark(string& mark)
	{
		if (mark == "Неуд" || mark == "Удовл" || mark == "Хор" || mark == "Отл" || mark == "Зачет" || mark == "Незачет") {
			this->mark = mark;
			return true;
		}
		else
		{
			cout << "Ай!\n";
			return false;
		}

	}


	friend std::istream& operator>>(std::istream& is, Subject& sub) {
		cout << "Введите название предмета:\n";
		cin.ignore(numeric_limits<streamsize>::max(), '\n');
		do {
			getline(is, sub.title);
		} while (!sub.setTitle(sub.title));

		cout << "Введите оценку следующим образом: Неуд Удовл Хор Отл Зачет Незачет \n(только через Е!)\n";
		do {
			is >> sub.mark;
		} while (!sub.setMark(sub.mark));
		return is;
	}

	friend std::ostream& operator<<(std::ostream& os, Subject const& sub) {
		return os << sub.title << " - " << sub.mark << endl;
	}
};

struct Session
{
	int semester;
	vector<Subject> subjects;
	int count;

	Session()
	{
		this->count = 2;
		this->semester = 1;
		subjects.resize(this->count);
		subjects.clear();
		for (int i = 0; i < this->count; i++)
		{
			subjects.push_back(Subject());
		}
	}

	Session(int size)
	{
		this->count = size;
		this->semester = 1;
		subjects.clear();
		subjects.resize(size);
		for (int i = 0; i < this->count; i++)
		{
			subjects[i] = Subject();
		}
	}

	string SessionToString(Session& sess)
	{
		string result{ to_string(count) + '$' + to_string(sess.semester) + '$' };
		for (int i = 0; i < sess.count; i++)
		{
			result += sess.subjects[i].subjectToString() + '$';
		}
		return result;
	}

	bool setCount(int& size)
	{
		if (size > 0 && size <= 10)
		{
			this->count = size;
			subjects.resize(size);
			subjects.clear();
			for (int i = 0; i < this->count; i++)
			{
				subjects.push_back(Subject());
			}
			return true;
		}
		else
		{
			cout << "Ай! неверное число предметов\n";
			return false;
		}
	}

	bool setSemester(int& sem)
	{
		if (sem > 0 && sem <= 10) {
			int temp = sem;
			this->semester = temp;
			return true;
		}
		else
		{
			cout << "Ай!неверный номер семестра\n";
			return false;
		}
	}

	void editSubjects()
	{
		string temp;
		string zeze;
		Subject sub;
		int handler;
		int iChoice = -1;
		for (; iChoice != 0;)
		{
			cout << "Режим редактирования предметов" << endl;
			cout << "1 - Добавить предмет" << endl;
			cout << "2 - Удалить предмет" << endl;
			cout << "3 - Отредактировать уже существующий предмет" << endl;
			cout << "4 - Распечатать данные" << endl;
			cout << "0 - Выход из режима" << endl;
			string zeze;
			do {
				cin >> temp;
				iChoice = stoi(temp);
				
			} while (iChoice > 4);
			switch (iChoice)
			{
			case 1:
				cout << "Сколько предметов добавить?" << endl;
				cin >> temp;
				handler = stoi(temp);
				for (int i = 0; i < handler; i++)
				{
					cin >> sub;
					subjects.push_back(sub);
				}
				system("cls");
				break;
			case 2:
				cout << "Предмет под каким номером желаете удалить?" << endl;
				do {
					cin >> temp;
					handler = stoi(temp);
				} while (handler > subjects.size());
				try
				{
					auto iter = subjects.cbegin();
					subjects.erase((iter + handler) - 1);
				}
				catch (std::out_of_range e)
				{
					cerr << "Ай!Неверный индекс" << endl;
				}
				system("cls");
				break;
			case 3:
				cout << "Предмет под каким номером желаете изменить?" << endl;
				do {
					cin >> temp;
					handler = stoi(temp);
				} while (handler > subjects.size());
				try
				{
					cout << "Введите новую информацию" << endl;
					cin >> sub;
					subjects[handler - 1] = sub;
				}
				catch (std::out_of_range e)
				{
					cerr << "Ай!Неверный номер" << endl;
				}
				system("cls");
				break;
			case 4:
				for (int i = 0; i < subjects.size(); i++)
				{
					cout << subjects[i];
				}
				system("pause");
				system("cls");
				break;
			default:
				break;
			}
		}
	}


	friend std::istream& operator>>(std::istream& is, Session& sess) {
		Subject sub;
		string temp;
		cout << "Введите номер семестра:\n";
		do {
			is >> temp;
			sess.semester = stoi(temp);
		} while (!sess.setSemester(sess.semester));
		cout << "Введите кол-во предметов:\n";
		do {
			is >> sess.count;
		} while (!sess.setCount(sess.count));
		sess.subjects.clear();
		for (int i = 0; i < sess.count; i++)
		{
			cout << "Ввод " << i + 1 << " предмета\n";
			is >> sub;
			sess.subjects.push_back(sub);
		}
		return is;
	}

	friend std::ostream& operator<<(std::ostream& os, Session const& sess) {
		os << "СЕМЕСТР №" << sess.semester << endl;
		for (int i = 0; i < sess.subjects.size(); i++)
		{
			os << i + 1 << ". " << sess.subjects[i];
		}
		return os;
	}
};
