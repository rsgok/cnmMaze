#include "initgame.h"

void initGame::loadGame()
{
	glGenTextures(20, Tex);
	GLuint* tmp = Tex;
	texload(tmp, (char*)"images/1.bmp");
	texload(++tmp, (char*)"images/2.bmp");
	texload(++tmp, (char*)"images/4.bmp");
	texload(++tmp, (char*)"images/5.bmp");
	texload(++tmp, (char*)"images/8.bmp");
	texload(++tmp, (char*)"images/9.bmp");
	texload(++tmp, (char*)"images/sky.bmp");
	texload(++tmp, (char*)"images/sky2.bmp");
	texload(++tmp, (char*)"images/walltext.bmp");
	texload(++tmp, (char*)"images/micai1.bmp");
	texload(++tmp, (char*)"images/micai2.bmp");
	texload(++tmp, (char*)"images/metal1.bmp");
	texload(++tmp, (char*)"images/metal2.bmp");
	texload(++tmp, (char*)"images/blue.bmp");
	texload(++tmp, (char*)"images/win.bmp");
	texload(++tmp, (char*)"images/tip.bmp");
	texload(++tmp, (char*)"images/wall2.bmp");
}
GLint initGame::drawScene()
{
	GLint lid = glGenLists(1);
	glNewList(lid, GL_COMPILE);

	drawFloor();
	drawSky();
	drawWall();

	glEndList();

	return lid;
}
void initGame::drawFloor() {
	glPushMatrix();
	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, Tex[FloorTexIndex]);
	glTranslatef(0, -1.0, 0);

	glBegin(GL_QUADS);
	glTexCoord2i(90, 20); glVertex3f(-90, 0, 20);
	glTexCoord2i(90, 0); glVertex3f(-90, 0, -20);
	glTexCoord2i(0, 0); glVertex3f(90, 0, -20);
	glTexCoord2i(0, 20); glVertex3f(90, 0, 20);
	glEnd();

	glDisable(GL_TEXTURE_2D);
	glPopMatrix();
}
void initGame::drawWall() {
	glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_DECAL);
	float skyHei = 30;                      //天空的高度
	float skyLen = 90;                   //天空的长度
	float skyWid = 20;
	//后
	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, Tex[16]);
	glBegin(GL_TRIANGLE_FAN);
	glTexCoord2f(1, 0);
	glVertex3f(skyLen, -skyHei, skyWid);
	glTexCoord2f(1, 1);
	glVertex3f(skyLen, +skyHei, skyWid);
	glTexCoord2f(0, 1);
	glVertex3f(-skyLen, +skyHei, skyWid);
	glTexCoord2f(0, 0);
	glVertex3f(-skyLen, -skyHei, skyWid);
	glEnd();
	//前
	glBindTexture(GL_TEXTURE_2D, Tex[16]);
	glBegin(GL_TRIANGLE_FAN);
	glTexCoord2f(1, 0);
	glVertex3f(-skyLen, -skyHei, -skyWid);
	glTexCoord2f(1, 1);
	glVertex3f(-skyLen, skyHei, -skyWid);
	glTexCoord2f(0, 1);
	glVertex3f(skyLen, skyHei, -skyWid);
	glTexCoord2f(0, 0);
	glVertex3f(skyLen, -skyHei, -skyWid);
	glEnd();
	//右面
	glBindTexture(GL_TEXTURE_2D, Tex[16]);
	glBegin(GL_TRIANGLE_FAN);
	glTexCoord2f(1, 0);
	glVertex3f(skyLen, -skyHei, -skyWid);
	glTexCoord2f(1, 1);
	glVertex3f(skyLen, skyHei, -skyWid);
	glTexCoord2f(0, 1);
	glVertex3f(skyLen, skyHei, skyWid);
	glTexCoord2f(0, 0);
	glVertex3f(skyLen, -skyHei, skyWid);
	glEnd();
	//左面
	glBindTexture(GL_TEXTURE_2D, Tex[16]);
	glBegin(GL_TRIANGLE_FAN);
	glTexCoord2f(1, 0);
	glVertex3f(-skyLen, -skyHei, skyWid);
	glTexCoord2f(1, 1);
	glVertex3f(-skyLen, +skyHei, skyWid);
	glTexCoord2f(0, 1);
	glVertex3f(-skyLen, +skyHei, -skyWid);
	glTexCoord2f(0, 0);
	glVertex3f(-skyLen, -skyHei, -skyWid);
	glEnd();
	glDisable(GL_TEXTURE_2D);
}
void initGame::drawSky() {
	glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_DECAL);
	float skyHei = 30;                      //天空的高度
	float skyLen = 90;                   //天空的长度
	float skyWid = 20;

	glEnable(GL_TEXTURE_2D);
	//顶面
	glBindTexture(GL_TEXTURE_2D, Tex[6]);
	glBegin(GL_TRIANGLE_FAN);
	glTexCoord2f(0, 1);
	glVertex3f(-skyLen, skyHei, -skyWid);
	glTexCoord2f(0, 0);
	glVertex3f(-skyLen, skyHei, skyWid);
	glTexCoord2f(1, 0);
	glVertex3f(skyLen, skyHei, skyWid);
	glTexCoord2f(1, 1);
	glVertex3f(skyLen, skyHei, -skyWid);
	glEnd();
	glDisable(GL_TEXTURE_2D);
}