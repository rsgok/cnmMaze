#pragma once

#include "tinyobjloader.h"
#include <GL/glut.h>
#include <utility>
#include <iostream>
using namespace std;
class draw
{
public:
	vector<pair<int, int>> objlist;
	draw();
	void loadElement(int num);
	void drawElement(int num);
};