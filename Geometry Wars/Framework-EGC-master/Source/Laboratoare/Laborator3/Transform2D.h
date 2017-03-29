#pragma once

#include <include/glm.h>

namespace Transform2D
{
	// Translate matrix
	inline glm::mat3 Translate(float tX, float tY)
	{
		// TODO implement translate matrix
		return glm::mat3(
			1, 0, 0,
			0, 1, 0,
			tX, tY, 1);
	}

	// Scale matrix
	inline glm::mat3 Scale(float sX, float sY)
	{
		// TODO implement scale matrix
		return glm::transpose(
			glm::mat3(sX, 0, 0,
				0, sY, 0,
				0, 0, 1)
		);
	}

	// Rotate matrix
	inline glm::mat3 Rotate(float rad)
	{
		// TODO implement rotate matrix
		return glm::mat3(
			cos(rad), sin(rad), 0,
			-sin(rad), cos(rad), 0,
			0, 0, 1);
	}
}
