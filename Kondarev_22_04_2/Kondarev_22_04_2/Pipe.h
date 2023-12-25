#pragma once
#include <string>
#include <vector>
#include <fstream>
#include <map>


using namespace std;


class Pipe
{
private:
	
	string name;
	float length;
	
	bool inRepare = false;
public:
	int id;
	static int MaxId;
	bool NotiInConn = true;
	int diameter;

	Pipe();
	
	vector <Pipe> pipe;
	map <int, Pipe> pipes;

	vector <int> filterPipes();

	void AddPipe();
	void AddCurPipe(int n);
	void PipeChange(const int& num);
	void ViewPipes();
	void packagePipe();

	void SaveDataPipes(ofstream& file);

	void PipeDataLoad(ifstream& file);

	string getName();
	int getDiam();
	int getLength();
	bool getStatus();

	void setStatus(bool status);

	int getId();

};

