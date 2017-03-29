#pragma once
#include <Component/SimpleScene.h>
#include "LabCamera.h"
#include "Enemy.h"
#include "Bullet.h"
#include "Turn.h"

using namespace std;

class Laborator5 : public SimpleScene
{
	public:
		Laborator5();
		~Laborator5();

		void Init() override;

	private:
		void FrameStart() override;
		void Update(float deltaTimeSeconds) override;
		void FrameEnd() override;

		void RenderMesh(Mesh * mesh, Shader * shader, const glm::mat4 & modelMatrix) override;
		void MinimapMesh(Mesh* mesh, Shader * shader, const glm::mat4 & modelMatrix);

		void OnInputUpdate(float deltaTime, int mods) override;
		void OnKeyPress(int key, int mods) override;
		void OnKeyRelease(int key, int mods) override;
		void OnMouseMove(int mouseX, int mouseY, int deltaX, int deltaY) override;
		void OnMouseBtnPress(int mouseX, int mouseY, int button, int mods) override;
		void OnMouseBtnRelease(int mouseX, int mouseY, int button, int mods) override;
		void OnMouseScroll(int mouseX, int mouseY, int offsetX, int offsetY) override;
		void OnWindowResize(int width, int height) override;
		void drawEnemy();
		void drawTowers();
		void drawBullet();
		void setTime(float deltaTime);
		void setTowerTime(float deltaTime);
		void TowerShoot();
		void addEnemy();
		void setMovement(Enemy* enemy);
		void setBulletMovement(Bullet* bullet);
		int findEnemy(float x, float z);
		float setTowerAngle(float x, float z, float ex, float ez);
		void removeBulletDistance();
		void hitEnemys();
		void elimGrenade(float x, float z);
		void elimBullet();
		void elimEnemies();

	protected:
		Laborator::Camera *camera, *camera2;
		glm::mat4 projectionMatrix;
		bool renderCameraTarget;
		float time;
		float resetTime;
		float enemyInterval;
		vector<Enemy*> inamici;
		vector<Bullet*> bullets;
		vector<Turn*> towers;
		vector<int> elimEnemy;
		vector<int> elimBullets;
		int nrInamici;
		int nrBullets;
		float resolutionX;
		float resolutionY;
};
