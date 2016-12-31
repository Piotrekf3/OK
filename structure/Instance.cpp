#include "Instance.h"
#include <windows.h>
#include <algorithm>

Instance::Instance()
{
    solutions = new Solutions[Constance::n_solutions + Constance::crossed_solutions];
	solutions_number = Constance::n_solutions;
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
			maintenance[i] = Operation(start, duration, true, task_index);
		}
	}
	else
		cout << "nie dziala" << endl;

	file.close();
}

void Instance::save_solution_to_file( int solution_number )
{
    int best_time, begin_time, idle_index_m1 = 1, maintenance_index_m1 = 1, idle_index_m2 = 1, maintenance_index_m2 = 1, all_idle_duration_m1 = 0,
    all_idle_duration_m2 = 0;
    ostringstream i_s;
    string file_name;
    ofstream file;

    i_s<<solution_number + 1;                     //konwersja z int na string
    file_name = "../Solutions/Solution" + i_s.str() + ".txt";   //nazwa pliku (scie¿ka)
    file.open(file_name.c_str());
    begin_time = target_function( solution_number );
    best_time = 100; //zmienic
    file<<best_time<<","<<
            begin_time<<endl;
    file<<"M1: ";
    for( int i = 0; i < Constance::n_tasks + Constance::n_maintenance; i++ )
    {
        if( i == 0 && solutions[solution_number].get_machine_one()[i]->get_start() != 0 )
        {
            file<<"idle"<<idle_index_m1<<"_"<<"M1,0,"<<solutions[solution_number].get_machine_one()[i]->get_start()<<",";
            idle_index_m1++;
            all_idle_duration_m1 += solutions[solution_number].get_machine_one()[i]->get_start();
        }
        else if( solutions[solution_number].get_machine_one()[i - 1]->get_start() + solutions[solution_number].get_machine_one()[i - 1]->get_duration() !=
                solutions[solution_number].get_machine_one()[i]->get_start() )
        {
            file<<"idle"<<idle_index_m1<<"_"<<"M1,"<<
                solutions[solution_number].get_machine_one()[i - 1]->get_start() + solutions[solution_number].get_machine_one()[i - 1]->get_duration()<<
                    ","<<solutions[solution_number].get_machine_one()[i]->get_start() -
                        (solutions[solution_number].get_machine_one()[i - 1]->get_start() + solutions[solution_number].get_machine_one()[i - 1]->get_duration())<<",";
            idle_index_m1++;
            all_idle_duration_m1 += solutions[solution_number].get_machine_one()[i]->get_start() -
                (solutions[solution_number].get_machine_one()[i - 1]->get_start() + solutions[solution_number].get_machine_one()[i - 1]->get_duration());
        }
        if( solutions[solution_number].get_machine_one()[i]->is_maintenance() )
        {
            file<<"maint"<<maintenance_index_m1<<"_M1,"<<
                solutions[solution_number].get_machine_one()[i]->get_start()<<
                    ","<<solutions[solution_number].get_machine_one()[i]->get_duration()<<",";
            maintenance_index_m1++;
        }
        else    file<<"op1_"<<solutions[solution_number].get_machine_one()[i]->get_task_index()<<
                    ","<<solutions[solution_number].get_machine_one()[i]->get_start()<<
                        ","<<solutions[solution_number].get_machine_one()[i]->get_duration()<<",";
    }
    file<<endl<<"M2: ";
    for( int i = 0; i < Constance::n_tasks + Constance::n_maintenance; i++ )
    {
        if( i == 0 && solutions[solution_number].get_machine_two()[i]->get_start() != 0 )
        {
            file<<"idle"<<idle_index_m2<<"_"<<"M2,0,"<<solutions[solution_number].get_machine_two()[i]->get_start()<<",";
            idle_index_m2++;
            all_idle_duration_m2 += solutions[solution_number].get_machine_two()[i]->get_start();
        }
        else if( solutions[solution_number].get_machine_two()[i - 1]->get_start() + solutions[solution_number].get_machine_two()[i - 1]->get_duration() !=
                solutions[solution_number].get_machine_two()[i]->get_start() )
        {
            file<<"idle"<<idle_index_m2<<"_"<<"M2,"<<
                solutions[solution_number].get_machine_two()[i - 1]->get_start() + solutions[solution_number].get_machine_two()[i - 1]->get_duration()<<
                    ","<<solutions[solution_number].get_machine_two()[i]->get_start() -
                        (solutions[solution_number].get_machine_two()[i - 1]->get_start() + solutions[solution_number].get_machine_two()[i - 1]->get_duration())<<",";
            idle_index_m2++;
            all_idle_duration_m2 += solutions[solution_number].get_machine_two()[i]->get_start() -
                (solutions[solution_number].get_machine_two()[i - 1]->get_start() + solutions[solution_number].get_machine_two()[i - 1]->get_duration());
        }
        if( solutions[solution_number].get_machine_two()[i]->is_maintenance() )
        {
            file<<"maint"<<maintenance_index_m2<<"_M2,"<<
                solutions[solution_number].get_machine_two()[i]->get_start()<<
                    ","<<solutions[solution_number].get_machine_two()[i]->get_duration()<<",";
            maintenance_index_m2++;
        }
        else    file<<"op2_"<<solutions[solution_number].get_machine_two()[i]->get_task_index()<<
                    ","<<solutions[solution_number].get_machine_two()[i]->get_start()<<
                        ","<<solutions[solution_number].get_machine_two()[i]->get_duration()<<",";
    }
    file<<endl<<"M1_maint: "<<maintenance_index_m1<<","<<maintenance_index_m1 * Constance::duration_maintenance<<endl<<
        "M2_maint: "<<maintenance_index_m2<<","<<maintenance_index_m2 * Constance::duration_maintenance<<endl<<
            "M1_idle: "<<idle_index_m1<<","<<all_idle_duration_m1<<endl<<
                "M2_idle: "<<idle_index_m2<<","<<all_idle_duration_m2<<endl;
    file.close();
}

