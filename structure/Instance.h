#pragma once
#include"Solutions.h"
#include"Task.h"
#include <fstream>
#include <string>
#include <sstream>
#include <iostream>
#include <ctime>
#include <cstdlib>
#include<iostream>
using namespace std;

class Instance
{
private:
	Task tasks [Constance::n_tasks];
	Operation maintenance[Constance::n_maintenance*2];

	//solutions
	int solutions_number;
	Solutions* solutions;
	
	int crossed_solutions_number;
	Solutions* crossed_solutions;

	void insertion_sort_machine_one( int index, int operations_on_machine );
	void insertion_sort_machine_two( int index, int operations_on_machine );
	int target_function( int index );

public:
	Instance();
	~Instance();
	void generate_instance_to_file();
	void load_from_file(const string & filename);
	void generate_solutions();
	void save_solution_to_file( int solution_number );
	void selection();
	Task get_task(int index){ return tasks[index]; }
	Operation get_maintenance(int index){ return maintenance[index]; }
	Solutions  get_solution(int index){ return solutions[index]; }
	void crossing(); //potrzebuje tablicy crossed_solutions
};

