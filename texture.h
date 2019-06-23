#define _CRT_SECURE_NO_WARNINGS

#ifndef _TEXTURE_H_
#define _TEXTURE_H_

#include <stdio.h>
#include <Windows.h>
#include <gl/glut.h>

#define BITMAP_ID 0x4D42

unsigned char *LoadBitmapFile(char *filename, BITMAPINFOHEADER *bitmapInfoHeader);

void texload(GLuint* i, char *filename);


#endif