#include "Laborator5.h"

#include <vector>
#include <string>
#include <iostream>
#include "Player.h"

#include <Core/Engine.h>

using namespace std;

Player* player;

Laborator5::Laborator5()
{
}

Laborator5::~Laborator5()
{
}

void Laborator5::Init()
{
	renderCameraTarget = true;
	camera = new Laborator::Camera();
	camera2 = new Laborator::Camera();
	camera2->Set(glm::vec3(0, 35, 0), glm::vec3(0, 1, 0), glm::vec3(1, 0, 0));

	//set player
	Mesh* mesh = new Mesh("player");
	mesh->LoadMesh(RESOURCE_PATH::MODELS + "Tema2", "Steve.obj");
	meshes[mesh->GetMeshID()] = mesh;
	player = new Player(0, 0, 0, 3);
	player->setMesh(mesh);
	player->setGrade(M_PI/2);
	player->setTime(1);

	//set Towers
	mesh = new Mesh("Tower1");
	mesh->LoadMesh(RESOURCE_PATH::MODELS + "Tema2", "tower.obj");
	meshes[mesh->GetMeshID()] = mesh;
	Turn* tower1 = new Turn();
	tower1->setGrade(M_PI / 2);
	tower1->setName("Tower1");
	tower1->setTime(6);
	towers.push_back(tower1);

	mesh = new Mesh("Tower2");
	mesh->LoadMesh(RESOURCE_PATH::MODELS + "Tema2", "tower.obj");
	meshes[mesh->GetMeshID()] = mesh;
	Turn* tower2 = new Turn();
	tower2->setGrade(M_PI / 2);
	tower2->setName("Tower2");
	tower2->setTime(10);
	towers.push_back(tower2);

	mesh = new Mesh("Tower3");
	mesh->LoadMesh(RESOURCE_PATH::MODELS + "Tema2", "tower.obj");
	meshes[mesh->GetMeshID()] = mesh;
	Turn* tower3 = new Turn();
	tower3->setGrade(M_PI / 2);
	tower3->setName("Tower3");
	tower3->setTime(8);
	towers.push_back(tower3);

	//set Enemy
	time = 5;
	resetTime = 30;
	enemyInterval = 5;
	nrInamici = 0;


	projectionMatrix = glm::perspective(RADIANS(60), window->props.aspectRatio, 0.01f, 200.0f);
}

void Laborator5::FrameStart()
{
	// clears the color buffer (using the previously set color) and depth buffer
	glClearColor(0, 0, 0, 1);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glm::ivec2 resolution = window->GetResolution();
	// sets the screen area where to draw
	glViewport(0, 0, resolution.x, resolution.y);
	resolutionX = resolution.x;
	resolutionY = resolution.y;


	
}

void Laborator5::Update(float deltaTimeSeconds)
{
	if (renderCameraTarget)
	{
		glViewport(0, 0, resolutionX, resolutionY);
		float angle = player->getGrade();
		glm::mat4 modelMatrix = glm::mat4(1);
		modelMatrix = glm::translate(modelMatrix, camera->GetTargetPosition());
		modelMatrix = glm::rotate(modelMatrix, angle, glm::vec3(0, 1, 0));
		modelMatrix = glm::scale(modelMatrix, glm::vec3(0.1f));
		RenderMesh(meshes["player"], shaders["VertexNormal"], modelMatrix);

		glViewport(0, 0, resolutionX / 4, resolutionY / 4);
		modelMatrix = glm::scale(modelMatrix, glm::vec3(5.f));
		MinimapMesh(meshes["player"], shaders["VertexNormal"], modelMatrix);
	}

	player->setTime(player->getTime() - deltaTimeSeconds);
	setTime(deltaTimeSeconds);
	setTowerTime(deltaTimeSeconds);
	drawEnemy();
	TowerShoot();
	drawBullet();
	drawTowers();
	removeBulletDistance();
	hitEnemys();
	elimBullet();	
	elimEnemies();
}

void Laborator5::FrameEnd()
{
	glViewport(0, 0, resolutionX, resolutionY);
	DrawCoordinatSystem(camera->GetViewMatrix(), projectionMatrix);

	glViewport(0, 0, resolutionX / 4, resolutionY / 4);
	DrawCoordinatSystem(camera2->GetViewMatrix(), projectionMatrix);
}

