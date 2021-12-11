#include <iostream>
#include <vector>
#include <fstream>
#include "TGA.h"
using namespace std;


TGA::TGA() {
    fileHeader = Header();
}

TGA::Header::Header() {
    idLength = 0;
    colorMapType = 0;
    dataTypeCode = 0;
    colorMapOrigin = 0;
    colorMapLength = 0;
    colorMapDepth = 0;
    xOrigin = 0;
    yOrigin = 0;
    width = 0;
    height = 0;
    bitsPerPixel = 0;
    imageDescriptor = 0;
}

TGA::pixelData& TGA::pixelData::operator-(TGA::pixelData pixel) {
	int colorData = (int)Red;
	colorData -= (int)pixel.Red;
	if (colorData <= 0) 
		this->Red = 0;
	else this->Red = (unsigned char)colorData;
	colorData = (int)Green;
	colorData -= (int)pixel.Green;
	if (colorData <= 0) 
		this->Green = 0;
	else this->Green = (unsigned char)colorData;
	colorData = (int)Blue;
	colorData -= (int)pixel.Blue;
	if (colorData <= 0) 
		this->Blue = 0;
	else this->Blue = (unsigned char)colorData;
		
	return *this;
}

TGA::pixelData& TGA::pixelData::operator+(TGA::pixelData pixel) {
	int colorData = (int)Red;
	colorData += (int)pixel.Red;
	if (colorData >= 255)
		this->Red = 255;
	else this->Red = (unsigned char)colorData;
	colorData = (int)Green;
	colorData += (int)pixel.Green;
	if (colorData >= 255)
		this->Green = 255;
	else this->Green = (unsigned char)colorData;
	colorData = (int)Blue;
	colorData += (int)pixel.Blue;
	if (colorData >= 255)
		this->Blue = 255;
	else this->Blue = (unsigned char)colorData;

	return *this;
}


TGA::pixelData& TGA::pixelData::operator*(TGA::pixelData pixel) {
	this->Red = (unsigned char)((((float)Red / 255.0f) * ((float)pixel.Red / 255.0f))*255.0f + 0.5f);
	this->Blue = (unsigned char)((((float)Blue / 255.0f) * ((float)pixel.Blue / 255.0f)) * 255.0f + 0.5f);
	this->Green = (unsigned char)((((float)Green / 255.0f) * ((float)pixel.Green / 255.0f)) * 255.0f + 0.5f);

	return *this;
}

bool TGA::pixelData::operator==(TGA::pixelData pixel) {
	bool equals = false;
	if (Red == pixel.Red && Green == pixel.Green && Blue == pixel.Blue) {
		equals = true;
	}
	return equals;
}

TGA::pixelData& TGA::pixelData::operator=(TGA::pixelData pixel) {
	Red = pixel.Red;
	Blue = pixel.Blue;
	Green = pixel.Green;
	
	return *this;
}




TGA loadImage(string fileName) {
	ifstream file(fileName, ios_base::binary);

	if (file.is_open()) {
		TGA image;

		file.read(&image.fileHeader.idLength, 1);
		file.read(&image.fileHeader.colorMapType, 1);
		file.read(&image.fileHeader.dataTypeCode, 1);
		file.read((char*)(&image.fileHeader.colorMapOrigin), 2);
		file.read((char*)(&image.fileHeader.colorMapLength), 2);
		file.read(&image.fileHeader.colorMapDepth, 1);
		file.read((char*)(&image.fileHeader.xOrigin), 2);
		file.read((char*)(&image.fileHeader.yOrigin), 2);
		file.read((char*)(&image.fileHeader.width), 2);
		file.read((char*)(&image.fileHeader.height), 2);
		file.read(&image.fileHeader.bitsPerPixel, 1);
		file.read(&image.fileHeader.imageDescriptor, 1);

		//cout << (int(image.fileHeader.width)) << endl;
		//cout << (int(image.fileHeader.height)) << endl;

		for (unsigned int i = 0; i < (image.fileHeader.height * image.fileHeader.width); i++) {
			TGA::pixelData pixel;
			file.read((char*)(&pixel.Blue), 1);
			file.read((char*)(&pixel.Green), 1);
			file.read((char*)(&pixel.Red), 1);
			image.imageData.push_back(pixel);
		}
		return image;
	}
	else {
		cout << "File not open" << endl;
	}
}

