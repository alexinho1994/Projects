#include "Laborator3.h"

#include <vector>
#include <iostream>

#include <Core/Engine.h>
#include "Transform2D.h"
#include "Object2D.h"
#include "Inamic.h"
#include "Bullet.h"

using namespace std;

Laborator3::Laborator3()
{
}

Laborator3::~Laborator3()
{
}
float time2 = 0, enemyTime = 2, time = 0, f, squareSide = 30, tx = 300; float ty = 250; int ok = 1; int rx = 400; int ry = 250; float scaleX = 500; float scaleY = 250; float ok2 = 1; float cx = 250; float cy = 125;
glm::ivec2 resolution;
int inamici = 0, gloante = 0;
vector<Inamic*> inam;
int vieti = 3;
vector<Bullet*> bullets;
bool click = false;
int mx, my;
vector<int> elimInamic;
vector<int> elimBullet;
float color = 0;

void Laborator3::Init()
{
	resolution = window->GetResolution();
	camera->SetOrthographic(0, (float)resolution.x, 0, (float)resolution.y, 0.01f, 400);
	camera->SetPosition(glm::vec3(0, 0, 50));
	camera->SetRotation(glm::vec3(0, 0, 0));
	camera->Update();
	cameraInput->SetActive(false);

	glm::vec3 corner = glm::vec3(0, 0, 0);
	squareSide = 30;

	// compute coordinates of square center
	float cx = corner.x + squareSide / 2;
	float cy = corner.y + squareSide / 2;
	
	// initialize tx and ty (the translation steps)
	translateX = 500;
	translateY = 300;

	// initialize sx and sy (the scale factors)
	scaleX = 1;
	scaleY = 1;
	
	// initialize angularStep
	angularStep = 0;
	

	Mesh* square1 = Object2D::CreateSquare("square1", corner, squareSide, glm::vec3(1, 0, 0), true);
	AddMeshToList(square1);

	Mesh* life1 = Object2D::CreateLife("life1", corner, squareSide, glm::vec3(1, 0, 0));
	AddMeshToList(life1);

	Mesh* life2 = Object2D::CreateLife("life2", corner, squareSide, glm::vec3(1, 0, 0));
	AddMeshToList(life2);

	Mesh* life3 = Object2D::CreateLife("life3", corner, squareSide, glm::vec3(1, 0, 0));
	AddMeshToList(life3);
}

void Laborator3::FrameStart()
{
	// clears the color buffer (using the previously set color) and depth buffer
	glClearColor(0, 0, 0, 1);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glm::ivec2 resolution = window->GetResolution();
	// sets the screen area where to draw
	glViewport(0, 0, resolution.x, resolution.y);
}

