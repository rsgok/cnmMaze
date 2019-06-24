#pragma once

#ifndef _INITGAME_H_
#define _INITGAME_H_


#include "global.h"
#include "texture.h"
class initGame
{
public:
	void loadGame();
	GLint drawScene();
	void drawFloor();
	void drawWall();
	void drawSky();
};

#endif
