#include "Solutions.h"
#include <ctime>
#include <cstdlib>


Solutions::Solutions()
{
    for (int i = 0; i < (Constance::n_operations/2 + Constance::n_maintenance); i++ )
    {
        machine_one[i] = nullptr;
        machine_two[i] = nullptr;
    }
}
Solutions::~Solutions()
{
}
Operation** Solutions::get_machine_one()
{
    return machine_one;
}
Operation** Solutions::get_machine_two()
{
    return machine_two;
}
