#pragma once
#include "objLoader.h"

#define ElementNum 10

class mydraw
{
public:
	vector<objLoader*> obj;
	mydraw();
	~mydraw();
	void loadElement(int num);
	void drawElement(int num);
};