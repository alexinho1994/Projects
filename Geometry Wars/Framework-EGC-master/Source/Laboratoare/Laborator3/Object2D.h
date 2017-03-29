#pragma once

#include <string>

#include <include/glm.h>
#include <Core/GPU/Mesh.h>
#include <vector>

using namespace std;

namespace Object2D
{
	Mesh* CreateSquare(std::string name, glm::vec3 leftBottomCorner, float length, glm::vec3 color, bool fill = false);

	Mesh* CreateLife(std::string name, glm::vec3 leftBottomCorner, float length, glm::vec3 color);
};


