#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include "TGA.h";
using namespace std;


int main() {
	TGA tempresult;
	TGA image1;
	TGA image2;
	TGA image3;
	TGA image4;
	TGA result;
	TGA expected;

	//task1
	image1 = loadImage("input/layer1.tga");
	image2 = loadImage("input/pattern1.tga");
	result = multiply(image1, image2);
	expected = loadImage("examples/EXAMPLE_part1.tga");
	cout << "1. ";
	Test(result, expected);
	writeFile("output/part1.tga", result);
	
	//task 2
	image1 = loadImage("input/car.tga");
	image2 = loadImage("input/layer2.tga");
	result = subtract(image1, image2);
	expected = loadImage("examples/EXAMPLE_part2.tga");
	cout << "2. ";
	Test(result, expected);
	writeFile("output/part2.tga", result);
	
	//task 3 
	image1 = loadImage("input/layer1.tga");
	image2 = loadImage("input/pattern2.tga");
	tempresult = multiply(image1, image2);
	image1 = loadImage("input/text.tga");
	result = screen(image1, tempresult);
	expected = loadImage("examples/EXAMPLE_part3.tga");
	cout << "3. ";
	Test(result, expected);
	writeFile("output/part3.tga", result);
	
	//task 4
	image1 = loadImage("input/circles.tga");
	image2 = loadImage("input/layer2.tga");
	tempresult = multiply(image1, image2);
	image1 = loadImage("input/pattern2.tga");
	result = subtract(tempresult, image1);
	expected = loadImage("examples/EXAMPLE_part4.tga");
	cout << "4. ";
	Test(result, expected);
	writeFile("output/part4.tga", result);
	
	//task 5
	image1 = loadImage("input/layer1.tga");
	image2 = loadImage("input/pattern1.tga");
	expected = loadImage("examples/EXAMPLE_part5.tga");
	result = overlay(image1, image2);
	cout << "5. ";
	Test(result, expected);
	writeFile("output/part5.tga", result);
	
	//task 6
	image1 = loadImage("input/car.tga");
	TGA task6;
	task6.fileHeader = image1.fileHeader;
	TGA::pixelData task6Pixel;
	task6Pixel.Red = 0, task6Pixel.Green = 200, task6Pixel.Blue = 0;
	for (unsigned int i = 0; i < (image1.fileHeader.height * image1.fileHeader.width); i++) {
		task6.imageData.push_back(image1.imageData[i] + task6Pixel);
	}
	
	expected = loadImage("examples/EXAMPLE_part6.tga");
	cout << "6. ";
	Test(task6, expected);
	writeFile("output/part6.tga", task6);
	
	//task 7
	image1 = loadImage("input/car.tga");
	expected = loadImage("examples/EXAMPLE_part7.tga");
	for (unsigned int i = 0; i < (image1.fileHeader.height * image1.fileHeader.width); i++) {
		int red = image1.imageData[i].Red;
		red *= 4;
		if (red >= 255) {
			image1.imageData[i].Red = 255;
		}
		else {
			image1.imageData[i].Red = red;
		}
		image1.imageData[i].Blue = 0;
	}
	
	cout << "7. ";
	Test(image1, expected);
	writeFile("output/part7.tga", image1);
	
	
	//task 8
	image1 = loadImage("input/car.tga");
	TGA::pixelData task8Pixel;
	TGA task8R;
	task8R.fileHeader = image1.fileHeader;
	TGA task8G;
	task8G.fileHeader = image1.fileHeader;
	TGA task8B;
	task8B.fileHeader = image1.fileHeader;
	
	for (unsigned int i = 0; i < (image1.fileHeader.height * image1.fileHeader.width); i++) {
		task8Pixel.Green = task8Pixel.Blue = task8Pixel.Red = image1.imageData[i].Red;
		task8R.imageData.push_back(task8Pixel);
	
		task8Pixel.Green = task8Pixel.Blue = task8Pixel.Red = image1.imageData[i].Green;
		task8G.imageData.push_back(task8Pixel);
	
		task8Pixel.Green = task8Pixel.Blue = task8Pixel.Red = image1.imageData[i].Blue;
		task8B.imageData.push_back(task8Pixel);
	
	}
		
	
	
	expected = loadImage("examples/EXAMPLE_part8_r.tga");
	cout << "8. ";
	Test(task8R, expected);
	writeFile("output/part8_r.tga", task8R);
	writeFile("output/part8_b.tga", task8B);
	writeFile("output/part8_g.tga", task8G);
	
	//task 9
	image1 = loadImage("input/layer_green.tga");
	image2 = loadImage("input/layer_red.tga");
	image3 = loadImage("input/layer_blue.tga");
	TGA task9;
	task9.fileHeader = image1.fileHeader;
	TGA::pixelData task9Pixel;
	
	for (unsigned int i = 0; i < (image1.fileHeader.height * image1.fileHeader.width); i++) {
		task9Pixel.Red = image2.imageData[i].Red;
		task9Pixel.Green = image1.imageData[i].Green;
		task9Pixel.Blue = image3.imageData[i].Blue;
		task9.imageData.push_back(task9Pixel);
	}
	
	expected = loadImage("examples/EXAMPLE_part9.tga");
	cout << "9. ";
	Test(task9, expected);
	writeFile("output/part9.tga", task9);
	
	//task 10
	image1 = loadImage("input/text2.tga");
	TGA task10;
	//TGA::pixelData task10Pixel;
	task10.fileHeader = image1.fileHeader;
	expected = loadImage("examples/EXAMPLE_part10.tga");
	
	for (int i = (image1.fileHeader.height * image1.fileHeader.width - 1); i >= 0; i--) {
		//task10Pixel = image1.imageData[i];
		task10.imageData.push_back(image1.imageData[i]);
	}
	
	//for (unsigned int i = 0; i < (image1.fileHeader.height * image1.fileHeader.width); i++) {
	//	cout << "Result: " << (int)task10.imageData[i].Red << ", " << (int)task10.imageData[i].Green << ", " << (int)task10.imageData[i].Blue << endl;
	//	cout << "Expected: " << (int)expected.imageData[i].Red << ", " << (int)expected.imageData[i].Green << ", " << (int)expected.imageData[i].Blue << endl;
	//}
	
	cout << "10. ";
	Test(expected, task10);
	writeFile("output/part10.tga", task10);

// extracredit
image1 = loadImage("input/car.tga");
image2 = loadImage("input/circles.tga");
image4 = loadImage("input/pattern1.tga");
image3 = loadImage("input/text.tga");
	TGA extracredit;
	TGA::pixelData ECPixel;
	extracredit.fileHeader = image1.fileHeader;
	//cout << extracredit.fileHeader.height << endl;
	extracredit.fileHeader.height = 1024;
	extracredit.fileHeader.width = 1024;

	//expected = loadImage("examples/EXAMPLE_part10.tga");
	unsigned int i = 0;
	unsigned int j = 0;
	unsigned int k = 0;
	unsigned int l = 0;
	
	//for (i = 0; i < (extracredit.fileHeader.height * extracredit.fileHeader.width); i++) {
	//	ECPixel = image1.imageData[i];
	//	extracredit.imageData.push_back(ECPixel);
	//	}
	for (i = 0; i < (image3.fileHeader.height); i++) {
		for (j = 0; j < (image4.fileHeader.width); j++) {
			ECPixel = image3.imageData[k];
			k++;
			extracredit.imageData.push_back(ECPixel);
		}
		for (j = 0; j < (image4.fileHeader.width); j++) {
			ECPixel = image4.imageData[l];
			l++;
			extracredit.imageData.push_back(ECPixel);
		}
	}
	k = l = 0;
	
	for (i = 0; i < (image1.fileHeader.height); i++) {
		for (j = 0; j < (image1.fileHeader.width); j++){
			ECPixel = image1.imageData[k];
			k++;
			extracredit.imageData.push_back(ECPixel);
		}
		for (j = 0; j < (image1.fileHeader.width); j++) {
			ECPixel = image2.imageData[l];
			l++;
			extracredit.imageData.push_back(ECPixel);
		}
		
	}

	cout << "EC: ";
 	//Test(extracredit, expected);

	ofstream file("output/extracredit.tga", ios_base::out | ios_base::binary);
	file.write(&extracredit.fileHeader.idLength, 1);
	file.write(&extracredit.fileHeader.colorMapType, 1);
	file.write(&extracredit.fileHeader.dataTypeCode, 1);
	file.write((char*)(&extracredit.fileHeader.colorMapOrigin), 2);
	file.write((char*)(&extracredit.fileHeader.colorMapLength), 2);
	file.write(&extracredit.fileHeader.colorMapDepth, 1);
	file.write((char*)(&extracredit.fileHeader.xOrigin), 2);
	file.write((char*)(&extracredit.fileHeader.yOrigin), 2);
	file.write((char*)(&extracredit.fileHeader.width), 2);
	file.write((char*)(&extracredit.fileHeader.height), 2);
	file.write(&extracredit.fileHeader.bitsPerPixel, 1);
	file.write(&extracredit.fileHeader.imageDescriptor, 1);


	for (unsigned int i = 0; i < (extracredit.fileHeader.height * extracredit.fileHeader.width); i++) {
		TGA::pixelData pixel = extracredit.imageData[i];
		file.write((char*)(&pixel.Blue), 1);
		file.write((char*)(&pixel.Green), 1);
		file.write((char*)(&pixel.Red), 1);

	}
	return 0;
}