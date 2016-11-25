#include "Operation.h"
#include "Solutions.h"

void generuj()
{
   // n = n_operations;
   // for (int i = 0; i < n; i++)
   // {
     //   this->machine_one[i] = Task(start1, duration1, start2, duration2, ready_time, indeks);
     //   this->machine_two[i] = Task(start1, duration1, start2, duration2, ready_time, indeks);
    //}
}
Solutions::Solutions(Operation mechine_one, Operation mechine_two )
{
    generuj();
}
Solutions::~Solutions()
{
    for (int i = 0; i < (n_operations + n_maintenance); i++ )
    {
        machine_one[i]=nullptr;
        machine_two[i]=nullptr;
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
