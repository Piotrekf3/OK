#include "Solutions.h"
#include <ctime>
#include <cstdlib>


Solutions::Solutions()
{
}
Solutions::~Solutions()
{
    for (int i = 0; i < (Constance::n_operations + Constance::n_maintenance); i++ )
    {
//        delete [] machine_one[i];
  //      delete [] machine_two[i];
    }
}
Operation* Solutions::get_machine_one()
{
    return *machine_one;
}
Operation* Solutions::get_machine_two()
{
    return *machine_two;
}
