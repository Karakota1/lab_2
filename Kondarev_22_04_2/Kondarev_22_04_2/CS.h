#pragma once
#include <string>
#include <vector>
#include <fstream>
class CS
{
	int id;
	std::string name;
	int wrkshopsCount;
	std::vector <bool> WS;
	float efficiency;
public:
	static int MaxIdCS;

	CS();

	int workingStations(int index);

	std::vector <CS> cs;


	std::vector <int> filterCS();

	void AddCS();
	void ViewWS(int& i);
	void ViewCSs();
	void CSChange(const int& id_cs);
	void packageCS();

	void SaveDataCS(std::ofstream& file);
	void CSDataLoad(std::ifstream& file);


};

