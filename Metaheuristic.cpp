#include<iostream>
#include"structure.h"
using namespace std;

int main()
{
	Instance generator;
	generator.load_from_file("../../Instances/Instancja1.txt");
	//cout << generator.get_task(2).get_index() << endl;
	generator.generate_solutions();
	cout << "1 maszyna\n";
	//generator.get_solution(2).show(1);
	//cout << endl;
	cout << "2 maszyna\n";
	//generator.get_solution(2).show(2);
	//cout << "koniec generowania rozw\n";
	for (int i = 0; i < 100; i++)
	{	
		generator.mutation();
		generator.crossing();
		
	}




	cin.ignore();
	cin.get();
	return 0;

}
