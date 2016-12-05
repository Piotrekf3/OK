#include "Instance.h"


Instance::Instance()
{
    solutions = new Solutions[Constance::n_solutions];
}

Instance::~Instance()
{
//	delete[] this->solutions;
}

void Instance::generate_instance_to_file()
{
    int time_op1, time_op2, machine_number_one, machine_number_two, ready_time;
    srand(time(NULL));
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
         for ( int i = 1; i <= Constance::n_maintenance*2; i++ )  //maintenancy
        {
            if( i > Constance::n_maintenance ) machine_number_one = 2;
            else machine_number_one = 1;
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
	string temp2;
	ifstream file;
	int index1 = 0;
	int index2 = 0;
	file.open(filename);
	if (file.is_open())
	{
		getline(file, temp);
		temp2 = temp[0] + temp[1];
		solutions_number = atoi(temp2.c_str());
		for (int i = 0; i < Constance::n_tasks; i++)
		{
			getline(file, temp);
			while (temp[index2] != ';')
				index2++;
			temp2 = temp.substr(index1, index2);
			tasks[i].get_operation1()->set_duration(atoi(temp2.c_str()));

			index2++;
			index1 = index2;
			while (temp[index2] != ';')
				index2++;
			temp2 = temp.substr(index1, index2);
			tasks[i].get_operation2()->set_duration(atoi(temp2.c_str()));

			index2 = 0;
			for (int j = 0; j < 4; j++)
			{
				while (temp[index2] != ';')
					index2++;
				index2++;
			}

			temp2 = temp.substr(index2);
			temp2.pop_back();
			tasks[i].set_ready_time(atoi(temp2.c_str()));
			tasks[i].set_index(i);
			index1 = index2 = 0;
		}
		//wczytywanie maintenance
		int task_index = 0;
		int duration = 0;
		int start = 0;
		getline(file, temp);
		for (int i = 0; i < Constance::n_maintenance * 2; i++)
		{
			getline(file, temp);
			while (temp[index2] != ';')
				index2++;
			temp2 = temp.substr(index1, index2);
			task_index = atoi(temp2.c_str());
			cout << task_index << endl;

			index2++;
			while (temp[index2] != ';')
				index2++;

			index2++;
			index1 = index2;
			while (temp[index2] != ';')
				index2++;
			temp2 = temp.substr(index1, index2-index1);
			duration = atoi(temp2.c_str());

			index2++;
			index1 = index2;
			while (temp[index2] != ';')
				index2++;
			temp2 = temp.substr(index1, index2-index1);
			start = atoi(temp2.c_str());
			index1 = index2 = 0;
			maintenance[i] = Operation(start, duration, 1, task_index);
		}
	}
	else
		cout << "nie dziala" << endl;

	file.close();
}

void Instance::is_blocked( int time_on_machine, bool &blocked, int &index )
{
    int min = 1000;
    for ( int i = 1; i < Constance::n_tasks; i++ )
    {
        if ( tasks[i].get_ready_time() < min )
        {
            if ( tasks[i].get_ready_time() > time_on_machine /*&& notused*/ )
            {
                blocked = true;
                min = tasks[i].get_ready_time();
                index = i;
            }
            else if ( tasks[i].get_ready_time() <= time_on_machine /*&& notused*/ )
            {
                blocked = false;
                break;
            }
        }
        //potrzebna zmienna used ktora mowi czy operacja zostala wlozona do maszyny
    }
}

void Instance::generate_solutions()
{
    int n = Constance::n_operations, task_index, time_on_machine = 0, control = 0;
    bool blocked = false;
  //  Operation element;
  //  Operation *machine_one;
    for ( int i = 0; i < Constance::n_solutions; i++ )
    {
        for ( int j = 0; j < Constance::n_tasks; j++ ) //n_tasks bo tyle jest operacji na 1 maszynie
        {
            do
            {
                task_index = rand()%Constance::n_tasks;
                control++;
                if ( control > 100 )
                {
                    is_blocked( time_on_machine, blocked, task_index );
                    if ( blocked )
                    {
                        solutions[i].get_machine_one()[j] = tasks[task_index].get_operation1();
                        time_on_machine += tasks[task_index].get_operation1()->get_duration();
                        break;
                    }
                }
            }
            while( tasks[task_index].get_ready_time() > time_on_machine );

            if ( blocked == false )
            {
                //  element = *tasks[task_index].get_operation1();
                //   machine_one = solutions[i].get_machine_one();
                //   machine_one[j] = &element;   wtf?? nie moge przywpisac adrsu operacji do adresu pod wskaznikiem w tablicy
                time_on_machine += tasks[task_index].get_operation1()->get_duration();
            }
            n--;
            control = 0;
            blocked = false;
        }
    }
}
/*int target_function( int index )
{
    Operation *machine_one, *machine_two;
    int result = 0, result1 = 0, result2 = 0;
    machine_one = mutated_solutions[index]->get_machine_one();
    machine_two = mutated_solutions[index]->get_machine_two();
    for ( int i = 0; i < Constance::n_operations + Constance::n_maintenance; i++ )
    {
        if ( machine_one[i] != nullptr )
        {
            result1 = result1 + machine_one[i].get_duration();
        }
        if ( machine_two[i] != nullptr )
        {
            result2 = result2 + machine_two[i].get_duration();
        }
    }
    return result = (result1 > result2) ? result1 : result2;
}*/

void Instance::selection()
{
//    int index1, index2, candidate1, candidate2, winner;
   /* while( mutated_solutions.amount > 101)
    {
        do
        {
            index1 = rand()%mutated_solutions.length;
        }
        while( mutated_solutions[index] == nullptr );
        do
        {
            index2 = rand()%mutated_solutions.length;
        }
        while( mutated_solutions[index] == nullptr || index2 == indeks1 );
        candidate1 = target_function(index1);
        candidate2 = target_function(index2);
        if ( candidate1 > candidate2 ) mutated_solutions[index1] = nullptr;
        else mutated_solutions[index2] = nullptr;
        mutated_solutions.length--;
    }*/
}
