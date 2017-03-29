#pragma once

#include <vector>
#include <string>
#include <include/glm.h>
#include <Core/Engine.h>

using namespace std;

class Enemy
{
public:
	Enemy();
	~Enemy();
	Enemy(float x, float y, float z, int lifes, float speed);

	float getX();
	float getY();
	float getZ();
	float getSpeed();
	float getGrade();
	int getLifes();
	glm::vec3 getPosition();
	Mesh* getMesh();
	string getName();
	int getMove();
	float getGradeX();

	void setX(float);
	void setY(float);
	void setZ(float);
	void setSpeed(float);
	void setGrade(float);
	void setLifes(int);
	void setPosition(glm::vec3);
	void setMesh(Mesh*);
	void setName(string name);
	void setMove(int move);
	void setGradeX();

private:
	float x;
	float y;
	float z;
	int lifes;
	float speed;
	float grade;
	glm::vec3 position;
	Mesh* mesh;
	string name;
	int move;
	float gradeX;
};

