#pragma once

#include <vector>
#include <string>
#include <include/glm.h>
#include <Core/Engine.h>

using namespace std;

class Bullet
{
public:
	Bullet();
	Bullet(float x, float y, float z, int type, float speed);
	~Bullet();
	

	float getX();
	float getY();
	float getZ();
	float getSpeed();
	float getGrade();
	int getType();
	glm::vec3 getPosition();
	Mesh* getMesh();
	string getName();
	float getTargetX();
	float getTargetZ();
	float getDistance();
	float getMoveY();

	void setX(float);
	void setY(float);
	void setZ(float);
	void setSpeed(float);
	void setGrade(float);
	void setType(int);
	void setPosition(glm::vec3);
	void setMesh(Mesh*);
	void setName(string name);
	void setTargetX(float tx);
	void setTargetZ(float ty);
	void setDistance(float d);
	void setMoveY();


private:
	float x;
	float y;
	float z;
	float targetX;
	float targetZ;
	int type;
	float speed;
	float grade;
	glm::vec3 position;
	Mesh* mesh;
	string name;
	float distance;
	float moveY;
};

