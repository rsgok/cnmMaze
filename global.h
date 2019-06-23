#pragma once
#include <stdio.h>
#include <stdlib.h>
#include <gl/glut.h>
#include <math.h>
#include <Windows.h>
#include <ctime>
#include <vector>
#include "mydraw.h"

#define BITMAP_ID 0x4D42

using namespace std;

struct CAMERA   /*用于摄像机定位*/
{
	GLfloat xeye;
	GLfloat yeye;
	GLfloat zeye;
};
struct CAMERA  camera = { 2, 0, 0 };

struct POLAR
{
	float r;            //距离r
	float alpha;     //水平偏角α
	float fy;          //竖直偏角φ（单位均用角度）
};

struct POLAR  polar = { 40.0f, 90, 90 };

GLint centerPoint[] = { 0, 0 };
GLint previousPoint[] = { 0, 0 };

GLfloat initPos[] = { 0, 0, 0 };
GLfloat initScale[] = { 0.3, 0.3, 0.3 };

GLsizei initialSize[] = { 1200, 600 };

float fTranslate;
float fRotate;
GLfloat m_PosX = 15;
GLfloat m_PosY = 10;
GLfloat m_PosZ = 15;
GLsizei currentSize[2] = { 0, 0 };
bool bshow = false;
bool lightOn = false;

GLint lightS = 0;

//GLint bList = 0;

GLint wallList = 0;
GLint singleLineList = 0;
GLint singleColumnList = 0;

GLuint Tex[20];
int texindex = 0;

mydraw objList;