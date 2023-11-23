#include "Subfuncs.h"

using namespace std;
namespace fs = std::filesystem;

int Menu()
{
	std::cout << "\n1.Добавить трубу" << endl
		<< "2.Добавить КС" << endl
		<< "3.Список объектов" << endl
		<< "4.Редактировать трубы" << endl
		<< "5.Редактировать цеха"<< endl
		<< "6.Сохранить"<< endl
		<< "7.Загрузить"<< endl
		<< "8.Пакетное редактирование труб" << endl
		<< "9.Пакетное редактирование КС" << endl
		<< "0.Выход"<< endl;
	int number = Choose(0, 9);
	return number;
}

float InputNum(float min, float max)
{
	float num;
	while ((cin >> num).fail() || (num < min) || (num > max)) {
		cin.clear();
		cin.ignore(10000, '\n');
	}
	cerr << num << endl;
	return num;
}

int Choose(int min, int max) 
{
	int num;
	while ((cin >> num).fail() || (num < min) || (num > max)) {
		cin.clear();
		cin.ignore(10000, '\n');
	}
	cerr << num << endl;
	return num;
}

void inputString(istream& in, string& str)
{
	in.ignore(10000, '\n');
	getline(in, str);
	cerr << str << endl;
}

string ChooseFileName()
{
	string name;
	cout << "Выберете имя файла: ";
	cin.ignore(10000, '\n');
	getline(cin, name);
	return name + ".txt";
}

std::string ViewFiles(const std::string& path)
{
	string filename;
	cout << "Файлы для чтения: \n";
	for (const auto& entry : fs::directory_iterator(path))
		std::cout << entry.path().filename() << std::endl;
	cout << "Выберите называние файла из предложенных: ";
	cin.ignore(10000, '\n');
	getline(cin, filename);
	return filename + ".txt";
}

vector <int> indexes(const int& max_num)
{
	int a;
	int b;
	cout << "Введите интервал: ";
	a = Choose(1, max_num);//1
	b = Choose(a, max_num);//2
	vector <int> res;
	for (int i = a; i <= b; ++i) {//
		res.push_back(i);
		cout << i << endl;
	}
	return res;
}