void Laborator5::RenderMesh(Mesh * mesh, Shader * shader, const glm::mat4 & modelMatrix)
{
	if (!mesh || !shader || !shader->program)
		return;

	// render an object using the specified shader and the specified position
	shader->Use();
	glUniformMatrix4fv(shader->loc_view_matrix, 1, GL_FALSE, glm::value_ptr(camera->GetViewMatrix()));
	glUniformMatrix4fv(shader->loc_projection_matrix, 1, GL_FALSE, glm::value_ptr(projectionMatrix));
	glUniformMatrix4fv(shader->loc_model_matrix, 1, GL_FALSE, glm::value_ptr(modelMatrix));

	mesh->Render();
}

void Laborator5::MinimapMesh(Mesh * mesh, Shader * shader, const glm::mat4 & modelMatrix)
{
	if (!mesh || !shader || !shader->program)
		return;

	shader->Use();
	glUniformMatrix4fv(shader->loc_view_matrix, 1, GL_FALSE, glm::value_ptr(camera2->GetViewMatrix()));
	glUniformMatrix4fv(shader->loc_projection_matrix, 1, GL_FALSE, glm::value_ptr(projectionMatrix));
	glUniformMatrix4fv(shader->loc_model_matrix, 1, GL_FALSE, glm::value_ptr(modelMatrix));

	mesh->Render();
}

// Documentation for the input functions can be found in: "/Source/Core/Window/InputController.h" or
// https://github.com/UPB-Graphics/Framework-EGC/blob/master/Source/Core/Window/InputController.h

void Laborator5::OnInputUpdate(float deltaTime, int mods)
{
	// move the camera only if MOUSE_RIGHT button is pressed
	if (window->MouseHold(GLFW_MOUSE_BUTTON_RIGHT))
	{
		float cameraSpeed = 2.5f;

		if (window->KeyHold(GLFW_KEY_W)) {
			camera->MoveForward(cameraSpeed * deltaTime);
			player->setPosition(camera->GetTargetPosition());
			// TODO : translate the camera forward
		}

		if (window->KeyHold(GLFW_KEY_A)) {
			camera->TranslateRight(-cameraSpeed * deltaTime);
			player->setPosition(camera->GetTargetPosition());
			// TODO : translate the camera to the left
		}

		if (window->KeyHold(GLFW_KEY_S)) {
			camera->MoveForward(-cameraSpeed * deltaTime);
			player->setPosition(camera->GetTargetPosition());
			// TODO : translate the camera backwards
		}

		if (window->KeyHold(GLFW_KEY_D)) {
			camera->TranslateRight(cameraSpeed * deltaTime);
			player->setPosition(camera->GetTargetPosition());
			// TODO : translate the camera to the right
		}
	}

	if (window->KeyHold(GLFW_KEY_2))
	{
		camera->distanceToTarget = -1;
		player->setType(2);
		player->setTime(0.2);

	}

	if (window->KeyHold(GLFW_KEY_1))
	{
		camera->distanceToTarget = 2;
		player->setType(1);
		player->setTime(1);
	}


	if (window->KeyHold(GLFW_KEY_3))
	{
		camera->distanceToTarget = 2;
		player->setType(3);
		player->setTime(5);
	}
}

void Laborator5::OnKeyPress(int key, int mods)
{
	
}

void Laborator5::OnKeyRelease(int key, int mods)
{
	// add key release event
}

void Laborator5::OnMouseMove(int mouseX, int mouseY, int deltaX, int deltaY)
{
	// add mouse move event

	if (window->MouseHold(GLFW_MOUSE_BUTTON_RIGHT))
	{
		float sensivityOX = 0.001f;
		float sensivityOY = 0.001f;

		if (window->GetSpecialKeyState() == 0) {
			renderCameraTarget = true;
			camera->RotateThirdPerson_OX(deltaY * sensivityOX);
			camera->RotateThirdPerson_OY(deltaX * sensivityOY);
			float angle;
			float x = camera->position.x - player->getX();
			float y = camera->position.z - player->getZ();
			angle = (float)(atan(x / y) + M_PI/2);
			if (y < 0)
				angle += (float)M_PI;
			player->setGrade(angle);
		}

			// TODO : rotate the camera in Third-person mode around OX and OY using deltaX and deltaY
			// use the sensitivity variables for setting up the rotation speed
		

	}
}

