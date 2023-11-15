#include <iostream>
#include <vector>
#include <Windows.h>
#include <cstdlib>
#include <fstream>
#include <string>
#include <filesystem>
#include "Pipe.h"
#include "CS.h"

namespace fs = std::filesystem;
using namespace std;

float InputNum(float min, float max) {
	float num;
	cout << "\n\n> ";
	while ((cin >> num).fail() || (num < min) || (num > max)) {
		cin.clear();
		cin.ignore(10000, '\n');
		cout << "\n\n> ";
	}
	cout << endl;
	return num;
}
int Choose(int min, int max) {
	int num;
	cout << "\n\n> ";
	while ((cin >> num).fail() || (num < min) || (num > max)) {
		cin.clear();
		cin.ignore(10000, '\n');
		cout << "\n> ";
	}
	cout << endl;
	return num;
}
int Menu() {
	std::cout << "\n1.Добавить трубу\n2.Добавить КС\n3.Список объектов\n4.Редактировать трубы\n5.Редактировать цеха\n6.Сохранить\n7.Загрузить\n0.Выход\n\n";
	int number = Choose(0, 7);
	return number;
}

void inputString(istream& in, string& str)
{
	in.ignore(10000, '\n');
	getline(in, str);
	cerr << str << endl;
}


vector <int> filterPipes(vector <Pipe>& pipes)
{
	vector <int> index;
	string name = "all";
	int status = -1;
	cout << "0. Фильтр \n1. Отобразить всё";
	if (!Choose(0, 1))
	{
		cout << "Поиск по названию \n0. Да\n1. Нет" << endl;
		if (!Choose(0, 1))
		{
			cout << "Имя: ";
			inputString(cin, name);
			cout << endl;
		}

		cout << "Поиск по статусу: \n0. Да\n1.Нет" << endl;
		if (!Choose(0, 1))
		{
			cout << "0. Работает \n1. В ремонте";
			status = Choose(0, 1);
		}

		if (name != "all" and status != -1) {
			for (int i = 0; i < pipes.size(); i++)
				if (pipes[i].name == name and pipes[i].inRepare == status)
					index.push_back(i);
		}
		else if (name == "all" and status != -1) {
			for (int i = 0; i < pipes.size(); i++)
				if (pipes[i].inRepare == status)
					index.push_back(i);
		}
		else if (name != "all" and status == -1) {
			for (int i = 0; i < pipes.size(); i++)
				if (pipes[i].name == name)
					index.push_back(i);
		}
		else {
			for (int i = 0; i < pipes.size(); i++)
				index.push_back(i);
		}
	}
	else
		for (int i = 0; i < pipes.size(); i++)
			index.push_back(i);
	return index;
}

int workingStations(vector <CS>& cs, int index) { //Кол-во задействованных цехов
	int num = 0;
	for (int i = 0; i < cs[index].wrkshopsCount; i++) {
		if (cs[index].WS[i])
			num++;
	}
	return num;
}

vector <int> filterCS(vector <CS>& cs)
{
	vector <int> index;
	string name = "all";
	float status = -1;
	cout << "0. Фильтр \n1. Отобразить всё";
	if (!Choose(0, 1))
	{
		cout << "Поиск по названию \n0. Да\n1. Нет" << endl;
		if (!Choose(0, 1))
		{
			cout << "Имя: ";
			inputString(cin, name);
			cout << endl;
		}
		cout << "Поиск по проценту незадействованных цехов: \n0. Да\n1.Нет" << endl;
		if (!Choose(0, 1))
		{
			cout << "Процент незадействованных цехов:";
			status = InputNum(0, 100);
			cout << endl;
		}

		if (name != "all" and status != -1) {
			for (int i = 0; i < cs.size(); i++)
				if (cs[i].name == name and (cs[i].wrkshopsCount - workingStations(cs, i)) / cs[i].wrkshopsCount * 100 == status)
					index.push_back(i);
		}
		else if (name == "all" and status != -1) {
			for (int i = 0; i < cs.size(); i++)
				if ((cs[i].wrkshopsCount - workingStations(cs, i)) / cs[i].wrkshopsCount * 100 == status)
					index.push_back(i);
		}
		else if (name != "all" and status == -1) {
			for (int i = 0; i < cs.size(); i++)
				if (cs[i].name == name)
					index.push_back(i);
		}
		else {
			for (int i = 0; i < cs.size(); i++)
				index.push_back(i);
		}
	}
	else
		for (int i = 0; i < cs.size(); i++)
			index.push_back(i);
	return index;
}

