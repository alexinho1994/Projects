#pragma once

#include <vector>
#include <include/glm.h>
#include <Core/Engine.h>

class Player
{
public:
	Player();
	Player(float x, float y, float z, int lifes);
	~Player();

	int getLifes();
	float getX();
	float getY();
	float getZ();
	float getSpeed();
	float getGrade();
	glm::vec3 getPosition();
	Mesh *getMesh();
	int getType();
	float getTime();

	void setLifes(int lifes);
	void setX(float x);
	void setY(float y);
	void setZ(float z);
	void setSpeed(float speed);
	void setGrade(float grade);
	void setPosition(glm::vec3 position);
	void setMesh(Mesh *mesh);
	void setType(int type);
	void setTime(float time);


private:
	int lifes;
	float x;
	float y;
	float z;
	float speed;
	float grade;
	glm::vec3 position;
	Mesh *mesh;
	int type;
	float time;
};

