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
	Operation maintenance[Constance::n_maintenance*2];
	int machine[Constance::n_maintenance]; //na ktorej maszynie jest maintenance
	
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