void AddPipe(vector <Pipe>& pipe) {
	Pipe p;
	cout << "Название трубы:\n\n> ";
	string name;
	cin.ignore(10000, '\n');
	getline(cin, p.name	 );
	cout << endl;
	cout << "Длина трубы:";
	float length = InputNum(0, INT_MAX);
	p.length = length;
	cout << "Диаметр трубы: ";
	float diameter = InputNum(0, INT_MAX);
	p.diameter = diameter;
	pipe.push_back(p);
}
void ViewPipes(const vector <Pipe>& pipe, vector <int> indexes) {
	cout << "Список труб:" << endl << endl;
	for (int i: indexes) {
		cout << "Название трубы: " << pipe[i].name << endl;
		cout << "Длина трубы: " << pipe[i].length << endl;
		cout << "Диаметр трубы: " << pipe[i].diameter << endl;
		if (!pipe[i].inRepare)
			cout << "Состояние: ВКЛ." << endl << endl;
		else
			cout << "Состояние: ВЫКЛ." << endl << endl;
	}
}
void AddCS(vector <CS>& cs) {
	CS css;
	cout << "Ввидите название КС: ";
	cin.ignore(10000, '\n');
	getline(cin, css.name);
	cout << "Введите число цехов (1,1000): ";
	int count = Choose(1, 10000);
	for (int j = 0; j < count; j++) {
		css.WS.push_back(true);
	}
	cout << "Введите эффективность (0,100): ";
	float effic = InputNum(0, 100);
	css.efficiency = effic;
	css.wrkshopsCount = count;
	cs.push_back(css);
}
void ViewCSs(const vector <CS>& cs, vector <int> indexes) 
{
	cout << "Список КС:" << endl << endl;
	for (int i: indexes) {
		cout << "Название КС: " << cs[i].name << endl;
		cout << "Число Цехов: " << cs[i].wrkshopsCount << endl << endl;
		cout << "Эффективность КС: " << cs[i].efficiency << "%" << endl << endl;
		for (int j = 0; j < cs[i].WS.size(); j++) {
			if (cs[i].WS[j])
				cout << "\tЦех №" << j + 1 << "      " << "В рабочем состоянии" << endl;
			else
				cout << "\tЦех №" << j + 1 << "      " << "Не в рабочем состоянии" << endl;
		}
		cout << endl;
	}
}
void PipeChange(vector <Pipe>& pipe) 
{
	if (pipe.size() != 0) {
		ViewPipes(pipe,filterPipes(pipe));
		cout << "Выберете трубу для редактирования: ";
		int num = Choose(1,pipe.size());
		cout << "Состояние:\n0.Работает\n1.Требуется ремонт\n";
		int n = Choose(0, 1);
		if (n == 0)
			pipe[num-1].inRepare = true;
		else
			pipe[num-1].inRepare = false;
	}
}
void CSChange(vector <CS>& cs) {
	if (cs.size() != 0) {
		ViewCSs(cs,filterCS(cs));
		cout << "\n\tВыберете КС: ";
		int id_cs = Choose(1, cs.size());
		for (int i = 0; i < cs[id_cs-1].WS.size(); i++) {
			if(cs[id_cs-1].WS[i])
				cout << "Цех №" << i << "\t" << "В рабочем состоянии" << endl;
			else
				cout << "Цех №" << i << "\t" << "В нерабочем состоянии" << endl;
		}
		cout << "\n\tВыберете цех для редактирования: ";
		int id_ws = Choose(1, cs[id_cs-1].WS.size());
		cs[id_cs-1].WS[id_ws - 1] = !cs[id_cs-1].WS[id_ws - 1];
	}
}

void packagePipe(const vector<int>& index, vector <Pipe>& pipes)
{
	cout << "0. Change pipe status\n1. Delete pipe";
	if (!Choose(0,1))
	{
		cout << "Pipe status:" << endl;
		cout << "\t1. UNDER REPAIR \n\t2. IS FUNCTIONING";
		bool status = Choose(1, 2) == 1;
		for (int i = 0; i < index.size(); i++)
			pipes[index[i]].inRepare = status;
	}
	else
		for (int i = index.size() - 1; i >= 0; i--)
		{
			//ID_lost.push_back(pipes[index[i]].id);
			pipes.erase(pipes.begin() + index[i]);
		}
}

