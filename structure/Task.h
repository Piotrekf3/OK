#pragma once
#include"Operation.h"

class Task
{
private:
	Operation op1;
	Operation op2;
	int ready_time;
	int index;

	public:
	Task(const int & start1,const int & dur1,const int & start2,const int & dur2,const int & ready_time,const int & index);
	int get_index(){ return index; }
	int get_ready_time() { return ready_time; }
	Operation * get_operation1();
	Operation * get_operation2();

};