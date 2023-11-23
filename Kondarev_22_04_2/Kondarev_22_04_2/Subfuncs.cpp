#include "Subfuncs.h"

using namespace std;
namespace fs = std::filesystem;

int Menu()
{
	std::cout << "\n1.�������� �����" << endl
		<< "2.�������� ��" << endl
		<< "3.������ ��������" << endl
		<< "4.������������� �����" << endl
		<< "5.������������� ����"<< endl
		<< "6.���������"<< endl
		<< "7.���������"<< endl
		<< "8.�������� �������������� ����" << endl
		<< "9.�������� �������������� ��" << endl
		<< "0.�����"<< endl;
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
	cout << "�������� ��� �����: ";
	cin.ignore(10000, '\n');
	getline(cin, name);
	return name + ".txt";
}

std::string ViewFiles(const std::string& path)
{
	string filename;
	cout << "����� ��� ������: \n";
	for (const auto& entry : fs::directory_iterator(path))
		std::cout << entry.path().filename() << std::endl;
	cout << "�������� ��������� ����� �� ������������: ";
	cin.ignore(10000, '\n');
	getline(cin, filename);
	return filename + ".txt";
}

vector <int> indexes(const int& max_num)
{
	int a;
	int b;
	cout << "������� ��������: ";
	a = Choose(1, max_num);//1
	b = Choose(a, max_num);//2
	vector <int> res;
	for (int i = a; i <= b; ++i) {//
		res.push_back(i);
		cout << i << endl;
	}
	return res;
}

