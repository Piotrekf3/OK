#pragma once
class Operation
{
private:
	int start;
	int duration;
public:
	Operation(const int & start,const int & duration);
	void set_start(const int & start);
	void set_duration(const int & duration);
	int get_start();
	int get_duration();

};

