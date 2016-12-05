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

	//solutions
	int solutions_number;
	Solutions* solutions;
	void is_blocked( int time_on_machine, bool &blocked, int &index );

public:
	Instance();
	~Instance();
	void generate_instance_to_file();
	void load_from_file(const string & filename);
	void generate_solutions();
	void selection();
	Task get_task(int index){ return tasks[index]; }
	Operation get_maintenance(int index){ return maintenance[index]; }
	Solutions  get_solution(int index){ return solutions[index]; }
};

