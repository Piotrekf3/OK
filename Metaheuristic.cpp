#include<iostream>
#include"structure.h"
using namespace std;

int main()
{
	Instance generator;
	generator.load_from_file("../../Instances/Instancja1.txt");
	//cout << generator.get_maintenance(2).get_task_index() << endl;
	generator.generate_solutions();
	cout << "koniec generowania rozw\n";
	generator.crossing();



	cin.ignore();
	cin.get();
	return 0;

}
