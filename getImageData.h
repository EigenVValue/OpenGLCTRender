#ifndef GETIMAGEDATA_HPP
#define GETIMAGEDATA_HPP

void getImageData(
	const char* path,
	std::vector<uint8_t> &raw,
	unsigned int &dimX,
	unsigned int &dimY,
	unsigned int &dimZ
);

#endif