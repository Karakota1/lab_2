#include "Pipe.h"

std::string Pipe::getName() const
{
	return name;
}

void Pipe::setName(std::string new_name)
{
	name = new_name;
}
