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
	//	unsigned char * buffer;		//文件夹下所有图像像素数据
	//	unsigned short columns;		//像素列数
	//	unsigned short rows;			//像素行数
	//	unsigned short bitCount;		//图像位深
	//	int countImages;					//文件夹下图像个数
	//	size_t bufferSize;					//所有像素数据大小
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