#include "Bullet.h"



Bullet::Bullet()
{
}


Bullet::~Bullet()
{
}

Bullet::Bullet(float x, float y, float z, int type, float speed)
{
	this->x = x;
	this->y = y;
	this->z = z;
	this->type = type;
	this->speed = speed;
	this->position = glm::vec3(x, y, z);
	if (type == 1)
		this->distance = 10;
	if (type == 2)
		this->distance = 15;
	if (type == 3)
	{
		this->distance = 3;
		this->moveY = 0.1;
	}
	if (type == 4)
		this->distance = 40;
}

float Bullet::getX()
{
	return this->x;
}

float Bullet::getY()
{
	return this->y;
}

float Bullet::getZ()
{
	return this->z;
}

float Bullet::getGrade()
{
	return this->grade;
}

float Bullet::getSpeed()
{
	return this->speed;
}

int Bullet::getType()
{
	return this->type;
}

glm::vec3 Bullet::getPosition()
{
	return this->position;
}

Mesh* Bullet::getMesh()
{
	return this->mesh;
}

void Bullet::setX(float x)
{
	this->x = x;
}

void Bullet::setY(float y)
{
	this->y = y;
}

void Bullet::setZ(float z)
{
	this->z = z;
}

void Bullet::setSpeed(float speed)
{
	this->speed = speed;
}

void Bullet::setGrade(float grade)
{
	this->grade = grade;
}

void Bullet::setType(int type)
{
	this->type = type;
}

void Bullet::setPosition(glm::vec3 position)
{
	this->position = position;
	this->x = position[0];
	this->y = position[1];
	this->z = position[2];
}

void Bullet::setMesh(Mesh* mesh)
{
	this->mesh = mesh;
}

string Bullet::getName()
{
	return this->name;
}

void Bullet::setName(string name)
{
	this->name = name;
}

float Bullet::getTargetX()
{
	return this->targetX;
}

float Bullet::getTargetZ()
{
	return this->targetZ;
}

void Bullet::setTargetX(float tx)
{
	this->targetX = tx;
}

void Bullet::setTargetZ(float tz)
{
	this->targetZ = tz;
}

void Bullet::setDistance(float d)
{
	this->distance = this->distance - d;
}

float Bullet::getDistance()
{
	return this->distance;
}

void Bullet::setMoveY()
{
	if (this->y > 2)
	{
		moveY = -0.1;
	}
}

float Bullet::getMoveY()
{
	return this->moveY;
}