void Laborator5::OnMouseBtnPress(int mouseX, int mouseY, int button, int mods)
{
	if (button == 1 && player->getTime() <= 0)
	{
		if (player->getType() != 3)
		{
			nrBullets++;
			Mesh* mesh = new Mesh("Bullet" + to_string(nrBullets));
			mesh->LoadMesh(RESOURCE_PATH::MODELS + "Tema2", "sphere.obj");
			meshes[mesh->GetMeshID()] = mesh;

			Bullet* bullet;
				if(player->getType() == 1)
					bullet = new Bullet(player->getX(), 1, player->getZ(), player->getType(), 0.2);
				else
					bullet = new Bullet(player->getX(), 1, player->getZ(), player->getType(), 0.3);
			bullet->setGrade(player->getGrade());
			bullet->setName("Bullet" + to_string(nrBullets));
			bullet->setMesh(mesh);
			float grade = player->getGrade() + (float)M_PI / 2;
			grade = sin(grade);
			bullet->setTargetX(grade * bullet->getSpeed());
			grade = cos(player->getGrade() + (float)M_PI / 2);
			bullet->setTargetZ(grade * bullet->getSpeed());

			bullets.push_back(bullet);
			if (player->getType() == 1)
				player->setTime(1);
			else player->setTime(0.2);
		}

		if (player->getType() == 3)
		{
			nrBullets++;
			Mesh* mesh = new Mesh("Bullet" + to_string(nrBullets));
			mesh->LoadMesh(RESOURCE_PATH::MODELS + "Tema2", "sphere.obj");
			meshes[mesh->GetMeshID()] = mesh;
			Bullet* bullet = new Bullet(player->getX(), 1, player->getZ(), player->getType(), 0.1);
			bullet->setGrade(player->getGrade());
			bullet->setName("Bullet" + to_string(nrBullets));
			bullet->setMesh(mesh);
			float grade = player->getGrade() + (float)M_PI / 2;
			grade = sin(grade);
			bullet->setTargetX(grade * 0.1);
			grade = cos(player->getGrade() + (float)M_PI / 2);
			bullet->setTargetZ(grade * 0.1);

			bullets.push_back(bullet);
			player->setTime(5);
		}
	}
}

void Laborator5::OnMouseBtnRelease(int mouseX, int mouseY, int button, int mods)
{
	// add mouse button release event
}

void Laborator5::OnMouseScroll(int mouseX, int mouseY, int offsetX, int offsetY)
{
}

void Laborator5::OnWindowResize(int width, int height)
{
}

void Laborator5::drawTowers()
{
	glm::mat4 modelMatrix = glm::mat4(1);
	modelMatrix = glm::translate(modelMatrix, glm::vec3(2, 0, 2));
	modelMatrix = glm::rotate(modelMatrix, towers[1]->getGrade(), glm::vec3(0, 1, 0));
	modelMatrix = glm::scale(modelMatrix, glm::vec3(0.002f));

	glViewport(0, 0, resolutionX, resolutionY);
	RenderMesh(meshes[towers[1]->getName()], shaders["VertexNormal"], modelMatrix);

	glViewport(0, 0, resolutionX / 4, resolutionY / 4);
	modelMatrix = glm::scale(modelMatrix, glm::vec3(4.f));
	MinimapMesh(meshes[towers[1]->getName()], shaders["VertexNormal"], modelMatrix);



	modelMatrix = glm::mat4(1);
	modelMatrix = glm::translate(modelMatrix, glm::vec3(5, 0, -5));
	modelMatrix = glm::rotate(modelMatrix, towers[0]->getGrade(), glm::vec3(0, 1, 0));
	modelMatrix = glm::scale(modelMatrix, glm::vec3(0.002f));

	glViewport(0, 0, resolutionX, resolutionY);
	RenderMesh(meshes[towers[0]->getName()], shaders["VertexNormal"], modelMatrix);

	glViewport(0, 0, resolutionX / 4, resolutionY / 4);
	modelMatrix = glm::scale(modelMatrix, glm::vec3(4.f));
	MinimapMesh(meshes[towers[0]->getName()], shaders["VertexNormal"], modelMatrix);



	modelMatrix = glm::mat4(1);
	modelMatrix = glm::translate(modelMatrix, glm::vec3(-3, 0, -4));
	modelMatrix = glm::rotate(modelMatrix, towers[2]->getGrade(), glm::vec3(0, 1, 0));
	modelMatrix = glm::scale(modelMatrix, glm::vec3(0.002f));

	glViewport(0, 0, resolutionX, resolutionY);
	RenderMesh(meshes[towers[2]->getName()], shaders["VertexNormal"], modelMatrix);

	glViewport(0, 0, resolutionX / 4, resolutionY / 4);
	modelMatrix = glm::scale(modelMatrix, glm::vec3(4.f));
	MinimapMesh(meshes[towers[2]->getName()], shaders["VertexNormal"], modelMatrix);
}

