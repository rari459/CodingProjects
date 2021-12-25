#pragma once
#include <iostream>
#include <vector>
using namespace std;

class TGA {
	public:
	struct Header
	{
		char idLength;
		char colorMapType;
		char dataTypeCode;
		short colorMapOrigin;
		short colorMapLength;
		char colorMapDepth;
		short xOrigin;
		short yOrigin;
		short width;
		short height;
		char bitsPerPixel;
		char imageDescriptor;
		Header();
	};

	struct  pixelData {
		unsigned char Red, Green, Blue;
		pixelData& operator * (pixelData pixel);
		pixelData& operator + (pixelData pixel);
		pixelData& operator - (pixelData pixel);
		bool operator == (pixelData pixel);
		pixelData& operator = (pixelData pixel);
	};

	Header fileHeader; 
	TGA();
	vector<pixelData> imageData;

};


TGA loadImage(string fileName);
void writeFile(string fileName, TGA image);
TGA subtract(TGA image1, TGA image2);
TGA multiply(TGA image1, TGA image2);
void Test(TGA image1, TGA image2);
TGA screen(TGA image1, TGA image2);
TGA overlay(TGA image1, TGA image2);


//Header headerObject;
//file.read(&headerObject.idLength, sizeof(headerObject.idLength));
//file.read(&headerObject.colorMapType, sizeof(headerObject.colorMapType));