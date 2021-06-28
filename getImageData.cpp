#include <Windows.h>
#include <vector>

// Inclued WANLI's file
#include "dependencies/include/converttobmp.h"

void getImageData(
		const char* path, 
		std::vector<uint8_t> &raw,
		unsigned int &dimX,
		unsigned int &dimY,
		unsigned int &dimZ
){
	// Struct see converttobmp.h file
	// struct DcmData {
	//	unsigned char * buffer;		//�ļ���������ͼ����������
	//	unsigned short columns;		//��������
	//	unsigned short rows;			//��������
	//	unsigned short bitCount;		//ͼ��λ��
	//	int countImages;					//�ļ�����ͼ�����
	//	size_t bufferSize;					//�����������ݴ�С
	//};
	DcmData data;
	int bufferSize = converttobmp(
		path,
		&data
	);

	// set size
	dimX = data.columns;
	dimY = data.rows;
	dimZ = data.countImages;

	// char size == dim of x (height) * dim of y (width) * dim of z(total number of dcm files)
	raw.resize(data.rows*data.columns*data.countImages);

	for (int z = 0; z < dimZ; z++)
	{
		for (int y = 0; y < dimY; y++)
		{
			for (int x = 0; x < dimX; x++)
			{
				uint8_t tmp = data.buffer[
					(x + y * dimX + z * dimX * dimY) * 4
					+ sizeof(BITMAPFILEHEADER)*(z+1)
					+ sizeof(BITMAPINFOHEADER)*(z+1)
				];
				raw[x + y * dimX + z * dimX * dimY] = tmp;
			}
		}
	}
	
	// TODO: remove noise.

}