void Laborator5::drawBullet()
{
	for (int i = 0; i < bullets.size(); i++)
	{
			float speed = bullets[i]->getSpeed();
			Bullet* bullet = bullets[i];
			setBulletMovement(bullet);
			glm::mat4 modelMatrix = glm::mat4(1);
			modelMatrix = glm::translate(modelMatrix, bullets[i]->getPosition());
			modelMatrix = glm::scale(modelMatrix, glm::vec3(0.2f));

			glViewport(0, 0, resolutionX, resolutionY);
			RenderMesh(meshes[bullets[i]->getName()], shaders["VertexNormal"], modelMatrix);
	}
}


void Laborator5::drawEnemy()
{
	for (int i = 0; i < inamici.size(); i++)
	{
		float speed = inamici[i]->getSpeed();
		Enemy* enemy = inamici[i];
		if (enemy->getLifes() > 0)
			setMovement(enemy);
		float angle = inamici[i]->getGrade();
		glm::mat4 modelMatrix = glm::mat4(1);
		modelMatrix = glm::translate(modelMatrix, inamici[i]->getPosition());
		modelMatrix = glm::rotate(modelMatrix, angle, glm::vec3(0, 1, 0));
		if (enemy->getLifes() <= 0)
		{
			modelMatrix = glm::rotate(modelMatrix, enemy->getGradeX(), glm::vec3(0, 0, 1));
			enemy->setGradeX();
			enemy->setPosition(glm::vec3(enemy->getX(), enemy->getY() - 0.02, enemy->getZ()));
		}
		modelMatrix = glm::scale(modelMatrix, glm::vec3(0.5f));

		glViewport(0, 0, resolutionX, resolutionY);
		RenderMesh(meshes[inamici[i]->getName()], shaders["VertexNormal"], modelMatrix);

		glViewport(0, 0, resolutionX / 4, resolutionY / 4);
		modelMatrix = glm::scale(modelMatrix, glm::vec3(2.f));
		MinimapMesh(meshes[inamici[i]->getName()], shaders["VertexNormal"], modelMatrix);
	}
}

void Laborator5::setTime(float deltaTime)
{
	time -= deltaTime;
	if (time <= 0)
	{
		addEnemy();
		time = enemyInterval;
	}

	resetTime -= deltaTime;
	if (resetTime <= 0)
	{
		resetTime = 30;
		enemyInterval -= 0.2;
	}
}

void Laborator5::setTowerTime(float deltaTime)
{
	for (int i = 0; i < towers.size(); i++)
	{
		towers[i]->setTime(towers[i]->getTime() - deltaTime);
	}
}

float Laborator5::setTowerAngle(float x, float z, float ex, float ez)
{
	float angle;
	x =x - ex;
	z =z - ez;
	angle = (float)(atan(x / z) + M_PI / 2);
	if (z < 0)
		angle += (float)M_PI;

	return angle;
}

