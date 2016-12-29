#pragma once
#include "Operation.h"
#include"Constance.h"
class Solutions
{
    private:
        Operation *machine_one[Constance::n_operations/2 + Constance::n_maintenance];
		Operation *machine_two[Constance::n_operations/2 + Constance::n_maintenance];
    public:
        //int solution_indeks;
        //bool set_solution_indeks(int indeks);
        Solutions();
        ~Solutions();
        Operation** get_machine_one();
        Operation** get_machine_two();
};
