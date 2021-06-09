/*

#include <vector>

// GLM
#include "dependencies/include/glm/glm.hpp"

#include "getUVs.hpp"

using namespace glm;

//MeshVertices 为mesh上的vertices点
//normal为 映射的方向
//返回 uv
void getUVs(std::vector<vec3> vertices, 
	vec3 normal, 
	std::vector<vec3>& uvs)
{
	float maxU = 0.0, minU = 0.0, maxV = 0.0, minV = 0.0;
	for (int i = 0; i < vertices.size() - 1; i++)
	{
		uvs.push_back(vec3());
		if (normal == (vec3(1, 0, 0)))
		{
			uvs[i].x = MeshVertices.Last().Y - MeshVertices[i].Y;
			if (uv[i].X > maxU)
			{
				maxU = uv[i].X;
			}
			else
			{
				if (uv[i].X < minU)
				{
					minU = uv[i].X;
				}
			}
			uv[i].Y = MeshVertices.Last().Z - MeshVertices[i].Z;
			if (uv[i].Y > maxV) {
				maxV = uv[i].Y;
			}
			else {
				if (uv[i].Y < minV)
				{
					minV = uv[i].Y;
				}
			}
		}
		else if (normal.Equals(FVector(0, 1, 0)))
		{
			uv[i].X = MeshVertices.Last().X - MeshVertices[i].X;
			if (uv[i].X > maxU)
			{
				maxU = uv[i].X;
			}
			else
			{
				if (uv[i].X < minU)
				{
					minU = uv[i].X;
				}
			}
			uv[i].Y = MeshVertices.Last().Z - MeshVertices[i].Z;
			if (uv[i].Y > maxV) {
				maxV = uv[i].Y;
			}
			else {
				if (uv[i].Y < minV)
				{
					minV = uv[i].Y;
				}
			}
		}
		else if (normal.Equals(FVector(0, 0, 1)))
		{
			uv[i].X = MeshVertices.Last().X - MeshVertices[i].X;
			if (uv[i].X > maxU)
			{
				maxU = uv[i].X;
			}
			else
			{
				if (uv[i].X < minU)
				{
					minU = uv[i].X;
				}
			}
			uv[i].Y = MeshVertices.Last().Y - MeshVertices[i].Y;
			if (uv[i].Y > maxV) {
				maxV = uv[i].Y;
			}
			else {
				if (uv[i].Y < minV)
				{
					minV = uv[i].Y;
				}
			}
		}
		else {
			uv[i].X = MeshVertices.Last().X - MeshVertices[i].X;
			if (uv[i].X > maxU)
			{
				maxU = uv[i].X;
			}
			else
			{
				if (uv[i].X < minU)
				{
					minU = uv[i].X;
				}
			}
			uv[i].Y = MeshVertices.Last().Y - MeshVertices[i].Y;
			if (uv[i].Y > maxV) {
				maxV = uv[i].Y;
			}
			else {
				if (uv[i].Y < minV)
				{
					minV = uv[i].Y;
				}
			}
		}
	}
	float lenghtU = maxU - minU;
	float lenghtV = maxV - minV;
	float uOffset = minU / lenghtU;
	float vOffset = minV / lenghtV;
	for (int i = 0; i < MeshVertices.Num() - 1; i++)
	{
		uv[i].X = uv[i].X / lenghtU - uOffset;
		uv[i].Y = uv[i].Y / lenghtV - vOffset;
	}
	uv.Add(FVector2D().ZeroVector);
}

*/