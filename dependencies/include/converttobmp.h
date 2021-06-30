#pragma once

#ifndef CONVERTBMPAPI
#define CONVERTBMPAPI __declspec(dllimport)
#endif

struct DcmData{
	unsigned char * buffer;		//�ļ���������ͼ����������
	unsigned short columns;		//��������
	unsigned short rows;		//��������
	int countImages;			//�ļ�����ͼ�����
	size_t bufferSize;			//�����������ݴ�С
	int RescaleIntercept;		//Rescale Intercept
	unsigned short RescaleSlope;			//Rescale Slope
};


//*dcmData: ����ṹ�����͵ĵ�ַ������DcmData ��Ա *buffer ��Ҫ�ֶ��ͷţ�
//if success will return zero,else return less than zero; 
CONVERTBMPAPI int __stdcall converttobmp(const char * filename, DcmData *dcmData);
CONVERTBMPAPI char* __stdcall Decode(char* addr, int size);
CONVERTBMPAPI void __stdcall Release(char*addr);
