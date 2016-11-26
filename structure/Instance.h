#pragma once
#include"Solutions.h"
class Instance
{
private:
	int solutions_number;
	Solutions* solutions;

public:
	Instance(const int & solutions_number);
	~Instance();
	void generate_instance();
};

