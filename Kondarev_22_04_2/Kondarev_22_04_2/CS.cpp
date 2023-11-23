#include "CS.h"
#include "Subfuncs.h"

using namespace std;

int CS::MaxIdCS = 0;

CS::CS() {
	id = MaxIdCS++;
}

int CS::workingStations(int index)
{
	int num = 0;
	for (int i = 0; i < cs[index].wrkshopsCount; i++) {
		if (cs[index].WS[i])
			num++;
	}
	return num;
}

std::vector<int> CS::filterCS()
{
	vector <int> index;
	string name = "all";
	float status = -1;
	cout << "\n0. ������ \n1. ���������� ��\n�������: ";
	if (!Choose(0, 1))
	{
		cout << "����� �� �������� \n0. ��\n1. ���\n�������: " << endl;
		if (!Choose(0, 1))
		{
			cout << "���: ";
			inputString(cin, name);
			cout << endl;
		}
		cout << "����� �� �������� ����������������� �����: \n0. ��\n1.���\n�������: " << endl;
		if (!Choose(0, 1))
		{
			cout << "������� ����������������� �����:";
			status = InputNum(0, 100);
			cout << endl;
		}

		if (name != "all" and status != -1) {
			for (int i = 0; i < cs.size(); i++)
				if (cs[i].name == name and (cs[i].wrkshopsCount - workingStations(i)) / cs[i].wrkshopsCount * 100 == status)
					index.push_back(i);
		}
		else if (name == "all" and status != -1) {
			for (int i = 0; i < cs.size(); i++)
				if ((cs[i].wrkshopsCount - workingStations(i)) / cs[i].wrkshopsCount * 100 == status)
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

void CS::AddCS()
{
	CS css;
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
}

void CS::ViewWS(int& i) {
	for (int j = 0; j < cs[i].WS.size(); j++) {
		if (cs[i].WS[j])
			cout << "\t��� �" << j + 1 << "\t\t� ������� ���������" << endl;
		else
			cout << "\t��� �" << j + 1 << "\t\t�� � ������� ���������" << endl;
	}
}

void CS::ViewCSs()
{
	vector <int> indexes = filterCS();
	cout << "������ ��:" << endl << endl;
	for (int i : indexes) {
		cout << "ID: " << cs[i].id << endl;
		cout << "�����: " << i+1 << endl;
		cout << "�������� ��: " << cs[i].name << endl;
		cout << "����� �����: " << cs[i].wrkshopsCount << endl << endl;
		cout << "������������� ��: " << cs[i].efficiency << "%" << endl << endl;
		cout << endl;
		ViewWS(i);
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
	vector <int> index = indexes(cs.size());
	cout << "\n0.�������� �������� ��\n1.������� ��\n�������: ";
	if (!Choose(0, 1)) {
		string new_name;
		cout << "������� ����� �������� ��� ��: ";
		cin.ignore(10000,'\n');
		getline(cin,new_name);
		for (int i : index) {
			cs[i-1].name = new_name;
		}
	}
	else {
		cs.erase(cs.begin() + index[0] - 1,cs.begin()+index[index.size()-1]);
	}
}

void CS::SaveDataCS(std::ofstream& file)
{
	if (cs.size() != 0) {
		file << 1 << " " << cs.size() << " " << MaxIdCS << endl;
		for (int i = 0; i < cs.size(); i++) {
			file << cs[i].name << endl;
			file << cs[i].id << " " << cs[i].wrkshopsCount << " " << cs[i].efficiency << endl;
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
		}
	}
}
