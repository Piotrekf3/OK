#pragma once
#include"Solutions.h"
#include"Task.h"
#include <fstream>
#include <string>
#include <sstream>
#include <iostream>
#include <ctime>
#include <cstdlib>
using namespace std;

class Instance
{
private:
	Task tasks [Constance::n_tasks];
	
	//solutions
	int solutions_number;
	Solutions* solutions;

public:
	Instance();
	Instance(const int & solutions_number);
	~Instance();
	void generate_instance_to_file();
	void load_from_file(const string & filename);
};

