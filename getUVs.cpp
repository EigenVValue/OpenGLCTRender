#include <vector>

#include "glm/vec3.hpp"
#include "glm/vec2.hpp"

#include "getUVs.hpp"

using namespace glm;

/*
CN:
CT 值：
骨组织:		>400	肝脏:	50-70	脾脏:	35-60
血块:		64-84	胰腺:	30-55	肾脏:	25-50
肌肉:		40-55	胆囊:	10-30	血液:	13-32
水:			0			血浆:	3-14		脂肪:	-100-[-20]
脑白质:		25-34	脑灰质:	28-44	脑脊液:	3-8
甲状腺:		50-90

目前贴图只区分:
1. 脂肪			-100-[-20]	RGB: (255,165,40)
2. 水				0				RGB: (127,255,212)
3. 血浆			3-10			RGB: (135,35,10)
4. 胆囊			11-30		RGB: (0,139,0)
5. 混合部分	31-50		RGB: (235,20,90)
6. 肝脏			51-70		RGB: (0,205,0)
7. 骨				>400		RGB: (190,190,190)
肾脏，胰腺，肌肉，脾脏统合为一种颜色(5)，因为目前难以区分
其他CT值为白色 (255,255,255)

脑部几个加甲状腺没处理，
可能需要dcmtk获取tag：Body Part Examined (0018,0015) --> HEAD
*/

void getUVs(
	const std::vector<vec3> & vertices, 
	const std::vector<int> & colors,
	std::vector<vec2> & uvs
) {
	//	1. 脂肪			-100 - [-20]
	//	2. 水				0
	//	3. 血浆			3 - 10
	//	4. 胆囊			11 - 30
	//	5. 混合部分	31 - 50
	//	6. 肝脏			51 - 70
	//	7. 骨				>400

	for (auto color : colors)
	{
		vec2 uv;
		//if (color >= -100 && color <= -20)+
		if (color >= 0 && color <= 100)
		{
			uv = vec2(0.25f, 1.0f-0.25f);
		}
		//else if (color == 0)
		//else if (color >= 33 && color <= 64)
		//{
		//	uv = vec2(0.125f, 1.0f - 0.125f);
		//}
		//else if (color >=3 && color <= 10)
		else if (color >= 101 && color <= 240)
		{
			uv = vec2(0.75f, 1.0f - 0.25f);
		}
		//else if (color >= 11 && color <= 30)
		//else if (color >= 97 && color <= 128)
		//{
		//	uv = vec2(0.375f, 1.0f - 0.375f);
		//}
		//else if (color >= 31 && color <= 50)
		//else if (color >=201 && color <= 254)
		//{
		//	uv = vec2(0.5f, 1.0f - 0.5f);
		//}
		//else if (color >= 51 && color <= 70)
		//else if (color >= 161 && color <= 192)
		//{
		//	uv = vec2(0.625f, 1.0f - 0.625f);
		//}
		//else if (color >= 400)
		else if (color >= 241 && color <= 255)
		{
			uv = vec2(0.25f, 1.0f - 0.75f);
		}
		else
		{
			uv = vec2(0.75f, 1.0f - 0.75f);
		}
		uvs.push_back(uv);
	}
}