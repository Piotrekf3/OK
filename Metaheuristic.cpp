#include<iostream>
#include<ctime>
#include"structure.h"
using namespace std;

int main()
{
	srand(time(NULL));
	Instance instance;
	instance.load_from_file("../../Instances/Instancja1.txt");
	instance.generate_solutions();
	time_t start = time(NULL);
	while (difftime(time(NULL), start) <= 5)
	{
		instance.mutation();
		for (int i = 0; i < 50;i++)
		instance.crossing();
		instance.selection(difftime(time(NULL), start));
	}
	//cout << "start=" << instance.get_solution(1).get_machine_one()[54]->get_start() << endl;

	cin.ignore();
	cin.get();
	return 0;

}