void Instance::insertion_sort_machine_one( int index, int operations_on_machine )
{
    int j;
    Operation* pom;
    for ( int i = 1; i < operations_on_machine; i++ )
    {
        j = i - 1;
        while ( (j >= 0) && (solutions[index].get_machine_one()[j + 1]->get_start() < solutions[index].get_machine_one()[j]->get_start()) )
        {
            pom = solutions[index].get_machine_one()[j + 1];
            solutions[index].get_machine_one()[j + 1] = solutions[index].get_machine_one()[j];
            solutions[index].get_machine_one()[j] = pom;
            j--;
        }
    }
}

void Instance::insertion_sort_machine_two( int index, int operations_on_machine )
{
    int j;
    Operation* pom;
    for ( int i = 1; i < operations_on_machine; i++ )
    {
        j = i - 1;
        while ( (j >= 0) && (solutions[index].get_machine_two()[j + 1]->get_start() < solutions[index].get_machine_two()[j]->get_start()) )
        {
            pom = solutions[index].get_machine_two()[j + 1];
            solutions[index].get_machine_two()[j + 1] = solutions[index].get_machine_two()[j];
            solutions[index].get_machine_two()[j] = pom;
            j--;
        }
    }
}

void Instance::insertion_sort_solutions( int chosen_solutions_amount )
{
    int j;
    Solutions pom;
    for ( int i = chosen_solutions_amount + 1; i < Constance::crossed_solutions; i++ )
    {
        j = i - 1;
        while ( (j >= 0) && (target_function( j + 1 ) < target_function( j )) )
        {
            pom = solutions[j + 1];
            solutions[j + 1] = solutions[j];
            solutions[j] = pom;
            j--;
        }
    }
}

