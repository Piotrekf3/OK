#include "Solutions.h"
#include <ctime>
#include <cstdlib>

void generuj()
{
 //   int n = n_operations;
//    for (int i = 0; i < n; i++)
    {
   //     this->machine_one[i] = Task(start1, duration1, start2, duration2, ready_time, indeks);
     //   this->machine_two[i] = Task(start1, duration1, start2, duration2, ready_time, indeks);
    }
}
Solutions::Solutions() //usunalem tu 2 argumenty machine_one i two, bo cmetoda generuj ma generowac maszyny a nie ze uczytkownik wywoluje konstruktor z maszynami, tak mysle przynajmniej//nom masz racjê pozdro :)
{
    generuj();
}
Solutions::~Solutions()
{
    for (int i = 0; i < (Constance::n_operations + Constance::n_maintenance); i++ )
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