string ChooseFileName() {
	string name;
	cout << "Выберете имя файла: ";
	cin.ignore(10000, '\n');
	getline(cin,name);
	return name+".txt";
}

string ViewFiles(const string& path) {
	string filename;
	cout << "Файлы для чтения: \n";
	for (const auto& entry : fs::directory_iterator(path))
		std::cout << entry.path().filename() << std::endl;
	cout << "Выберите называние файла из предложенных: ";
	cin.ignore(10000, '\n');
	getline(cin, filename);
	return filename + ".txt";
}

void SaveData(vector <Pipe>& pipe, vector <CS>& cs) {
	ofstream file;
	file.open("Saves\\"+ChooseFileName(), ios_base::out);
	if (!file.is_open()) {
		cout << "Ошибка чтения файла!";
	}
	else {
		if (pipe.size()!=0) {
			file << 1 << " " << pipe.size() << endl;
			for (int i = 0; i < pipe.size(); i++) {
				file << pipe[i].name << endl;
				file << pipe[i].length << " " << pipe[i].diameter << " " << pipe[i].inRepare << endl;
			}
		}
		else {
			file << 0 << endl;
		}
		if (cs.size() != 0) {
			file << 1 << " " << cs.size() <<  endl;
			for (int i = 0; i < cs.size(); i++) {
				file << cs[i].name << endl;
				file << cs[i].wrkshopsCount << " " << cs[i].efficiency << endl;
				for (bool WS : cs[i].WS) {
					file << WS << " ";
				}
				file << endl;
			}
		}
		else {
			file << 0 << endl;
		}
	}
	file.close();
}

void LoadData(vector <Pipe>& pipe, vector <CS>& cs) {
	ifstream file("Saves\\"+ViewFiles("Saves"), ios::in);
	if (file.is_open() and file.peek() != EOF) {
		bool existPipe;
		int pipeCount;
		file >> existPipe;
		if (existPipe) {
			file >> pipeCount;
			for (int i = 0; i < pipeCount;i++) {
				Pipe pipes;
				file.ignore(10000, '\n');
				getline(file, pipes.name);
				file >> pipes.length;
				file >> pipes.diameter;
				file >> pipes.inRepare;
				pipe.push_back(pipes);
			}
		}
		bool existCS;
		int csCount;
		file >> existCS;
		if (existCS) {
			file >> csCount;
			for (int i = 0; i < csCount; i++) {
				CS css;
				file.ignore(10000, '\n');
				getline(file, css.name);
				file >> css.wrkshopsCount;
				file >> css.efficiency;
				css.WS.resize(css.wrkshopsCount);
				for (int i = 0; i < css.WS.size(); i++) { //добавить всё в WS
					bool ws;
					file >> ws;
					css.WS[i] = ws;

				}
				cs.push_back(css);
			}
		}
	}
	else {
		cout << "\n\nОшибка загрузки файла\n\n";
	}
	file.close();
}
int main()
{
	vector <Pipe> pipe;
	vector <CS> cs;
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);
	while (true) {
		int number = Menu();
		switch (number) {
		case 1:
			//system("cls");
			AddPipe(pipe);
			//system("cls");
			break;
		case 2:
			//system("cls");
			AddCS(cs);
			//system("cls");
			break;
		case 3:
			//system("cls");
			cout << "\t0.Трубы\n\t1.КС\n";
			if(!Choose(0,1))
				ViewPipes(pipe,filterPipes(pipe));
			else
				ViewCSs(cs, filterCS(cs));
			break;
		case 4:
			//system("cls");
			PipeChange(pipe);
			//system("cls");
			break;
		case 5:
			//system("cls");
			CSChange(cs);
			//system("cls");
			break;
		case 6:
			SaveData(pipe, cs);
			break;
		case 7:
			LoadData(pipe, cs);
			break;
		case 0:
			exit(0);
		default:
			system("cls");
			cout << "Ошибка ввода\n";
			break;
		}
	}
	return 0;
}