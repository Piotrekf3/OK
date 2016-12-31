#pragma once
#include "Operation.h"
#include"Constance.h"
#include<iostream>
#include<algorithm>
class Solutions
{
    private:
		int machine_one_operations_number;
		int machine_two_operations_number;
        Operation *machine_one[Constance::n_operations/2 + Constance::n_maintenance];
		Operation *machine_two[Constance::n_operations/2 + Constance::n_maintenance];
    public:
        //int solution_indeks;
        //bool set_solution_indeks(int indeks);
        Solutions();
        ~Solutions();
		void insertion_sort_machine_one(int operations_on_machine);
		void insertion_sort_machine_two(int operations_on_machine);
		int get_machine_one_operations_number(){ return machine_one_operations_number; }
		int get_machine_two_operations_number() { return machine_two_operations_number; }
		//wstawia w pierwsze wolne miejsce, jako insert time podaæ ready time
		void insert_operation(int machine_number, Operation * operation, int & inserted_end_time, int insert_time = 0);
		void show(int machine);
        Operation** get_machine_one();
        Operation** get_machine_two();
};
