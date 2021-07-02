#include <vector>

#include "glm/vec3.hpp"
#include "glm/vec2.hpp"

#include "getUVs.hpp"

using namespace glm;

/*
CN:
CT ֵ��
����֯:		>400	����:	50-70	Ƣ��:	35-60
Ѫ��:		64-84	����:	30-55	����:	25-50
����:		40-55	����:	10-30	ѪҺ:	13-32
ˮ:			0			Ѫ��:	3-14		֬��:	-100-[-20]
�԰���:		25-34	�Ի���:	28-44	�Լ�Һ:	3-8
��״��:		50-90

Ŀǰ��ͼֻ����:
1. ֬��			-100-[-20]	RGB: (255,165,40)
2. ˮ				0				RGB: (127,255,212)
3. Ѫ��			3-10			RGB: (135,35,10)
4. ����			11-30		RGB: (0,139,0)
5. ��ϲ���	31-50		RGB: (235,20,90)
6. ����			51-70		RGB: (0,205,0)
7. ��				>400		RGB: (190,190,190)
���࣬���٣����⣬Ƣ��ͳ��Ϊһ����ɫ(5)����ΪĿǰ��������
����CTֵΪ��ɫ (255,255,255)

�Բ������Ӽ�״��û����
������Ҫdcmtk��ȡtag��Body Part Examined (0018,0015) --> HEAD
*/

void getUVs(
	const std::vector<vec3> & vertices, 
	const std::vector<int> & colors,
	std::vector<vec2> & uvs
) {
	//	1. ֬��			-100 - [-20]
	//	2. ˮ				0
	//	3. Ѫ��			3 - 10
	//	4. ����			11 - 30
	//	5. ��ϲ���	31 - 50
	//	6. ����			51 - 70
	//	7. ��				>400

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