#pragma once
#include <string>

#include <include/glm.h>
#include <Core/GPU/Mesh.h>
#include <vector>

using namespace std;

class Bullet
{
private:
	string nume;
	float viteza;
	float tx, ty;
	float dx, dy;

public:
	Bullet();
	Bullet(string nume, float tx, float ty, float viteza, float dx, float dy);
	string getNume();
	float getTx();
	float getTy();
	void setTx(float ty);
	void setTy(float tx);
	float getdx();
	float getdy();
	~Bullet();
	Mesh* CreateBullet(string name, glm::vec3 leftBottomCorner, float lenght, glm::vec3 color);
};