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
	//while (difftime(time(NULL), start) < 5)
	for (int i = 0; i < 100; i++)
	{
		instance.mutation();
		for (int j = 0; j < 100;j++)
		instance.crossing();
	}


	cin.ignore();
	cin.get();
	return 0;

}
