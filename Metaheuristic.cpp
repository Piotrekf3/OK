#include<iostream>
#include<ctime>
#include"structure.h"
using namespace std;

int main()
{
	srand(time(NULL));
	Instance instance;
	//instance.generate_instance_to_file(); generuje instancje
		instance.load_from_file("../../Instances/Instancja50.txt");
		instance.generate_solutions();
		instance.save_begin_time();
		time_t start = time(NULL);
		int duration = 0;
		while (duration <= 5)
		{
			instance.mutation(duration);
			for (int i = 0; i < 50; i++)
				instance.crossing();
			instance.selection(duration);
			duration = difftime(time(NULL), start);
		}
		instance.save_best_solution();
		cout << "koniec\n";
	//cin.ignore();
	//cin.get();
	return 0;

}
