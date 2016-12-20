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
	//generator.crossing();

	Operation operations[3];
	operations[0].set_duration(2);
	operations[0].set_start(1);

	operations[1].set_duration(2);
	operations[1].set_start(2);

	operations[2].set_duration(2);
	operations[2].set_start(3);


	Solutions test;
	test.insert_operation(1, &operations[0],2);
	test.insert_operation(1, &operations[1],6);
	test.insert_operation(1, &operations[2]);
	for (int i = 0; i <= 2; i++)
	{
		cout << operations[i].get_start() << endl;
		cout << test.get_machine_one()[i]->get_start() << endl;
	}
	cin.ignore();
	cin.get();
	return 0;

}
