#pragma once

#include <string>

using namespace std;

class Turn
{
public:
	Turn();
	~Turn();

	float getGrade();
	string getName();
	float getTime();

	void setGrade(float grade);
	void setName(string name);
	void setTime(float time);

private:
	float grade;
	string name;
	float time;
};

