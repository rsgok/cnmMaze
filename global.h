#pragma once

#ifndef _GLOBAL_H_
#define _GLOBAL_H_

#include <stdio.h>
#include <stdlib.h>
#include <gl/glut.h>
#include <math.h>
#include <Windows.h>
#include <ctime>
#include <vector>
#include "mydraw.h"
#include "Action.h"
#include "GenerateMap.h"

#define BITMAP_ID 0x4D42

using namespace std;

//struct CAMERA   /*�����������λ*/
/*{
	GLfloat xeye;
	GLfloat yeye;
	GLfloat zeye;
};
struct CAMERA  camera = { 2, 0, 0 };*/

/*struct POLAR
{
	float r;            //����r
	float alpha;     //ˮƽƫ�Ǧ�
	float fy;          //��ֱƫ�Ǧգ���λ���ýǶȣ�
};

struct POLAR  polar = { 40.0f, 90, 90 };*/

#include "gl/glut.h"
#define FloorTexIndex 0


extern mydraw objList;

extern GLint myObjList[10];
extern GLint mapList;
extern GLint wallList;
extern GLint singleLineList;
extern GLint singleColumnList;
extern GLuint Tex[20];
extern int texindex;

#endif // _GLOBAL_H_
