#pragma once
#include <fstream>
#include <iostream>
#include <string>
#include "MyList.hpp"
#include "Student.h"

struct Files
{
	static const MyList<Student>& WriteToFile(MyList<Student>&);
	static MyList<Student> ReadFromFile(string&);
};

