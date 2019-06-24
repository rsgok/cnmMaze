#ifndef _SCREENSHOT_H_
#define _SCREENSHOT_H_

#include <Windows.h>
#include <stdio.h>
#include <gl/glut.h>
#include <string>
#include <time.h>

#define BITMAP_ID 0x4D42

using namespace std;

bool SnapScreen(int width, int height){
	static int count = 0;
	string saveFile("screen_shots/shot");
	char buf[5][10];
	time_t t;
	struct tm tmval;
	time(&t);
	tmval = *localtime(&t);
	_itoa(tmval.tm_mday, buf[0], 10);
	_itoa(tmval.tm_hour, buf[1], 10);
	_itoa(tmval.tm_min, buf[2], 10);
	_itoa(tmval.tm_sec, buf[3], 10);
	_itoa(++count, buf[4], 10);

	saveFile = saveFile + buf[1] + buf[2] + buf[3] + "-" + buf[4] + ".bmp";
	char* file = (char *)saveFile.c_str();
	typedef unsigned char byte;
	byte *image;
	FILE *fp;
	BITMAPFILEHEADER FileHeader;
	BITMAPINFOHEADER InfoHeader;

	FileHeader.bfType = BITMAP_ID;
	FileHeader.bfOffBits = sizeof(BITMAPFILEHEADER) + sizeof(BITMAPINFOHEADER);
	FileHeader.bfReserved1 = 0;
	FileHeader.bfReserved2 = 0;
	FileHeader.bfSize = height * width * 24 + FileHeader.bfOffBits;

	InfoHeader.biXPelsPerMeter = 0;
	InfoHeader.biYPelsPerMeter = 0;
	InfoHeader.biClrUsed = 0;
	InfoHeader.biClrImportant = 0;
	InfoHeader.biPlanes = 1;
	InfoHeader.biCompression = BI_RGB;
	InfoHeader.biBitCount = 24;
	InfoHeader.biSize = sizeof(BITMAPINFOHEADER);
	InfoHeader.biHeight = height;
	InfoHeader.biWidth = width;
	InfoHeader.biSizeImage = height * width * 4;

	image = (byte *)malloc(sizeof(byte)*InfoHeader.biSizeImage);
	if (image == NULL){
		free(image);
		printf("Exception: No enough space!\n");
		return false;
	}
	//像素格式设置4字节对齐
	glPixelStorei(GL_UNPACK_ALIGNMENT, 4);
	//接收出像素的数据
	glReadPixels(0, 0, width, height, GL_BGR_EXT, GL_UNSIGNED_BYTE, image);

	fp = fopen(file, "wb");
	if (fp == NULL){
		printf("Error: Fail to open file!\n");
		return false;
	}
	fwrite(&FileHeader, sizeof(BITMAPFILEHEADER), 1, fp);
	fwrite(&InfoHeader, sizeof(BITMAPINFOHEADER), 1, fp);
	fwrite(image, InfoHeader.biSizeImage, 1, fp);
	free(image);
	fclose(fp);
	printf("ScreenShot has been saved successfully.[%s]\n", file);
	return true;
}

#endif
