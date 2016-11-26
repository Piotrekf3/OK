#include "Operation.h"


Operation::Operation(const int & start, const int & duration, bool m, const int & task_index) :maintenance(m)
{
	this->start = start;
	this->duration = duration;
	this->task_index = task_index;
}

bool Operation::set_start(const int & start)
{
	if (this->maintenance == false)
	{
		this->start = start;
		return true;
	}
	else
		return false;

}

bool Operation::set_duration(const int & duration)
{
	if (this->maintenance == false)
	{
		this->duration = duration;
		return true;
	}
	else
		return false;

}

int Operation::get_start()
{
	return this->start;
}

int Operation::get_duration()
{
	return this->duration;
}

