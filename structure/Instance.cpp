#include "Instance.h"
#include "Solutions.h"
#include "COnstance.h"
#include <fstream>
#include <string>
#include <sstream>
#include <iostream>
#include <ctime>
#include <cstdlib>

using namespace std;

Instance::Instance(const int & solutions_number)
{
	//this->solutions_number = solutions_number;
	//this->solutions = new Solutions[solutions_number];
}

Instance::~Instance()
{
	delete[] this->solutions;
}

void Instance::generate_instance()
{
    int time_op1, time_op2, machine_number_one, machine_number_two, ready_time;
    for( int i = 1; i <= Constance::n_instances; i++ )
    {
        ostringstream i_s;
        i_s<<i;                     //konwersja z int na string
        string file_name;
        file_name = "../Instances/Instancja" + i_s.str() + ".txt";   //nazwa pliku (scie¿ka)
        ofstream file;
        file.open(file_name.c_str());

        file<<Constance::n_operations/2<<";"<<endl;

        for ( int i = 1; i <= Constance::n_operations/2; i++ ) //operacje
        {
            time_op1 = (rand()%20) + 1;
            time_op2 = (rand()%20) + 1;         //do poustawiania
            machine_number_one=(rand()%2) + 1;
            if ( machine_number_one == 1 ) machine_number_two = 2;
            else machine_number_two = 1;
            ready_time = (rand()%6);


            file<<time_op1<<";"
                    <<time_op2<<";"
                            <<machine_number_one<<";"
                                    <<machine_number_two<<";"
                                            <<ready_time<<";"<<endl;
        }
        file<<"MAINTENANCE"<<endl;
        int start_maintenance = (rand()%6) + 5;
        for ( int i = 1; i <= Constance::n_maintenance; i++ )  //maintenancy
        {
            machine_number_one=(rand()%2) + 1;
            file<<i<<";"
                <<machine_number_one<<";"
                    <<Constance::duration_maintenance<<";"
                        <<start_maintenance<<";"<<endl;
            start_maintenance = start_maintenance + Constance::duration_maintenance + (rand()%10) + 1;
        }
        file.close();
    }
}
