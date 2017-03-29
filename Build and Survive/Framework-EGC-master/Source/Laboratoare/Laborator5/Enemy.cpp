#include "Enemy.h"



Enemy::Enemy()
{
}


Enemy::~Enemy()
{
}

Enemy::Enemy(float x, float y, float z, int lifes, float speed)
{
	this->x = x;
	this->y = y;
	this->z = z;
	this->lifes = lifes;
	this->speed = speed;
	this->position = glm::vec3(x, y, z);
	this->move = 1;
	this->gradeX = 0;
}

float Enemy::getX()
{
	return this->x;
}

float Enemy::getY()
{
	return this->y;
}

float Enemy::getZ()
{
	return this->z;
}

float Enemy::getGrade()
{
	return this->grade;
}

float Enemy::getSpeed()
{
	return this->speed;
}

int Enemy::getLifes()
{
	return this->lifes;
}

glm::vec3 Enemy::getPosition()
{
	return this->position;
}

Mesh* Enemy::getMesh()
{
	return this->mesh;
}

void Enemy::setX(float x)
{
	this->x = x;
}

void Enemy::setY(float y)
{
	this->y = y;
}

void Enemy::setZ(float z)
{
	this->z = z;
}

void Enemy::setSpeed(float speed)
{
	this->speed = speed;
}

void Enemy::setGrade(float grade)
{
	this->grade = grade;
}

void Enemy::setLifes(int lifes)
{
	this->lifes = lifes;
}

void Enemy::setPosition(glm::vec3 position)
{
	this->position = position;
	this->x = position[0];
	this->y = position[1];
	this->z = position[2];
}

void Enemy::setMesh(Mesh* mesh)
{
	this->mesh = mesh;
}

string Enemy::getName()
{
	return this->name;
}

void Enemy::setName(string name)
{
	this->name = name;
}

int Enemy::getMove()
{
	return this->move;
}

void Enemy::setMove(int move)
{
	this->move = move;
}

float Enemy::getGradeX()
{
	return this->gradeX;
}

void Enemy::setGradeX()
{
	this->gradeX = this->gradeX + 0.05f;
}