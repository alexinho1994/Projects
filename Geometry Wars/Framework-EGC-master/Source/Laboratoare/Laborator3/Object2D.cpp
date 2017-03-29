#include "Object2D.h"

#include <Core/Engine.h>

using namespace std;


Mesh* Object2D::CreateSquare(std::string name, glm::vec3 leftBottomCorner, float length, glm::vec3 color, bool fill)
{
	glm::vec3 corner = leftBottomCorner;

	std::vector<VertexFormat> vertices =
	{
		VertexFormat(corner + glm::vec3(-length/2, -length*sqrt(3)/2, 0), color),
		VertexFormat(corner, color),
		VertexFormat(corner + glm::vec3(length/2, -length*sqrt(3) / 2, 0), color),
		VertexFormat(corner + glm::vec3(-length / 2, length*sqrt(3) / 2, 0), color),
		VertexFormat(corner + glm::vec3(length/2, length*sqrt(3) / 2, 0), color)
	};

	Mesh* square = new Mesh(name);
	std::vector<unsigned short> indices = { 0, 1, 2, 4, 3, 1};
	
	if (!fill) {
		square->SetDrawMode(GL_LINE_LOOP);
	}
	else {
		// draw 2 triangles. Add the remaining 2 indices
		indices.push_back(0);
		indices.push_back(2);
	}

	square->InitFromData(vertices, indices);
	return square;
}

Mesh* Object2D::CreateLife(std::string name, glm::vec3 leftBottomCorner, float length, glm::vec3 color)
{
	glm::vec3 corner = leftBottomCorner;

	std::vector<VertexFormat> vertices =
	{
		VertexFormat(corner + glm::vec3(0, 0, 0), color),
		VertexFormat(corner + glm::vec3(length / 5, 0, 0), color),
		VertexFormat(corner + glm::vec3(length / 5, length, 0), color),
		VertexFormat(corner + glm::vec3(0, length, 0), color)
	};

	Mesh* square = new Mesh(name);
	std::vector<unsigned short> indices = { 0, 1, 2, 3};

	square->InitFromData(vertices, indices);
	return square;
}

