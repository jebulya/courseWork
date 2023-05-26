#include "CryptoTools.h"
#include <iostream>
#include <Windows.h>
CryptoTools::CryptoTools()
{
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);
	pathToFile = "db.bin";
	cout << "¬ведите пароль" << endl;
	cin >> password;
}


bool CryptoTools::encrypt()
{
	string command = "openssl\\bin\\openssl.exe enc -aes-256-cbc -salt -in " + pathToFile + " -out db.enc -pass pass:" + password;
	system(command.c_str());
	if (remove("db.bin") != 0) {
		return false;
	}
	return true;
}

bool CryptoTools::decrypt()
{
	string command = "openssl\\bin\\openssl.exe enc -aes-256-cbc -d -in db.enc -out db.bin -pass pass:";
	command += password;
	system(command.c_str());
	if (remove("db.enc") != 0) {
		return false;
	}
	return true;
}
