#include "Operation.h"


Operation::Operation(const int & start, const int & duration)
{
	this->start = start;
	this->duration = duration;
}

void Operation::set_start(const int & start)
{
	this->start = start;
}

void Operation::set_duration(const int & duration)
{
	this->duration = duration;
}

int Operation::get_start()
{
	return this->start;
}

int Operation::get_duration()
{
	return this->duration;
}

