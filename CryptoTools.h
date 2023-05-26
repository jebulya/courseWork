#pragma once
#include <string>
using namespace std;
class CryptoTools
{
	string pathToFile;
	char password[64];
public:
	CryptoTools();
	bool encrypt();
	bool decrypt();
};
