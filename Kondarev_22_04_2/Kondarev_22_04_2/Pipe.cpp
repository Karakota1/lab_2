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
	if (pipe.size() != 0) {
		vector <int> index;
		string name;
		int status;
		cout << "\n0. ������ \n1. ���������� ��\n�������: ";
		if (!Choose(0, 1))
		{
			cout << "���: ";
			inputString(cin, name);
			cout << endl;

			cout << "0. �������� \n1. � �������";
			status = Choose(0, 1);

			for (int i = 0; i < pipe.size(); i++)
				if (pipe[i].name == name and pipe[i].inRepare == status)
					index.push_back(i);
		}
		else
			for (int i = 0; i < pipe.size(); i++)
				index.push_back(i);
		return index;
	}
	else
		return {};
}

void Pipe::AddPipe()
{
	Pipe p;
	cout << "�������� �����: ";
	cin.ignore(10000, '\n');
	getline(cin, p.name);
	cerr << p.name << endl;
	cout << "����� �����: ";
	float length = InputNum(0, 10000);
	p.length = length;
	cout << "������� �����: ";
	float diameter = InputNum(0, 10000);
	p.diameter = diameter;
	pipe.push_back(p);
}

void Pipe::ViewPipes()
{
	if (pipe.size()!=0) {
		vector <int> indexes = filterPipes();
		cout << "������ ����:" << endl << endl;
		for (auto i : indexes) {
			cout << "Id: " << pipe[i].id << endl;
			cout << "�����: " << i + 1 << endl;
			cout << "�������� �����: " << pipe[i].name << endl;
			cout << "����� �����: " << pipe[i].length << endl;
			cout << "������� �����: " << pipe[i].diameter << endl;
			if (pipe[i].inRepare)
				cout << "���������: ����." << endl << endl;
			else
				cout << "���������: ���." << endl << endl;
		}
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
		cout << "���������:\n0.��������\n1.��������� ������\n";
		if (Choose(0, 1))
			pipe[num - 1].inRepare = true;
		else
			pipe[num - 1].inRepare = false;
	}
}

void Pipe::packagePipe() //�������������, �������, ����������  ��� �������� �������������� ������ ��� �� ������� �������������!
{
	if (pipe.size() != 0) {
		cout << "0. ������������� �����\n1. ������� �����\n�������: ";
		int num = Choose(0, 2);
		int status;
		vector <int> index = filterPipes();
		switch (num)
		{
		case 0:
			cout << "���������:\n0.��������\n1.��������� ������\n";
			status = Choose(0, 1);
			for (int i : index) {
				pipe[i].inRepare = status;
			}
			break;
		case 1:
			for (int i = index.size() - 1; i >= 0; i--) {
				pipe.erase(pipe.begin() + index[i]);
			}
			break;
		}
	}
}