#pragma once
#include "mydraw.h"

mydraw::mydraw()
{
	obj.clear();
	for (int i = 0; i < ElementNum; i++)
	{
		objLoader* newObjLoader = new objLoader();
		obj.push_back(newObjLoader);
	}
}

mydraw::~mydraw()
{
	obj.clear();
}

void mydraw::loadElement(int num)
{
	string filename;
	switch (num)
	{
	case 0:
		filename = "road.obj";
		break;
	case 1:
		filename = "cat.obj";
		break;
	case 2:
		filename = "door.obj";
		break;
	case 3:
		filename = "deer.obj";
		break;
	case 4:
		filename = "palmtree.obj";
		break;
	case 5:
		filename = "rose.obj";
		break;
	case 6:
		filename = "pinetree.obj";
		break;
	case 7:
		filename = "oaktree.obj";
		break;
	case 8:
		filename = "followball.obj";
		break;
	case 9:
		filename = "rock1.obj";
	}
	// load file
	objLoader* curObjLoader = obj[num];
	curObjLoader->load(filename);
}

void mydraw::drawElement(int num)
{
	objLoader* curObjLoader = obj[num];
	curObjLoader->draw();
}

