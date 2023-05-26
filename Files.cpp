#include "Files.h"
#include "CryptoTools.h"

using namespace std;

static const string filename = "db.bin";
static CryptoTools crypter;
 const MyList<Student>&Files::WriteToFile(MyList<Student>& studBase)
{
	const int size = studBase.size();
	fstream file;
	file.open(filename, ios_base::binary | ios_base::out);
	for (int i = 0; i < size; i++)
	{
		file << studBase[i].convertForFile() << endl;
	}
	file.close();
	crypter.encrypt();
	return studBase;
}

 MyList<Student> Files::ReadFromFile(string& filename)
 {
	 ifstream iff("db.enc");
	 if (!iff.fail()) {
		 iff.close();
		 crypter.decrypt();
	 }
	 else {
		 iff.close();
	 }
	 fstream file;
	 MyList<Student> base;
	 file.open(filename, ios_base::binary | ios_base::in);
	 if (!file.is_open())
	 {
		 cout << "Ошибка открытия файла" << endl;
		 return base;
	 }
	 string line;
	 while (getline(file, line))
	 {
		 Student stud;
		 stud.fillStudFromString(line, stud, '$');
		 base.push_back(stud);
	 }
	 return base;
 }
 