void Laborator5::TowerShoot()
{
	if (towers[0]->getTime() < 0 && nrInamici > 0)
	{
		towers[0]->setTime(6);
		nrBullets++;
		Mesh* mesh = new Mesh("Bullet" + to_string(nrBullets));
		mesh->LoadMesh(RESOURCE_PATH::MODELS + "Tema2", "sphere.obj");
		meshes[mesh->GetMeshID()] = mesh;

		Bullet* bullet = new Bullet(5, 1, -5, 4, 0.3);
		bullet->setGrade(towers[0]->getGrade());
		bullet->setName("Bullet" + to_string(nrBullets));
		bullet->setMesh(mesh);
		int inamic = findEnemy(5, -5);
		float ex = inamici[inamic]->getX();
		float ez = inamici[inamic]->getZ();

		towers[0]->setGrade(setTowerAngle(5, -5, ex, ez));

		float exx, ezz;
		if (ex < 5)
			exx = 5 - ex;
		else
			exx = ex - 5;
		if (ez < -5)
			ezz = abs(ez + 5);
		else
			ezz = ez + 5;

		float dist = sqrt(exx * exx + ezz * ezz);

		float angle = exx / dist;
		float tx = 0.3 * angle;

		angle = ezz / dist;
		float tz = 0.3 * angle;

		if (ex < 5)
			bullet->setTargetX(-tx);
		else
			bullet->setTargetX(tx);

		if (ez < -5)
			bullet->setTargetZ(-tz);
		else
			bullet->setTargetZ(tz);

		bullets.push_back(bullet);
	}

	if (towers[1]->getTime() < 0 && nrInamici > 0)
	{
		towers[1]->setTime(10);
		nrBullets++;
		Mesh* mesh = new Mesh("Bullet" + to_string(nrBullets));
		mesh->LoadMesh(RESOURCE_PATH::MODELS + "Tema2", "sphere.obj");
		meshes[mesh->GetMeshID()] = mesh;

		Bullet* bullet = new Bullet(2, 1, 2, 4, 0.3);
		bullet->setGrade(towers[1]->getGrade());
		bullet->setName("Bullet" + to_string(nrBullets));
		bullet->setMesh(mesh);
		int inamic = findEnemy(2, 2);
		
		float ex = inamici[inamic]->getX();
		float ez = inamici[inamic]->getZ();

		towers[1]->setGrade(setTowerAngle(2, 2, ex, ez));

		float exx, ezz;
		if (ex < 2)
			exx = 2 - ex;
		else
			exx = ex - 2;
		if (ez < 2)
			ezz = 2 - ez;
		else
			ezz = ez - 2;

		float dist = sqrt(exx * exx + ezz * ezz);

		float angle = exx / dist;
		float tx = 0.3 * angle;

		angle = ezz / dist;
		float tz = 0.3 * angle;

		if (ex < 2)
			bullet->setTargetX(-tx);
		else
			bullet->setTargetX(tx);

		if (ez < 2)
			bullet->setTargetZ(-tz);
		else
			bullet->setTargetZ(tz);

		bullets.push_back(bullet);
	}

	if (towers[2]->getTime() < 0 && nrInamici > 0)
	{
		towers[2]->setTime(8);
		nrBullets++;
		Mesh* mesh = new Mesh("Bullet" + to_string(nrBullets));
		mesh->LoadMesh(RESOURCE_PATH::MODELS + "Tema2", "sphere.obj");
		meshes[mesh->GetMeshID()] = mesh;

		Bullet* bullet = new Bullet(-3, 1, -4, 4, 0.3);
		bullet->setGrade(towers[2]->getGrade());
		bullet->setName("Bullet" + to_string(nrBullets));
		bullet->setMesh(mesh);
		int inamic = findEnemy(-3, -4);
		
		float ex = inamici[inamic]->getX();
		float ez = inamici[inamic]->getZ();

		towers[2]->setGrade(setTowerAngle(-3, -4, ex, ez));

		float exx, ezz;
		if (ex < -3)
			exx = -3 - ex;
		else
			exx = ex + 3;
		if (ez < -4)
			ezz = -4 - ez;
		else
			ezz = ez + 4;

		float dist = sqrt(exx * exx + ezz * ezz);

		float angle = exx / dist;
		float tx = 0.3 * angle;

		angle = ezz / dist;
		float tz = 0.3 * angle;

		if (ex < -3)
			bullet->setTargetX(-tx);
		else
			bullet->setTargetX(tx);

		if (ez < -4)
			bullet->setTargetZ(-tz);
		else
			bullet->setTargetZ(tz);

		bullets.push_back(bullet);
	}
}

int Laborator5::findEnemy(float x, float z)
{
	float dist = 100;
	int inamic = 0;
	for (int i = 0; i < inamici.size(); i++)
	{
		int ex = inamici[i]->getX();
		int ez = inamici[i]->getZ();

		if (ex < x)
			ex = x - ex;
		else
			ex = ex - x;
		if (ez < z)
			ez = z - ez;
		else
			ez = ez - z;

		int distE = sqrt(ex*ex + ez*ez);
		if (dist > distE)
		{
			inamic = i;
			dist = distE;
		}
	}

	return inamic;
}

