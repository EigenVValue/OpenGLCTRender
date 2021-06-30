#include <Windows.h>
#include <vector>

// Inclued WANLI's file
#include "dependencies/include/converttobmp.h"

void getImageData(
		const char* path, 
		std::vector<uint8_t> &raw,
		unsigned int &dimX,
		unsigned int &dimY,
		unsigned int &dimZ,
		int &rescale_intercept,
		unsigned short &rescale_slope
){
	// Struct see converttobmp.h file
	//struct DcmData {
	//	unsigned char * buffer;		//�ļ���������ͼ����������
	//	unsigned short columns;		//��������
	//	unsigned short rows;		//��������
	//	int countImages;			//�ļ�����ͼ�����
	//	size_t bufferSize;			//�����������ݴ�С
	//	int RescaleIntercept;		//Rescale Intercept
	//	unsigned short RescaleSlope;			//Rescale Slope
	//};
	DcmData data;
	int bufferSize = converttobmp(
		path,
		&data
	);

	// get values
	dimX = data.columns;
	dimY = data.rows;
	dimZ = data.countImages;
	rescale_intercept = data.RescaleIntercept;
	rescale_slope = data.RescaleSlope;

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

}