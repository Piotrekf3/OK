#include "Instance.h"


Instance::Instance()
{

}

Instance::Instance(const int & solutions_number)
{
	//this->solutions_number = solutions_number;
	//this->solutions = new Solutions[solutions_number];
}

Instance::~Instance()
{
	delete[] this->solutions;
}

void Instance::generate_instance_to_file()
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

        file<<Constance::n_tasks<<";"<<endl;

        for ( int i = 1; i <= Constance::n_tasks; i++ ) //operacje
        {
            time_op1 = (rand()%20) + 1;
            time_op2 = (rand()%20) + 1;         //do poustawiania
			machine_number_one = 1;
            machine_number_two = 2;
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

void Instance::load_from_file(const string & filename)
{
	string temp;
	ifstream file;
	file.open(filename);
	getline(file, temp);
	for (int i = 0; i < Constance::n_tasks; i++)
	{
		getline(file, temp);
		tasks[i].get_operation1()->set_duration(temp[0]-'0');
		tasks[i].get_operation2()->set_duration(temp[2] - '0');
		tasks[i].set_ready_time(temp[8] - '0');
		tasks[i].set_index(i);
	}
	getline(file, temp);
	for (int i = 0; i <= Constance::n_maintenance*2; i++)
	{
		getline(file, temp);
		maintenance[i] = Operation(temp[6] - '0', temp[4] - '0', 1, temp[0] - '0');
	}
	file.close();
}