void Instance::generate_solutions()
{
    int task_index, used[Constance::n_tasks], index_on_machine, j, operations_on_machine;

    for ( int ind = 0; ind < Constance::n_solutions; ind++ )
    {
        for ( int i = 0; i < Constance::n_tasks; i++ ) used[i] = 0;
        j = 0;
        task_index = rand()%(Constance::n_tasks);
        index_on_machine = 0;
        operations_on_machine = 5;
        //maszyna  nr  1
        for ( int k = 0; k < Constance::n_maintenance; k++ )
        {
            solutions[ind].get_machine_one()[k] = &maintenance[k];
        }

        while ( j < Constance::n_tasks )
        {
            while( used[task_index] == 1 )  task_index = rand()%(Constance::n_tasks);

            index_on_machine = 0;
            while( index_on_machine < Constance::n_tasks + Constance::n_maintenance )
            {
                if( index_on_machine == 0 )
                {
                    if( tasks[task_index].get_ready_time() + tasks[task_index].get_operation1()->get_duration() < solutions[ind].get_machine_one()[index_on_machine]->get_start())
                    {
                        tasks[task_index].get_operation1()->set_start( tasks[task_index].get_ready_time() );
                        solutions[ind].get_machine_one()[operations_on_machine] = new Operation(*tasks[task_index].get_operation1());
                        break;
                    }
                }
                else if(  solutions[ind].get_machine_one()[index_on_machine] == nullptr )
                {
                        if( tasks[task_index].get_ready_time() <= solutions[ind].get_machine_one()[index_on_machine - 1]->get_start() + solutions[ind].get_machine_one()[index_on_machine - 1]->get_duration())
                        {
                            tasks[task_index].get_operation1()->set_start( solutions[ind].get_machine_one()[index_on_machine - 1]->get_start() + solutions[ind].get_machine_one()[index_on_machine - 1]->get_duration() );
                            solutions[ind].get_machine_one()[operations_on_machine] = new Operation(*tasks[task_index].get_operation1());
                            break;
                        }
                        else
                        {
                            tasks[task_index].get_operation1()->set_start( tasks[task_index].get_ready_time() );
                            solutions[ind].get_machine_one()[operations_on_machine] = new Operation(*tasks[task_index].get_operation1());
                            break;
                        }
                }
                else
                {
                    if( (tasks[task_index].get_ready_time() <= solutions[ind].get_machine_one()[index_on_machine - 1]->get_start() + solutions[ind].get_machine_one()[index_on_machine - 1]->get_duration()) &&
                        solutions[ind].get_machine_one()[index_on_machine - 1]->get_start() + solutions[ind].get_machine_one()[index_on_machine - 1]->get_duration() + tasks[task_index].get_operation1()->get_duration() < solutions[ind].get_machine_one()[index_on_machine]->get_start())
                    {
                        tasks[task_index].get_operation1()->set_start( solutions[ind].get_machine_one()[index_on_machine - 1]->get_start() + solutions[ind].get_machine_one()[index_on_machine - 1]->get_duration() );
                        solutions[ind].get_machine_one()[operations_on_machine] = new Operation(*tasks[task_index].get_operation1());
                        break;
                    }

                }
                index_on_machine++;
            }
            operations_on_machine++;
            insertion_sort_machine_one(ind,operations_on_machine);
            used[task_index] = 1;
            j++;

        }
        //maszyna nr 2
        for ( int i = 0; i < Constance::n_tasks; i++ ) used[i] = 0;
        index_on_machine = 0;
        j = 0;

        task_index = rand()%(Constance::n_tasks);

        for ( int k = 5 ; k < Constance::n_maintenance * 2; k++ )
        {
            solutions[ind].get_machine_two()[k - 5] = &maintenance[k];
        }
        operations_on_machine = 5;

        while ( j < Constance::n_tasks )
        {
            while( used[task_index] == 1 )  task_index = rand()%(Constance::n_tasks);

            index_on_machine = 0;
            while( index_on_machine < Constance::n_tasks + Constance::n_maintenance )
            {
                if( index_on_machine == 0 )
                {//zmiana ponizszego warunku
                    if( tasks[task_index].get_operation1()->get_start() + tasks[task_index].get_operation1()->get_duration() + tasks[task_index].get_operation2()->get_duration() < solutions[ind].get_machine_two()[index_on_machine]->get_start() )
                    {
                        tasks[task_index].get_operation2()->set_start( tasks[task_index].get_operation1()->get_start() + tasks[task_index].get_operation1()->get_duration() );
                        solutions[ind].get_machine_two()[operations_on_machine] = new Operation(*tasks[task_index].get_operation2());
                        break;
                    }
                }
                else if(  solutions[ind].get_machine_two()[index_on_machine] == nullptr )
                {
                    tasks[task_index].get_operation2()->set_start( solutions[ind].get_machine_two()[index_on_machine - 1]->get_start() + solutions[ind].get_machine_two()[index_on_machine - 1]->get_duration() );
                    solutions[ind].get_machine_two()[operations_on_machine] = new Operation(*tasks[task_index].get_operation2());
                    break;
                }
                else
                {
                    if( (tasks[task_index].get_operation1()->get_start() + tasks[task_index].get_operation1()->get_duration() <= solutions[ind].get_machine_two()[index_on_machine - 1]->get_start() + solutions[ind].get_machine_two()[index_on_machine - 1]->get_duration()) &&
                        solutions[ind].get_machine_two()[index_on_machine - 1]->get_start() + solutions[ind].get_machine_two()[index_on_machine - 1]->get_duration() + tasks[task_index].get_operation2()->get_duration() < solutions[ind].get_machine_two()[index_on_machine]->get_start())
                    {
                        tasks[task_index].get_operation2()->set_start( solutions[ind].get_machine_two()[index_on_machine - 1]->get_start() + solutions[ind].get_machine_two()[index_on_machine - 1]->get_duration() );
                        solutions[ind].get_machine_two()[operations_on_machine] = new Operation(*tasks[task_index].get_operation2());
                        break;
                    }
                }
                index_on_machine++;
            }
            operations_on_machine++;
            insertion_sort_machine_two(ind,operations_on_machine);
            used[task_index] = 1;
            j++;
        }
    }
    for(int k = 0; k < Constance::n_solutions; k++)
    {
        insertion_sort_machine_one(k,55);
        insertion_sort_machine_two(k,55);
    }
}