void Laborator3::Update(float deltaTimeSeconds)
{
	// TODO: update steps for translation, rotation, scale, in order to create animations
	glm::ivec2 resolution = window->GetResolution();

	time += deltaTimeSeconds;
	time2 += deltaTimeSeconds;
	if (time2 > 10 && enemyTime>0.5)
	{
		time2 = 0;
		enemyTime -= 0.1;
	}
	f = -(M_PI - atan((my - ty) / (mx - tx)));

	if (vieti > 0)
	{
		modelMatrix = glm::mat3(1);
		modelMatrix *= Transform2D::Translate(resolution.x - 50.0, resolution.y - 50.0);
		RenderMesh2D(meshes["life1"], shaders["VertexColor"], modelMatrix);
	}

	if (vieti > 1)
	{
		modelMatrix = glm::mat3(1);
		modelMatrix *= Transform2D::Translate(resolution.x - 30.0, resolution.y - 50.0);
		RenderMesh2D(meshes["life2"], shaders["VertexColor"], modelMatrix);
	}

	if (vieti > 2)
	{
		modelMatrix = glm::mat3(1);
		modelMatrix *= Transform2D::Translate(resolution.x - 70.0, resolution.y - 50.0);
		RenderMesh2D(meshes["life3"], shaders["VertexColor"], modelMatrix);
	}

	modelMatrix = glm::mat3(1);
	modelMatrix *= Transform2D::Translate(0.0f, 0.0f);
	modelMatrix *= Transform2D::Translate(tx, ty);
	modelMatrix *= Transform2D::Rotate(f);
	modelMatrix *= Transform2D::Translate(0.0f, 0.0f);
	RenderMesh2D(meshes["square1"], shaders["VertexColor"], modelMatrix);

	if (vieti > 0)
	{

		if (time > enemyTime)
		{
			inamici++;
			time = 0;
			string nume = "enemy" + to_string(inamici);
			float enX = tx - 300 + (rand() % (601));
			float enXX;
			if (enX > tx)
				enXX = enX - tx;
			else
				enXX = tx - enX;
			float enY = sqrt(300 * 300 - (enXX*enXX));
			int enYY = rand() % 2;
			if (enYY == 0)
				enY = ty - enY;
			else enY += ty;
			int vieti = rand() % 2;
			vieti++;
			
			int viteza = rand() % 2;
			viteza++;
			Inamic *inamic = new Inamic(nume, enX, enY, vieti, viteza, squareSide);
			inam.push_back(inamic);
			Mesh* enemy;
			if (vieti == 1)
				enemy = inamic->CreateEnemy(nume, glm::vec3(1, 1, 1), squareSide, glm::vec3(0, 1, 0));
			else
				enemy = inamic->CreateEnemy(nume, glm::vec3(1, 1, 1), squareSide, glm::vec3(0, 0, 1));
			AddMeshToList(enemy);
			modelMatrix = glm::mat3(1);
			modelMatrix *= Transform2D::Translate(enX, enY);
			RenderMesh2D(meshes[nume], shaders["VertexColor"], modelMatrix);
			
		}

		if (click == true)
		{
			click = false;
			string nume = "bullet" + to_string(gloante);
			float dx = abs(tx - mx);
			float dy = abs(ty - my);
			float dist = sqrt(dx*dx + dy*dy);
			float sin1 = dx / dist;
			float sin2 = dy / dist;
			sin1 = sin1 * 10;
			sin2 = sin2 * 10;
			if (mx < tx)
				sin1 = 0 - sin1;
			if (my < ty)
				sin2 = 0 - sin2;
			Bullet *bullet = new Bullet(nume, tx, ty, 10, sin1, sin2);
			bullets.push_back(bullet);
			Mesh* blt = bullet->CreateBullet(nume, glm::vec3(1, 1, 1), squareSide, glm::vec3(1, 0, 0));
			AddMeshToList(blt);
			modelMatrix = glm::mat3(1);
			modelMatrix *= Transform2D::Translate(tx, ty);
			modelMatrix *= Transform2D::Rotate(f);
			modelMatrix *= Transform2D::Translate(0.0f, 0.0f);
			RenderMesh2D(meshes[nume], shaders["VertexColor"], modelMatrix);
		}

		for (int i = 0; i < inam.size(); i++)
		{
			float dX = abs(tx - inam[i]->getTx());
			float dY = abs(ty - inam[i]->getTy());
			float dist = sqrt(dX*dX + dY*dY);
			float sn = dX / dist;
			dX = sn * inam[i]->getViteza();
			sn = dY / dist;
			dY = sn * inam[i]->getViteza();

			if (ty > inam[i]->getTy())
				inam[i]->setTy(inam[i]->getTy() + dY);
			else
				inam[i]->setTy(inam[i]->getTy() - dY);

			if (tx > inam[i]->getTx())
				inam[i]->setTx(inam[i]->getTx() + dX);
			else
				inam[i]->setTx(inam[i]->getTx() - dX);
			if (sqrt((inam[i]->getTx() - tx)*(inam[i]->getTx() - tx) + (inam[i]->getTy() - ty)*(inam[i]->getTy() - ty)) <= squareSide)
			{
				elimInamic.push_back(i);
				vieti--;
			}
			else
			{
				float fe = -(M_PI - atan((ty - inam[i]->getTy()) / (tx - inam[i]->getTx())));
				modelMatrix = glm::mat3(1);
				modelMatrix *= Transform2D::Translate(inam[i]->getTx(), inam[i]->getTy());
				modelMatrix *= Transform2D::Rotate(fe);
				modelMatrix *= Transform2D::Translate(0, 0);
				RenderMesh2D(meshes[inam[i]->getNume()], shaders["VertexColor"], modelMatrix);
			}
		}

		for (int i = 0; i < bullets.size(); i++)
		{
			bullets[i]->setTx(bullets[i]->getTx() + bullets[i]->getdx());
			bullets[i]->setTy(bullets[i]->getTy() + bullets[i]->getdy());
			int ok = 0;
			int ok2 = 0;
			for (int j = 0; j < inam.size(); j++)
			{
				if (ok2 == 1)
				{
					ok2 = 0;
					j--;
				}
				float ex = inam[j]->getTx();
				float ey = inam[j]->getTy();
				float bx = bullets[i]->getTx();
				float by = bullets[i]->getTy();
				if (sqrt((ex - bx)*(ex - bx) + (ey - by) * (ey - by)) <= squareSide)
				{
					elimInamic.push_back(j);
					ok = 1;
					if (inam[j]->getVieti() == 2)
					{
						inamici++;
						float fe = -(M_PI - atan((ty - inam[j]->getTy()) / (tx - inam[j]->getTx())));
						string nume = "enemy" + to_string(inamici);
						Inamic *inamic = new Inamic(nume, inam[j]->getTx(), inam[j]->getTy(), 1, inam[j]->getViteza() * 2, squareSide / 2);
						inam.push_back(inamic);
						Mesh* enemy = inamic->CreateEnemy(nume, glm::vec3(1, 1, 1), squareSide / 2, glm::vec3(0, 1, 0));
						AddMeshToList(enemy);
						modelMatrix = glm::mat3(1);
						modelMatrix *= Transform2D::Translate(inam[j]->getTx(), inam[j]->getTy());
						modelMatrix *= Transform2D::Rotate(fe);
						RenderMesh2D(meshes[nume], shaders["VertexColor"], modelMatrix);
						j++;
						ok2 = 1;
					}
				}
			}
			if (ok == 1)
			{
				ok == 0;
				elimBullet.push_back(i);
			}
			else
			{
				modelMatrix = glm::mat3(1);
				modelMatrix *= Transform2D::Translate(bullets[i]->getTx(), bullets[i]->getTy());
				modelMatrix *= Transform2D::Rotate(f);
				RenderMesh2D(meshes[bullets[i]->getNume()], shaders["VertexColor"], modelMatrix);
			}
		}

		for (int i = elimInamic.size() - 1; i >= 0; i--)
		{
			if (elimInamic[i] < inam.size())
				inam.erase(inam.begin() + elimInamic[i]);
		}

		elimInamic.clear();

		for (int i = elimBullet.size() - 1; i >= 0; i--)
		{
			if (elimBullet[i] < bullets.size())
				bullets.erase(bullets.begin() + elimBullet[i]);
		}
		elimBullet.clear();
	}
	else {
		if (color < 1)
			color += deltaTimeSeconds;
		glClearColor(color, 0, 0, 0);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	}
}

