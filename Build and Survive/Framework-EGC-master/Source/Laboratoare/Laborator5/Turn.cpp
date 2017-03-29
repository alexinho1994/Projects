#include "Turn.h"



Turn::Turn()
{
}


Turn::~Turn()
{
}

float Turn::getGrade()
{
	return this->grade;
}

string Turn::getName()
{
	return this->name;
}

void Turn::setGrade(float grade)
{
	this->grade = grade;
}

void Turn::setName(string name)
{
	this->name = name;
}

float Turn::getTime()
{
	return this->time;
}

void Turn::setTime(float time)
{
	this->time = time;
}
