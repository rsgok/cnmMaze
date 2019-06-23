#pragma once
#include "mydraw.h"

mydraw::mydraw()
{
	obj.clear();
	for (int i = 0; i < ElementNum; i++)
	{
		objLoader* newObjLoader = new objLoader();
		obj.push_back(make_pair(newObjLoader,0));
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
	case -1:
		filename = "wall.obj";
		break;
	case 100:
		filename = "man.obj";
		break;
	case 0:
		filename = "road.obj";
		break;
	case 1:
		filename = "cat.obj";
		break;
	case 2:
		filename = "deer.obj";
		break;
	case 3:
		filename = "house.obj";
		break;
	case 4:
		filename = "12281_Container_v2_L2.obj";
		break;
	case 5:
		filename = "Rock1.obj";
		break;
	case 6:
		filename = "rose.obj";
		break;
	case 7:
		filename = "tree1.obj";
		break;
	case 8:
		filename = "tree2.obj";
		break;
	case 9:
		filename = "well_OBJ.obj";
		break;
	case 10:
		filename = "wood.obj";
		break;
	}
	// load file
	objLoader* curObjLoader = obj[num].first;
	curObjLoader->load("assets/"+filename);

	GLint lid = glGenLists(1);
	glNewList(lid, GL_COMPILE);
	glPushMatrix();
	glScalef(0.05, 0.05, 0.05);
	curObjLoader->draw();
	glPopMatrix();
	glEndList();

	obj[num].second = lid;
}

void mydraw::drawElement(int num)
{
	glCallList(obj[num].second);
}

