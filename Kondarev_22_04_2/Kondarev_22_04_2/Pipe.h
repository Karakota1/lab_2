#pragma once
#include <string>
class Pipe
{
public:
	int id;
	std::string name;
	int length;
	int diameter;
	bool inRepare = false;

	std::string getName() const;
	
	void setName(std::string new_name);
};

