#pragma once
#include "Operation.h"
class Solutions
{
    public:
        Solutions();
        ~Solutions();
        Operation* get_machine_one();
        Operation* get_machine_two();
    private:
        Operation *machine_one[];
        Operation *machine_two[];
};
