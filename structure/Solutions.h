#pragma once
#include "Operation.h"
#include"Constance.h"
class Solutions
{
    public:
        Solutions();
        ~Solutions();
        Operation* get_machine_one();
        Operation* get_machine_two();
    private:
        Operation *machine_one[Constance::n_operations+Constance::n_maintenance];
		Operation *machine_two[Constance::n_operations + Constance::n_maintenance];
};
