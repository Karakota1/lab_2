#include "Pipe.h"
#include "Subfuncs.h"

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



			//for(int id=0;id<pipe.size();id++)
			for (const auto& [id,p] : pipes)
				if (p.name == name and p.inRepare == status)
					index.push_back(id);
		}
		else
			for (const auto& [id,p]: pipes)
				index.push_back(id);
			//for (int id = 0; id < pipe.size(); id++)
			//	//for (const auto& [id,p] : pipes)
			//		index.push_back(id);
		return index;
	}
	else
		return {};
}

void Pipe::AddPipe()
{
	Pipe p;
	id++;
	cout << "�������� �����: ";
	cin.ignore(10000, '\n');
	getline(cin, p.name);
	cerr << p.name << endl;
	cout << "����� �����: ";
	float length = InputNum(0, 10000);
	p.length = length;
	cout << "������� �����:\n1.500\n2.700\n3.1000\n4.1400 ";
	float diameter = InputNum(1, 4);
	p.diameter = diameter == 1 ? 500: diameter == 2 ? 700: diameter == 3 ? 1000:1400;
	pipe.push_back(p);
	pipes.insert({id,p});
}

void Pipe::ViewPipes()
{
	if (pipes.size()!=0) {
		vector <int> indexes = filterPipes();
		cout << "������ ����:" << endl << endl;
		for (auto id : indexes) {
			cout << "Id: " << pipes[id].id << endl;
			//cout << "�����: " << id + 1 << endl;
			cout << "�������� �����: " << pipes[id].name << endl;
			cout << "����� �����: " << pipes[id].length << endl;
			cout << "������� �����: " << pipes[id].diameter << endl;
			if (pipes[id].inRepare)
				cout << "���������: ����." << endl << endl;
			else
				cout << "���������: ���." << endl << endl;
		}
	}
}

bool Pipe::getStatus()
{
	return NotiInConn;
}

void Pipe::SaveDataPipes(std::ofstream& file)
{
	if (pipes.size() != 0) {
		file << 1 << " " << pipes.size() << " " << MaxId << endl;
		for (const auto& [id,p]: pipes) {
			file << p.name <<  endl;
			file << id << " " << p.length << " " << p.diameter << " " << p.inRepare << endl;
		}
	}
	else {
		file << 0 << endl;
	}
}

void Pipe::setStatus(bool status)
{
	NotiInConn = status;
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
			Pipe pip;
			file.ignore(10000, '\n');
			getline(file, pip.name);
			file >> pip.id;
			file >> pip.length;
			file >> pip.diameter;
			file >> pip.inRepare;
			pipe.push_back(pip);
			pipes.insert({pip.id,pip});
		}
	}
}

int Pipe::getId()
{
	return id;
}

void Pipe::PipeChange(const int& num)
{
	if (pipes.size() != 0) {
		cout << "���������:\n0.��������� ������\n1.��������\n";
		bool status = Choose(0, 1);
		pipes[num].inRepare = status;
	}
}

void Pipe::AddCurPipe(int di)
{
	Pipe p;
	id++;
	cout << "�������� �����: ";
	cin.ignore(10000, '\n');
	getline(cin, p.name);
	cerr << p.name << endl;
	cout << "����� �����: ";
	float length = InputNum(0, 10000);
	p.length = length;
	p.diameter = di;
	p.NotiInConn = false;
	pipe.push_back(p);
	pipes.insert({id, p});
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
				pipes[i].inRepare = status;
			}
			break;
		case 1:
			for (int i = index.size() - 1; i >= 0; i--) {
				pipes.erase(index[i]);
			}
			break;
		}
	}
}

int Pipe::getDiam() {
	return diameter;
}

std::string Pipe::getName()
{
	return name;
}

int Pipe::getLength()
{
	return length;
}