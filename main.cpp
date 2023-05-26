#include "Files.h"
#include "MyList.hpp"
#include "Student.h"
#include <windows.h>

int main()
{
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);
	string s = "db.bin";
	MyList<Student> students, fileStudents;
	students = Files::ReadFromFile(s);
	Student tempStud;
	int handler;
	string temp;
	int iChoice = -1;
	for (; iChoice != 0;)
	{
		cout << " - - - Г Л А В Н О Е  М Е Н Ю  - - - " << endl;
		cout << "1 - Распечатать краткий список студентов" << endl;
		cout << "2 - Отсортировать студентов по варианту (№37)" << endl;
		cout << "3 - Добавить студента" << endl;
		cout << "4 - Удалить студента" << endl;
		cout << "5 - Редактировать студента" << endl;
		cout << "6 - Вывести карточку студента" << endl;
		cout << "7 - Сохранить изменения в файл" << endl;
		cout << "0 - Выход из программы" << endl;
		string temp;
		do {
			cout << ">";
			cin >> temp;
			iChoice = stoi(temp);
		} while (iChoice > 7);
		switch (iChoice)
		{
		case 1:
			cout << "Вы выбрали вариант 1 - Распечатать краткий список студентов. Доступно " << students.size() << endl;
			for (int i = 0; i < students.size(); i++)
			{
				cout << i + 1 << ". " << students[i].getName() << ' ' << students[i].getPatronymic() << ' ' << students[i].getSurname()
					<< ' ' << students[i].GetDateOfBirth() << ' ' << students[i].getGroup() << endl;
			}
			system("pause");
			system("cls");
			break;
		case 2:
			cout << "Вы выбрали вариант 2 - Отсортировать студентов. Доступно " << students.size() << endl; //cls
			tempStud.sorter(students);
			fileStudents = Files::WriteToFile(students);
			cout << "Успех!" << endl;
			system("pause");
			system("cls");
			break;
		case 3:
			cout << "Вы выбрали вариант 3 - Добавить студента" << endl; //cls
			cin >> tempStud;
			students.push_back(tempStud);
			fileStudents = Files::WriteToFile(students);
			cout << "Успех!" << endl;
			system("pause");
			system("cls");
			break;
		case 4:
			cout << "Вы выбрали вариант 4 - Удалить студента. Доступно " << students.size() << endl;
			cout << "Введите номер студента" << endl;
			if (students.size() > 0)
			{
				do {
					cin >> temp;
					handler = stoi(temp);
				} while (handler > students.size());
				students.removeAt(handler - 1);
				fileStudents = Files::WriteToFile(students);
				cout << "Успех!" << endl;
				system("pause");
				system("cls");
			}
			break;
		case 5:
			cout << "Вы выбрали вариант 5 - Редактировать студента. Доступно " << students.size() << endl;
			cout << "Введите номер студента" << endl;
			do {
				cin >> temp;
				handler = stoi(temp);
			} while (handler > students.size());
			students[handler - 1].editInfo();
			fileStudents = Files::WriteToFile(students);
			cout << "Успех!" << endl;
			system("pause");
			system("cls");
			break;
		case 6:
			cout << "Вы выбрали вариант 6 - Вывести карточку студента. Доступно " << students.size() << endl;
			cout << "Введите номер студента" << endl;
			do {
				cin >> temp;
				handler = stoi(temp);
			} while (handler > students.size());
			cout << students[handler - 1];
			cout << "Успех!" << endl;
			system("pause");
			system("cls");
			break;
		case 7:
			cout << "Вы выбрали вариант 7 - Сохранить данные в файл " << endl;
			fileStudents = Files::WriteToFile(students);
			cout << "Успех!" << endl;
			system("pause");
			system("cls");
			break;
		}
	}
}