void Laborator5::addEnemy()
{
	nrInamici++;
	Mesh* mesh = new Mesh("Enemy" + to_string(nrInamici));
	mesh->LoadMesh(RESOURCE_PATH::MODELS + "Tema2", "MonsterLowPoly.obj");
	meshes[mesh->GetMeshID()] = mesh;

	Enemy* enemy = new Enemy(-10, 0.65, -10, 20, 0.03);
	enemy->setMesh(mesh);
	enemy->setGrade(M_PI/2);
	enemy->setName("Enemy" + to_string(nrInamici));

	inamici.push_back(enemy);
}

void Laborator5::setBulletMovement(Bullet* bullet)
{
	if(bullet->getType() != 3)
		bullet->setPosition(glm::vec3(bullet->getX() + bullet->getTargetX(), bullet->getY(), bullet->getZ() + bullet->getTargetZ()));
	else
	{
		bullet->setPosition(glm::vec3(bullet->getX() + bullet->getTargetX(), bullet->getY() + bullet->getMoveY(), bullet->getZ() + bullet->getTargetZ()));
		bullet->setMoveY();
	}
		bullet->setDistance(bullet->getSpeed());
}

void Laborator5::setMovement(Enemy* enemy)
{
	if (enemy->getMove() == 1)
	{
		enemy->setPosition(glm::vec3(enemy->getX() + enemy->getSpeed(), enemy->getY(), enemy->getZ()));
		if (enemy->getX() >= 10)
		{
			enemy->setMove(2);
			enemy->setGrade(- M_PI / 4);
		}
	}
	else
		if (enemy->getMove() == 2)
		{
			float x = sqrt(enemy->getSpeed() * enemy->getSpeed() / 2);
			enemy->setPosition(glm::vec3(enemy->getX() - x, enemy->getY(), enemy->getZ() + x));
			if (enemy->getX() <= -10)
			{
				enemy->setMove(3);
				enemy->setGrade(M_PI / 2);
			}
		}
		else
			if (enemy->getMove() == 3)
			{
				enemy->setPosition(glm::vec3(enemy->getX() + enemy->getSpeed(), enemy->getY(), enemy->getZ()));
				if (enemy->getX() >= 10)
				{
					enemy->setMove(4);
				}
			}
}

void Laborator5::removeBulletDistance()
{
	for (int i = bullets.size() - 1; i >= 0; i--)
	{
		if (bullets[i]->getType() != 3)
		{
			if (bullets[i]->getDistance() <= 0)
			{
				bullets.erase(bullets.begin() + i);
				nrBullets--;
			}
		}
		else
		{
			if (bullets[i]->getDistance() <= 0)
			{
				elimGrenade(bullets[i]->getX(), bullets[i]->getZ());
				bullets.erase(bullets.begin() + i);
				nrBullets--;
			}
		}
	}
}

void Laborator5::elimGrenade(float x, float z)
{
	for (int i = inamici.size() - 1; i >= 0; i--)
	{
		float xx = inamici[i]->getX() - x;
		float zz = inamici[i]->getZ() - z;
		float dist = xx*xx + zz*zz;
		if (dist <= 2.5)
		{
			inamici[i]->setLifes(-1);
		}
	}
}

void Laborator5::hitEnemys()
{
	int ok = 0;
	for (int i = 0; i < inamici.size(); i++)
	{
		for (int j = 0; j < bullets.size(); j++)
		{
			if (bullets[j]->getType() != 3)
			{
				float x = inamici[i]->getX() - bullets[j]->getX();
				float z = inamici[i]->getZ() - bullets[j]->getZ();

				float dist = x*x + z*z;
				if (dist < 1)
				{
					inamici[i]->setLifes(inamici[i]->getLifes() - bullets[j]->getType());
					elimBullets.push_back(j);
					nrBullets--;
				}
			}
		}
	}
}

void Laborator5::elimBullet()
{
	for (int i = elimBullets.size() - 1; i >= 0; i--)
	{
		if (bullets.size() > elimBullets[i])
		{
			bullets.erase(bullets.begin() + elimBullets[i]);
			nrBullets--;
		}
	}
	elimBullets.clear();
}

void Laborator5::elimEnemies()
{
	for (int i = inamici.size() - 1; i >= 0; i--)
	{
		if (inamici[i]->getLifes() <= 0)
			if (inamici[i]->getGradeX() > M_PI/2)
			{
				inamici.erase(inamici.begin() + i);
				nrInamici--;
			}

	}
}
