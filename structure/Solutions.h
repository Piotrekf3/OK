#pragma once
#include "operation.h"
class Solutions
{
    public:
        enum{n_operations=50,n_maintenance=5};
        Solutions( Operation mechine_one, Operation machine_two );
        ~Solutions();
        static const int get_n_operations();
        static const int get_n_maintenance();
        Operation* get_machine_one();
        Operation* get_machine_two();
    private:
        Operation *machine_one[n_operations];
        Operation *machine_two[n_maintenance];
};