int Instance::target_function( int index )
{
    int sum_of_end_time = 0;
    for( int i = 0; i < Constance::n_tasks + Constance::n_maintenance; i++ )
    {
        if( !solutions[index].get_machine_one()[i]->is_maintenance() ) sum_of_end_time += solutions[index].get_machine_one()[i]->get_start() + solutions[index].get_machine_one()[i]->get_duration();
        if( !solutions[index].get_machine_two()[i]->is_maintenance() ) sum_of_end_time += solutions[index].get_machine_two()[i]->get_start() + solutions[index].get_machine_two()[i]->get_duration();
    }
    return sum_of_end_time;
}

void Instance::selection( int time )
{
    int solution_index, chosen_solutions_amount = 0, proportion ;
    Solutions temp;

    if( time < 1 ) proportion = 0.3 * Constance::crossed_solutions;
    else if( time < 2 ) proportion = 0.4 * Constance::crossed_solutions;
    else if( time < 3 ) proportion = 0.5 * Constance::crossed_solutions;
    else if( time < 4 ) proportion = 0.6 * Constance::crossed_solutions;
    else if( time < 5 ) proportion = 0.7 * Constance::crossed_solutions;
    else proportion = 0.8 * Constance::crossed_solutions;

    //ruletka
    while( proportion < Constance::crossed_solutions )
    {
        solution_index = rand()%( Constance::crossed_solutions - chosen_solutions_amount ) + chosen_solutions_amount;
        temp = solutions[solution_index];
        solutions[solution_index] = solutions[chosen_solutions_amount];
        solutions[chosen_solutions_amount] = temp;
        chosen_solutions_amount++;
        proportion++;
    }
    //turniej
    insertion_sort_solutions( chosen_solutions_amount );
    /*for( int i = 100; i < Constance::crossed_solutions; i++ )
    {
        delete *solutions[i];
        solutions[i] = nullptr;
    }*/
    //sprawdzialem czy sie nie powtarzaja
   /* for( int i = 0; i < Constance::n_solutions-1; i++ )
     for( int j = i + 1; j < Constance::n_solutions; j++ )
        if( solutions[i].solution_indeks == solutions[j].solution_indeks )
        {
            cout<<"dupa"<<endl;
            cout<<"i"<<i<<endl;
            cout<<"j"<<j<<endl;
        }*/
}

