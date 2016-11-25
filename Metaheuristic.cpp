#include<iostream>
#include"structure.h"
using namespace std;

int main()
{
	Task task1(3, 2, 1, 2, 0, 0);
	Operation * op = task1.get_operation1();
	cout << op->get_start() << endl;
	cin.ignore();
	cin.get();
	return 0;
}