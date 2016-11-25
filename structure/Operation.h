#pragma once
class Operation
{
private:
	int start;
	int duration;
	const bool maintenance; //1- maintenance,0-nie
	int task_index;
public:
	Operation(const int & start, const int & duration, bool maintenance,const int & task_index);
	bool set_start(const int & start);
	bool set_duration(const int & duration);
	int get_start();
	int get_duration();

};

