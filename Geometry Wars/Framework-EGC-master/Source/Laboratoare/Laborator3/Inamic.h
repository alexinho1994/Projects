#pragma once

#include <string>

#include <include/glm.h>
#include <Core/GPU/Mesh.h>
#include <vector>

using namespace std;

class Inamic
{
private:
	string nume;
	int vieti;
	float viteza;
	float tx, ty;
	float length;

public:
	Inamic();
	Inamic(string nume, float tx, float ty, int vieti, float viteza, float length);
	string getNume();
	float getTx();
	float getTy();
	void setTx(float ty);
	void setTy(float tx);
	~Inamic();
	float getViteza();
	int getVieti();
	void setVieti(int vieti);
	float getLength();
	Mesh* CreateEnemy(string name, glm::vec3 leftBottomCorner, float lenght, glm::vec3 color);
};