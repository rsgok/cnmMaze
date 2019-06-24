#pragma once
#include "objLoader.h"

#define ElementNum 15

class mydraw
{
public:
	vector<pair<objLoader*,int>> obj;
	mydraw();
	~mydraw();
	void loadElement(int num);
	void drawElement(int num);
};