void Instance::crossing()
{
	//losowanie rozwi¹zañ
	srand(time(NULL));

	int solution1_index = rand() % Constance::n_solutions;
	cout << solution1_index << endl;

	int solution2_index = rand() % Constance::n_solutions;
	while (solution2_index == solution1_index)
		solution2_index = rand() % Constance::n_solutions;
	cout << solution2_index << endl;

	//wstawianie maintenance
	Solutions *solution1, *solution2;
	solution1 = new Solutions;
	solution2 = new Solutions;
	int dupa = 0;

	for (int i = 0; i < Constance::n_maintenance; i++)
	{
		solution1->insert_operation(1, &maintenance[i],dupa,maintenance[i].get_start());
		solution1->insert_operation(2, &maintenance[Constance::n_maintenance + i], dupa, maintenance[Constance::n_maintenance + i].get_start());
		solution2->insert_operation(1, &maintenance[i],dupa,maintenance[i].get_start());
		solution2->insert_operation(2, &maintenance[Constance::n_maintenance + i], dupa, maintenance[Constance::n_maintenance + i].get_start());
	}
	//wstawianie operacji
	//pierwsze wylosowane do drugiego tworzonego, maszyna 1
	int i = 0;
	int i1 = 0;
	int last_operation_end = 0;
	int index = 0;
	while (i < Constance::n_tasks/2)
	{
		if (solutions[solution1_index].get_machine_one()[i1]->is_maintenance())
			;
		else
		{
			solution2->insert_operation(1, solutions[solution1_index].get_machine_one()[i1],last_operation_end, max(last_operation_end, tasks[solutions[solution1_index].get_machine_one()[i1]->get_task_index()].get_ready_time()));
			i++;
		}
		i1++;
	}
	i1 = 0;
	for (int i = 0; i < (Constance::n_tasks + Constance::n_maintenance); i++)
	{
		if (!solutions[solution2_index].get_machine_one()[i]->is_maintenance())
		{
			i1 = 0;
			while (i1 < solution2->get_machine_one_operations_number()
				&& (solutions[solution2_index].get_machine_one()[i]->get_task_index() != solution2->get_machine_one()[i1]->get_task_index() || solution2->get_machine_one()[i1]->is_maintenance()))
			{
				i1++;
			}
			if (i1 == solution2->get_machine_one_operations_number())
			{
				solution2->insert_operation(1, solutions[solution2_index].get_machine_one()[i],last_operation_end, max(last_operation_end, tasks[solutions[solution2_index].get_machine_one()[i]->get_task_index()].get_ready_time()));
			}
		}
	}
	//pierwsze wylosowane do drugiego tworzonego, maszyna 2
	i1 = i = 0;
	last_operation_end = 0;
	while (i < Constance::n_tasks / 2)
	{
		if (solutions[solution1_index].get_machine_two()[i1]->is_maintenance())
			;
		else
		{
			while (solution2->get_machine_one()[index]->get_task_index() != solutions[solution1_index].get_machine_two()[i1]->get_task_index() || solution2->get_machine_one()[index]->is_maintenance())
				index++;
			last_operation_end = max(last_operation_end, solution2->get_machine_one()[index]->get_start() + solution2->get_machine_one()[index]->get_duration());
			index = 0;
			solution2->insert_operation(2, solutions[solution1_index].get_machine_two()[i1],last_operation_end, max(last_operation_end, tasks[solutions[solution1_index].get_machine_two()[i1]->get_task_index()].get_ready_time()));
			i++;
		}
		i1++;
	}

	i1 = 0;
	for (int i = 0; i < (Constance::n_tasks + Constance::n_maintenance); i++)
	{
		if (!solutions[solution2_index].get_machine_two()[i]->is_maintenance())
		{
			i1 = 0;
			while (i1 < solution2->get_machine_two_operations_number()
				&& (solutions[solution2_index].get_machine_two()[i]->get_task_index() != solution2->get_machine_two()[i1]->get_task_index() || solution2->get_machine_two()[i1]->is_maintenance()))
			{
				i1++;
			}
			if (i1 == solution2->get_machine_two_operations_number())
			{
				while (solution2->get_machine_one()[index]->get_task_index() != solutions[solution2_index].get_machine_two()[i]->get_task_index() || solution2->get_machine_one()[index]->is_maintenance())
					index++;
				last_operation_end = max(last_operation_end, solution2->get_machine_one()[index]->get_start() + solution2->get_machine_one()[index]->get_duration());
				index = 0;
				solution2->insert_operation(2, solutions[solution2_index].get_machine_two()[i],last_operation_end, max(last_operation_end, tasks[solutions[solution2_index].get_machine_two()[i]->get_task_index()].get_ready_time()));
			}
		}
	}
	//drugie wylosowane do pierwszego tworzonego, maszyna 1
	i1 = i = 0;
	last_operation_end = 0;
	while (i < Constance::n_tasks / 2)
	{
		if (solutions[solution2_index].get_machine_one()[i1]->is_maintenance())
			;
		else
		{
			solution1->insert_operation(1, solutions[solution2_index].get_machine_one()[i1],last_operation_end, max(last_operation_end, tasks[solutions[solution2_index].get_machine_one()[i1]->get_task_index()].get_ready_time()));
			i++;
		}
		i1++;
	}

	i1 = 0;
	for (int i = 0; i < (Constance::n_tasks + Constance::n_maintenance); i++)
	{
		if (!solutions[solution1_index].get_machine_one()[i]->is_maintenance())
		{
			i1 = 0;
			while (i1 < solution1->get_machine_one_operations_number()
				&& (solutions[solution1_index].get_machine_one()[i]->get_task_index() != solution1->get_machine_one()[i1]->get_task_index() || solution1->get_machine_one()[i1]->is_maintenance()))
			{
				i1++;
			}
			if (i1 == solution1->get_machine_one_operations_number())
			{
				solution1->insert_operation(1, solutions[solution1_index].get_machine_one()[i], last_operation_end, max(last_operation_end, tasks[solutions[solution1_index].get_machine_one()[i]->get_task_index()].get_ready_time()));
			}
		}
	}
	//drugie wylosowane do pierwszego tworzonego, maszyna 2
	i1 = i = 0;
	last_operation_end = 0;
	while (i < Constance::n_tasks / 2)
	{
		if (solutions[solution2_index].get_machine_two()[i1]->is_maintenance())
			;
		else
		{
			while (solution1->get_machine_one()[index]->get_task_index() != solutions[solution2_index].get_machine_two()[i1]->get_task_index() || solution1->get_machine_one()[index]->is_maintenance())
				index++;
			last_operation_end = max(last_operation_end, solution1->get_machine_one()[index]->get_start() + solution1->get_machine_one()[index]->get_duration());
			index = 0;
			solution1->insert_operation(2, solutions[solution2_index].get_machine_two()[i1], last_operation_end, max(last_operation_end, tasks[solutions[solution2_index].get_machine_two()[i1]->get_task_index()].get_ready_time()));
			i++;
		}
		i1++;
	}

	i1 = 0;
	for (int i = 0; i < (Constance::n_tasks + Constance::n_maintenance); i++)
	{
		if (!solutions[solution1_index].get_machine_two()[i]->is_maintenance())
		{
			i1 = 0;
			while (i1 < solution1->get_machine_two_operations_number()
				&& (solutions[solution1_index].get_machine_two()[i]->get_task_index() != solution1->get_machine_two()[i1]->get_task_index() || solution1->get_machine_two()[i1]->is_maintenance()))
			{
				i1++;
			}
			if (i1 == solution1->get_machine_two_operations_number())
			{
				while (solution1->get_machine_one()[index]->get_task_index() != solutions[solution1_index].get_machine_two()[i]->get_task_index() || solution1->get_machine_one()[index]->is_maintenance())
					index++;
				last_operation_end = max(last_operation_end, solution1->get_machine_one()[index]->get_start() + solution1->get_machine_one()[index]->get_duration());
				index = 0;
				solution1->insert_operation(2, solutions[solution1_index].get_machine_two()[i], last_operation_end, max(last_operation_end, tasks[solutions[solution1_index].get_machine_two()[i]->get_task_index()].get_ready_time()));
			}
		}
	}
	solutions[solutions_number] = *solution1;
	solutions_number++;
	solutions[solutions_number] = *solution2;
	solutions_number++;
}
