#pragma once
#include <iostream>
#include <string>
#include <fstream>
#include <filesystem>


int Menu();

float InputNum(float min, float max);
int Choose(int min, int max);
void inputString(std::istream& in, std::string& str);
std::string ChooseFileName();
std::string ViewFiles(const std::string& path);

std::vector <int> indexes(const int& max_num);

class redirect_output_wrapper
{
	std::ostream& stream;
	std::streambuf* const old_buf;
public:
	redirect_output_wrapper(std::ostream& src)
		:old_buf(src.rdbuf()), stream(src)
	{
	}

	~redirect_output_wrapper() {
		stream.rdbuf(old_buf);
	}
	void redirect(std::ostream& dest)
	{
		stream.rdbuf(dest.rdbuf());
	}
};