void writeFile(string fileName, TGA image) {
	ofstream file(fileName, ios_base::out | ios_base::binary);
	file.write(&image.fileHeader.idLength, 1);
	file.write(&image.fileHeader.colorMapType, 1);
	file.write(&image.fileHeader.dataTypeCode, 1);
	file.write((char*)(&image.fileHeader.colorMapOrigin), 2);
	file.write((char*)(&image.fileHeader.colorMapLength), 2);
	file.write(&image.fileHeader.colorMapDepth, 1);
	file.write((char*)(&image.fileHeader.xOrigin), 2);
	file.write((char*)(&image.fileHeader.yOrigin), 2);
	file.write((char*)(&image.fileHeader.width), 2);
	file.write((char*)(&image.fileHeader.height), 2);
	file.write(&image.fileHeader.bitsPerPixel, 1);
	file.write(&image.fileHeader.imageDescriptor, 1);


	for (unsigned int i = 0; i < (image.fileHeader.height * image.fileHeader.width); i++) {
		TGA::pixelData pixel = image.imageData[i];
		file.write((char*)(&pixel.Blue), 1);
		file.write((char*)(&pixel.Green), 1);
		file.write((char*)(&pixel.Red), 1);
		
	}
}

void Test(TGA image1, TGA image2) {
	bool same = true;
	for (unsigned int i = 0; i < (image1.fileHeader.height * image1.fileHeader.width); i++) {
		if (!(image1.imageData[i] == image2.imageData[i])){
			same = false;
			}
	}
	if (same){
		cout << "Test Passed" << endl;
	}
	else {
		cout << "Test Failed" << endl;
	}
}

TGA subtract(TGA image1, TGA image2) {
	TGA final;
	final.fileHeader = image1.fileHeader;
	for (unsigned int i = 0; i < (image1.fileHeader.height * image1.fileHeader.width); i++) {
		final.imageData.push_back(image1.imageData[i] - image2.imageData[i]);
	}
	return final;
}

TGA multiply(TGA image1, TGA image2) {
	TGA final;
	final.fileHeader = image1.fileHeader;
	for (unsigned int i = 0; i < (image1.fileHeader.height * image1.fileHeader.width); i++) {
		final.imageData.push_back(image1.imageData[i] * image2.imageData[i]);
	}
	return final;
}

TGA screen(TGA image1, TGA image2) {
	TGA final;
	final.fileHeader = image1.fileHeader;
	TGA::pixelData pixelA, pixelB, pixelC, result;

	for (unsigned int i = 0; i < (image1.fileHeader.height * image1.fileHeader.width); i++) {
		pixelA.Red = pixelB.Red = pixelC.Red = 255;
		pixelA.Green = pixelB.Green = pixelC.Green = 255;
		pixelA.Blue = pixelB.Blue = pixelC.Blue = 255;
		

		result = pixelA - ((pixelB - image1.imageData[i]) * (pixelC - image2.imageData[i]));
		final.imageData.push_back(result);
	}
	return final;
}

TGA overlay(TGA image1, TGA image2) {
	TGA final;
	final.fileHeader = image1.fileHeader;
	float pixelARed;
	float pixelBRed;
	float pixelAGreen;
	float pixelBGreen;
	float pixelABlue;
	float pixelBBlue;
	float finalred;
	float finalgreen;
	float finalblue;
	TGA::pixelData finalPixel;
	for (unsigned int i = 0; i < (image1.fileHeader.height * image1.fileHeader.width); i++) {
		pixelARed = image1.imageData[i].Red / 255.0f;
		pixelBRed = image2.imageData[i].Red / 255.0f;
		pixelAGreen = image1.imageData[i].Green / 255.0f;
		pixelBGreen = image2.imageData[i].Green / 255.0f;
		pixelABlue = image1.imageData[i].Blue / 255.0f;
		pixelBBlue = image2.imageData[i].Blue / 255.0f;
		
		if (pixelBRed <= 0.5f) {
			finalred = (pixelARed * pixelBRed * 2.0f) * 255.0f + 0.5f;
		}
		else {
			finalred = (1.0f - 2.0f * (1.0f - pixelARed) * (1.0f - pixelBRed)) * 255.0f +0.5f;
		} finalPixel.Red = finalred;
		if (pixelBGreen <= 0.5f) {
			finalgreen = (pixelAGreen * pixelBGreen * 2.0f) * 255.0f + 0.5f;
		}
		else {
			finalgreen = (1.0f - 2.0f * (1.0f - pixelAGreen) * (1.0f - pixelBGreen)) * 255.0f + 0.5f;
		} finalPixel.Green = finalgreen;
		if (pixelBBlue <= 0.5f) {
			finalblue = (pixelABlue * pixelBBlue * 2.0f) * 255.0f + 0.5f;
		}
		else {
			finalblue = (1.0f - 2.0f * (1.0f - pixelABlue) * (1.0f - pixelBBlue)) * 255.0f + 0.5f;
		} finalPixel.Blue = finalblue;

		final.imageData.push_back(finalPixel);
	}
	return final;
}