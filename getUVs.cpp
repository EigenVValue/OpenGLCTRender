#include <vector>

#include "glm/vec3.hpp"
#include "glm/vec2.hpp"

#include "getUVs.hpp"

using namespace glm;

void getUVs(std::vector<vec3> vertices, 
	vec3 normal, 
	std::vector<vec2>& uvs)
{
	float maxU = 0.0, minU = 0.0, maxV = 0.0, minV = 0.0;
	for (int i = 0; i < vertices.size() - 1; i++)
	{
		uvs.push_back(vec3(0, 0, 0));

		if (normal == (vec3(1, 0, 0)))
		{
			uvs[i].x = vertices.back().y - vertices[i].y;
			if (uvs[i].x > maxU)
			{
				maxU = uvs[i].x;
			}
			else
			{
				if (uvs[i].x < minU)
				{
					minU = uvs[i].x;
				}
			}
			uvs[i].y = vertices.back().z - vertices[i].z;
			if (uvs[i].y > maxV) {
				maxV = uvs[i].y;
			}
			else {
				if (uvs[i].y < minV)
				{
					minV = uvs[i].y;
				}
			}
		}
		else if (normal == (vec3(0, 1, 0)))
		{
			uvs[i].x = vertices.back().x - vertices[i].x;
			if (uvs[i].x > maxU)
			{
				maxU = uvs[i].x;
			}
			else
			{
				if (uvs[i].x < minU)
				{
					minU = uvs[i].x;
				}
			}
			uvs[i].y = vertices.back().z - vertices[i].z;
			if (uvs[i].y > maxV) {
				maxV = uvs[i].y;
			}
			else {
				if (uvs[i].y < minV)
				{
					minV = uvs[i].y;
				}
			}
		}
		else if (normal == (vec3(0, 0, 1)))
		{
			uvs[i].x = vertices.back().x - vertices[i].x;
			if (uvs[i].x > maxU)
			{
				maxU = uvs[i].x;
			}
			else
			{
				if (uvs[i].x < minU)
				{
					minU = uvs[i].x;
				}
			}
			uvs[i].y = vertices.back().y - vertices[i].y;
			if (uvs[i].y > maxV) {
				maxV = uvs[i].y;
			}
			else {
				if (uvs[i].y < minV)
				{
					minV = uvs[i].y;
				}
			}
		}
		else {
			uvs[i].x = vertices.back().x - vertices[i].x;
			if (uvs[i].x > maxU)
			{
				maxU = uvs[i].x;
			}
			else
			{
				if (uvs[i].x < minU)
				{
					minU = uvs[i].x;
				}
			}
			uvs[i].y = vertices.back().y - vertices[i].y;
			if (uvs[i].y > maxV) {
				maxV = uvs[i].y;
			}
			else {
				if (uvs[i].y < minV)
				{
					minV = uvs[i].y;
				}
			}
		}
	}
	float lengthU = maxU - minU;
	float lengthV = maxV - minV;
	float uOffset = minU / lengthU;
	float vOffset = minV / lengthV;
	for (int i = 0; i < vertices.size() - 1; i++)
	{
		uvs[i].x = uvs[i].x / lengthU - uOffset;
		uvs[i].y = uvs[i].y / lengthV - vOffset;
	}
	uvs.push_back(vec3(0.0f, 0.0f, 0.0f));
}