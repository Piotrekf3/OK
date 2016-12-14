#include "Instance.h"
#include <windows.h>

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
			//cout << task_index << endl;

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


void Instance::insertion_sort( int index, int operations_on_machine )
{
    int j;
    Operation* pom;
    for ( int i = 1; i < operations_on_machine; i++ )
    {
        j = i - 1;
        while ( (solutions[index].get_machine_one()[j + 1]->get_start() < solutions[index].get_machine_one()[j]->get_start()) && (j >= 0) )
        {
            pom = solutions[index].get_machine_one()[j + 1];
            solutions[index].get_machine_one()[j + 1] = solutions[index].get_machine_one()[j];
            solutions[index].get_machine_one()[j] = pom;
            j--;
        }
    }
}

void Instance::generate_solutions()
{
    int task_index = rand()%(Constance::n_tasks), used[Constance::n_tasks];

    for ( int i = 0; i < Constance::n_tasks; i++ ) used[i] = 0;
//maszyna  nr  1
cout<<"zaczynamy"<<endl;
    for ( int i = 0; i < 1/*Constance::n_solutions*/; i++ )
    {
        cout<<"1 rozwiazanie"<<endl;
        for ( int k = 0; k < Constance::n_maintenance; k++ )
        {
            solutions[i].get_machine_one()[k] = &maintenance[k];
        }
        cout<<"main wstawione"<<endl;
        int j = 0, operations_on_machine = 5;
        while ( j < Constance::n_tasks )
        {
            while( used[task_index] == 1 )  task_index = rand()%(Constance::n_tasks);
            //cout<<"maintenance"<<solutions[i].get_machine_one()[0]->get_start()<<endl;
            cout<<"losowanie "<<j<<" zadanie "<<task_index<<" ready_time "<<tasks[task_index].get_ready_time()<<" duration "<<tasks[task_index].get_operation1()->get_duration()<<endl;
            int index_on_machine = 0;
            while( index_on_machine < Constance::n_tasks + Constance::n_maintenance )
            {
                if( index_on_machine == 0 )
                {
                    if( tasks[task_index].get_ready_time() + tasks[task_index].get_operation1()->get_duration() < solutions[i].get_machine_one()[index_on_machine]->get_start())
                    {
                        tasks[task_index].get_operation1()->set_start( tasks[task_index].get_ready_time() );
                        solutions[i].get_machine_one()[operations_on_machine] = tasks[task_index].get_operation1();
                       // cout<<"index_on_machine "<<index_on_machine<<endl;
                        break;
                    }
                }
                else if(  solutions[i].get_machine_one()[index_on_machine] == nullptr )
                {
                        if( tasks[task_index].get_ready_time() <= solutions[i].get_machine_one()[index_on_machine - 1]->get_start() + solutions[i].get_machine_one()[index_on_machine - 1]->get_duration())
                        {
                            tasks[task_index].get_operation1()->set_start( solutions[i].get_machine_one()[index_on_machine - 1]->get_start() + solutions[i].get_machine_one()[index_on_machine - 1]->get_duration() );
                            solutions[i].get_machine_one()[operations_on_machine] = tasks[task_index].get_operation1();
                            break;
                        }
                        else
                        {
                            tasks[task_index].get_operation1()->set_start( tasks[task_index].get_ready_time() );
                            solutions[i].get_machine_one()[operations_on_machine] = tasks[task_index].get_operation1();
                            break;
                        }
                }
                else
                {
                    if( (tasks[task_index].get_ready_time() <= solutions[i].get_machine_one()[index_on_machine - 1]->get_start() + solutions[i].get_machine_one()[index_on_machine - 1]->get_duration()) &&
                        solutions[i].get_machine_one()[index_on_machine - 1]->get_start() + solutions[i].get_machine_one()[index_on_machine - 1]->get_duration() + tasks[task_index].get_operation1()->get_duration() < solutions[i].get_machine_one()[index_on_machine]->get_start())
                    {
                        tasks[task_index].get_operation1()->set_start( solutions[i].get_machine_one()[index_on_machine - 1]->get_start() + solutions[i].get_machine_one()[index_on_machine - 1]->get_duration() );
                        solutions[i].get_machine_one()[operations_on_machine] = tasks[task_index].get_operation1();
                       // cout<<"index_on_machine else"<<index_on_machine<<endl;
                        break;
                    }

                }
                index_on_machine++;
            }
            cout<<"indeks w ktorym wstawilem"<<operations_on_machine<<endl;
            operations_on_machine++;
            cout<<"sortuje..."<<endl;
            insertion_sort(i,operations_on_machine);
            cout<<"koniec sortowania"<<endl;

            used[task_index] = 1;
            j++;
            //cout<<"wypisz"<<j;
            //cout<<solutions[i].get_machine_one()[index_on_machine]->get_start()<<";"<<
            //solutions[i].get_machine_one()[index_on_machine]->get_duration()<<";"<<
            //task_index<<";"<<endl;
            //control = 0;
           // blocked = false;
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
