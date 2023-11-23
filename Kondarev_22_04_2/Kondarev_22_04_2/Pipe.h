#pragma once
#include <string>
#include <vector>
#include <fstream>
class Pipe
{
private:
	int id;
	std::string name;
	float length;
	float diameter;
	bool inRepare = false;
public:
	static int MaxId;


	Pipe();
	
	std::vector <Pipe> pipe;

	std::vector <int> filterPipes();

	void AddPipe();
	void PipeChange(const int& num);
	void ViewPipes();
	void packagePipe();

	void SaveDataPipes(std::ofstream& file);

	void PipeDataLoad(std::ifstream& file);

};

