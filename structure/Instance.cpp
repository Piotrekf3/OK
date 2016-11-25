#include "Instance.h"


Instance::Instance(const int & solutions_number)
{
	this->solutions_number = solutions_number;
	this->solutions = new Solutions[solutions_number];
}

Instance::~Instance()
{
	delete[] this->solutions;
}

void Instance::generate_instance()
{

}