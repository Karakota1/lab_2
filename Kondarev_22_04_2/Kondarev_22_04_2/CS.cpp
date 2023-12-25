#include "Connection.h"

using namespace std;

int CS::workingStations(int index)
{
	int num = 0;
	for (int i = 0; i < Stations[index].wrkshopsCount; i++) {
		if (Stations[index].WS[i])
			num++;
	}
	return num;
}

std::vector<int> CS::filterCS()
{
	if (cs.size() != 0) {
		vector <int> index;
		string name;
		float status;
		cout << "\n0. ������ \n1. ���������� ��\n�������: ";
		if (!Choose(0, 1))
		{
			cout << "���: ";
			inputString(cin, name);
			cout << endl;

			cout << "������� ����������������� �����:";
			status = InputNum(0, 100);
			cout << endl;

			for (const auto& i: Stations)
				if (i.second.name == name and (i.second.wrkshopsCount - workingStations(i.first)) / i.second.wrkshopsCount * 100 == status)
					index.push_back(i.first);
		}
		else
			for (const auto& i : Stations)
				index.push_back(i.first);
		return index;
	}
	else
		return {};
}

void CS::AddCS()
{
	CS css;
	id = MaxIdCS++;
	cout << "������� �������� ��: ";
	cin.ignore(10000, '\n');
	getline(cin, css.name);
	cerr << css.name << endl;
	cout << "������� ����� ����� (1,1000): ";
	int count = Choose(1, 10000);
	for (int j = 0; j < count; j++) {
		css.WS.push_back(true);
	}
	cout << "������� ������������� (0,100): ";
	float effic = InputNum(0, 100);
	css.efficiency = effic;
	css.wrkshopsCount = count;
	cs.push_back(css);
	Stations.insert({ id, css });
	cout << Stations.size() << " " << MaxIdCS;
}

void CS::ViewWS(int& i) {
	if (cs.size() != 0) {
		for (int j = 0; j < cs[i].WS.size(); j++) {
			if (cs[i].WS[j])
				cout << "\t��� �" << j + 1 << "\t\t� ������� ���������" << endl;
			else
				cout << "\t��� �" << j + 1 << "\t\t�� � ������� ���������" << endl;
		}
	}
}

void CS::ViewCSs()
{
	if (Stations.size() != 0) {
		vector <int> indexes = filterCS();
		cout << "������ ��:" << endl << endl;
		for (int i : indexes) {
			cout << "ID: " << i << endl;
			//cout << "�����: " << i + 1 << endl;
			cout << "�������� ��: " << Stations[i].name << endl;
			cout << "����� �����: " << Stations[i].wrkshopsCount << endl << endl;
			cout << "������������� ��: " << Stations[i].efficiency << "%" << endl << endl;
			cout << "����� ������� �������: " << Stations[i].WS.size() << endl;
			cout << endl;
			//ViewWS(i); �� ���� ����� ������� ���������� �� ������� �������, �� ������� ����� - �������������
		}
	}
	
}

void CS::CSChange(const int& id_cs)
{
	if (cs.size() != 0) {
		for (int i = 0; i < cs[id_cs - 1].WS.size(); i++) {
			if (cs[id_cs - 1].WS[i])
				cout << "��� �" << i << "\t" << "� ������� ���������" << endl;
			else
				cout << "��� �" << i << "\t" << "� ��������� ���������" << endl;
		}
		cout << "\n\t�������� ��� ��� ��������������: ";
		int id_ws = Choose(1, cs[id_cs - 1].WS.size());
		cs[id_cs - 1].WS[id_ws - 1] = !cs[id_cs - 1].WS[id_ws - 1];
	}
}

void CS::packageCS()
{
	vector <int> index = filterCS();
	for (auto i : index) {
		std::cout << "��������: " << Stations[i].name << endl;
		std::cout << "���-�� �������: " << Stations[i].wrkshopsCount << endl;
		std::cout << "�������������: " << Stations[i].efficiency << endl;
	}
	cout << "\n0.�������������\n1.�������\n�������:  ";
	int num = Choose(0, 2);
	string new_name;
	switch (num) {
	case 0:
		cout << "������� ����� �������� ��� ��: ";
		inputString(cin, new_name);
		for (int i : index) {
			Stations[i].name = new_name;
		}
		break;
	case 1:
		for (int i = index.size() - 1; i >= 0; i--) {
			Stations.erase(index[i]);//����� �� ������� ��������� ��������, ���� ���������, ��� �� ����� �� ������� �����-�� ������, ������, �� ������ ������. ������ ������!
		}
		break;
	}
}

void CS::SaveDataCS(std::ofstream& file)
{
	if (Stations.size() != 0) {
		file << 1 << " " << Stations.size() << " " << MaxIdCS << endl;
		for (const auto& [id,st] : Stations) {
			file << st.name << endl;
			file << id << " " << st.wrkshopsCount << " " << st.efficiency << endl;
			for (bool WS : st.WS) {
				file << WS << " ";
			}
			file << endl;
		}
	}
	else {
		file << 0 << endl;
	}
}

void CS::CSDataLoad(std::ifstream& file)
{
	bool existCS;
	int csCount;
	file >> existCS;
	if (existCS) {
		file >> csCount;
		file >> MaxIdCS;
		for (int i = 0; i < csCount; i++) {
			CS css;
			file.ignore(10000, '\n');
			getline(file, css.name);
			file >> css.id;
			file >> css.wrkshopsCount;
			file >> css.efficiency;
			css.WS.resize(css.wrkshopsCount);
			for (int i = 0; i < css.WS.size(); i++) { //�������� �� � WS
				bool ws;
				file >> ws;
				css.WS[i] = ws;

			}
			cs.push_back(css);
			Stations.insert({css.id,css});
		}
	}
}

std::string CS::getName()
{
	return name;
}

int CS::getWSnum()
{
	return wrkshopsCount;
}