void Laborator3::FrameEnd()
{

}

void Laborator3::OnInputUpdate(float deltaTime, int mods)
{
	if (vieti > 0)
	{
		if (window->KeyHold(GLFW_KEY_W))
		{
			ty += 4;
		}

		if (window->KeyHold(GLFW_KEY_A))
		{
			tx -= 4;
		}

		if (window->KeyHold(GLFW_KEY_S))
		{
			ty -= 4;
		}

		if (window->KeyHold(GLFW_KEY_D))
		{
			tx += 4;
		}
	}
	
}

void Laborator3::OnKeyPress(int key, int mods)
{
	// add key press event
};

void Laborator3::OnKeyRelease(int key, int mods)
{
	// add key release event
};

void Laborator3::OnMouseMove(int mouseX, int mouseY, int deltaX, int deltaY)
{
	// add mouse move event
	if (vieti > 0)
	{
		mx = mouseX;
		my = resolution.y - mouseY;
	}
};

void Laborator3::OnMouseBtnPress(int mouseX, int mouseY, int button, int mods)
{
	// add mouse button press event
	if (vieti > 0)
	{
		click = true;
		mx = mouseX;
		my = resolution.y - mouseY;
	}
};

void Laborator3::OnMouseBtnRelease(int mouseX, int mouseY, int button, int mods)
{
	// add mouse button release event
}

void Laborator3::OnMouseScroll(int mouseX, int mouseY, int offsetX, int offsetY)
{
}