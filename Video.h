#pragma once
// BMP file type supporting
#include <stdlib.h>
#include <iostream>
#include <fstream>
#include <string>
#include <GL/glut.h>
#define BITMAP_ID 0x4D42
using namespace std;
class Video
{
public:
	unsigned int textureVideo[10];
	int displayFPS = 0;
	unsigned char *loadBitmapFile(char *filename, BITMAPINFOHEADER *bitmapInfoHeader);
	void loadTexture(int i, char* filename);
	void initTextureVideo();
	void renderVideoFrame(GLfloat x);
	void renderVideo();
};
