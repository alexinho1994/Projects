#include "Bullet.h"


Mesh* Bullet::CreateBullet(string name, glm::vec3 leftBottomCorner, float length, glm::vec3 color)
{
	glm::vec3 corner = leftBottomCorner;

	std::vector<VertexFormat> vertices =
	{
		VertexFormat(corner + glm::vec3(-length / 4, -length/ 8, 0), color),
		VertexFormat(corner + glm::vec3(length / 4, -length / 8, 0), color),
		VertexFormat(corner + glm::vec3(length / 4, length / 8, 0), color),
		VertexFormat(corner + glm::vec3(-length / 4, length / 8, 0), color)
	};

	Mesh* square = new Mesh(name);
	std::vector<unsigned short> indices = { 0, 1, 2, 3};

	indices.push_back(0);
	indices.push_back(2);

	square->InitFromData(vertices, indices);
	return square;
}

Bullet::Bullet()
{
}


Bullet::~Bullet()
{
}

Bullet::Bullet(string nume, float tx, float ty,  float viteza, float dx, float dy)
{
	this->nume = nume;
	this->tx = tx;
	this->ty = ty;
	this->viteza = viteza;
	this->dx = dx;
	this->dy = dy;
}

string Bullet::getNume()
{
	return this->nume;
}

float Bullet::getTx()
{
	return this->tx;
}

float Bullet::getTy()
{
	return this->ty;
}

void Bullet::setTx(float tx)
{
	this->tx = tx;
}

void Bullet::setTy(float ty)
{
	this->ty = ty;
}

float Bullet::getdx()
{
	return this->dx;
}

float Bullet::getdy()
{
	return this->dy;
}