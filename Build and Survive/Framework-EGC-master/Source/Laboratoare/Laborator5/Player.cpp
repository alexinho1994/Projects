#include "Player.h"



Player::Player()
{
}


Player::~Player()
{
}

Player::Player(float x, float y, float z, int lifes)
{
	this->x = x;
	this->y = y;
	this->z = z;
	this->lifes = lifes;
	this->position = glm::vec3(x, y, z);
	this->type = 1;
}

float Player::getGrade()
{
	return this->grade;
}

float Player::getX()
{
	return this->x;
}

float Player::getY()
{
	return this->y;
}

float Player::getZ()
{
	return this->z;
}

float Player::getSpeed()
{
	return this->speed;
}

int Player::getLifes()
{
	return this->lifes;
}

glm::vec3 Player::getPosition()
{
	return this->position;
}

Mesh* Player::getMesh()
{
	return this->mesh;
}

void Player::setGrade(float grade)
{
	this->grade = grade;
}

void Player::setX(float x)
{
	this->x = x;
}

void Player::setY(float y)
{
	this->y = y;
}

void Player::setZ(float z)
{
	this->z = z;
}

void Player::setSpeed(float speed)
{
	this->speed = speed;
}

void Player::setLifes(int lifes)
{
	this->lifes = lifes;
}

void Player::setPosition(glm::vec3 position)
{
	this->position = position;
	this->x = position[0];
	this->y = position[1];
	this->z = position[2];
}

void Player::setMesh(Mesh* mesh)
{
	this->mesh = mesh;
}

int Player::getType()
{
	return this->type;
}

void Player::setType(int type)
{
	this->type = type;
}

void Player::setTime(float time)
{
	this->time = time;
}

float Player::getTime()
{
	return this->time;
}