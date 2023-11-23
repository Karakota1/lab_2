#include "Pipe.h"
#include "Subfuncs.h"

using namespace std;

int Pipe::MaxId = 0;

Pipe::Pipe()
{
	id = MaxId++;
}

vector <int> Pipe::filterPipes()
{
	vector <int> index;
	string name = "all";
	int status = -1;
	cout << "\n0. Фильтр \n1. Отобразить всё\nВведите: ";
	if (!Choose(0, 1))
	{
		cout << "Поиск по названию \n0. Да\n1. Нет\nВведите: " << endl;
		if (!Choose(0, 1))
		{
			cout << "Имя: ";
			inputString(cin, name);
			cout << endl;
		}

		cout << "Поиск по статусу: \n0. Да\n1.Нет\nВведите: " << endl;
		if (!Choose(0, 1))
		{
			cout << "0. Работает \n1. В ремонте";
			status = Choose(0, 1);
		}

		if (name != "all" and status != -1) {
			for (int i = 0; i < pipe.size(); i++)
				if (pipe[i].name == name and pipe[i].inRepare == status)
					index.push_back(i);
		}
		else if (name == "all" and status != -1) {
			for (int i = 0; i < pipe.size(); i++)
				if (pipe[i].inRepare == status)
					index.push_back(i);
		}
		else if (name != "all" and status == -1) {
			for (int i = 0; i < pipe.size(); i++)
				if (pipe[i].name == name)
					index.push_back(i);
		}
		else {
			for (int i = 0; i < pipe.size(); i++)
				index.push_back(i);
		}
	}
	else
		for (int i = 0; i < pipe.size(); i++)
			index.push_back(i);
	return index;
}

void Pipe::AddPipe()
{
	Pipe p;
	cout << "Название трубы: ";
	cin.ignore(10000, '\n');
	getline(cin, p.name);
	cerr << p.name << endl;
	cout << "Длина трубы: ";
	float length = InputNum(0, 10000);
	p.length = length;
	cout << "Диаметр трубы: ";
	float diameter = InputNum(0, 10000);
	p.diameter = diameter;
	pipe.push_back(p);
}

void Pipe::ViewPipes()
{
	vector <int> indexes = filterPipes();
	cout << "Список труб:" << endl << endl;
	for (int i : indexes) {
		cout << "Id: " << pipe[i].id << endl;
		cout << "Номер: " << i + 1 << endl;
		cout << "Название трубы: " << pipe[i].name << endl;
		cout << "Длина трубы: " << pipe[i].length << endl;
		cout << "Диаметр трубы: " << pipe[i].diameter << endl;
		if (pipe[i].inRepare)
			cout << "Состояние: ВЫКЛ." << endl << endl;
		else
			cout << "Состояние: ВКЛ." << endl << endl;
	}
}

void Pipe::SaveDataPipes(std::ofstream& file)
{
	if (pipe.size() != 0) {
		file << 1 << " " << pipe.size() << " " << MaxId << endl;
		for (int i = 0; i < pipe.size(); i++) {
			file << pipe[i].name <<  endl;
			file << pipe[i].id << " " << pipe[i].length << " " << pipe[i].diameter << " " << pipe[i].inRepare << endl;
		}
	}
	else {
		file << 0 << endl;
	}
}

void Pipe::PipeDataLoad(std::ifstream& file)
{
	bool existPipe;
	int pipeCount;
	file >> existPipe;
	if (existPipe) {
		file >> pipeCount;
		file >> MaxId;
		for (int i = 0; i < pipeCount; i++) {
			Pipe pipes;
			file.ignore(10000, '\n');
			getline(file, pipes.name);
			file >> pipes.id;
			file >> pipes.length;
			file >> pipes.diameter;
			file >> pipes.inRepare;
			pipe.push_back(pipes);
		}
	}
}

void Pipe::PipeChange(const int& num)
{
	if (pipe.size() != 0) {
		cout << "Состояние:\n0.Работает\n1.Требуется ремонт\n";
		if (Choose(0, 1))
			pipe[num - 1].inRepare = true;
		else
			pipe[num - 1].inRepare = false;
	}
}

void Pipe::packagePipe()
{
	std::vector <int> index = indexes(pipe.size());
	cout << "0. Изменить состояние труб\n1. Удалить трубы";
	if (!Choose(0, 1))
	{
		cout << "Состояние:\n0.Работает\n1.Требуется ремонт\n";
		int status = Choose(0, 1);
		for (int i : index) {
			pipe[i - 1].inRepare = status;
		}
	}
	else
		pipe.erase(pipe.begin()+index[0]-1, pipe.begin()+index[index.size()-1]);
}
