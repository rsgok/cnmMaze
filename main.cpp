#include<iostream>
#include <stdlib.h>
#include "gl/glut.h"
#include"Action.h"


void idle()
{
	glutPostRedisplay();
}
//���ƶ���
Action act(0,0,0,0,0,5);
void  MouseAction(int x, int y)
{
	act.MouseAction(x, y);
}

void KeyAction(unsigned char k, int x, int y)
{
	act.KeyAction(k, x, y);
}
////////////////////////////////////////////////////////for test

int wHeight = 0;
int wWidth = 0;



void updateView(int width, int height)
{
	glViewport(0, 0, width, height);					// Reset The Current Viewport
	glMatrixMode(GL_PROJECTION);						// Select The Projection Matrix
	glLoadIdentity();									// Reset The Projection Matrix
	float whRatio = (GLfloat)width / (GLfloat)height;
	gluPerspective(45.0f, whRatio, 0.1f, 100.0f);
	glMatrixMode(GL_MODELVIEW);							// Select The Modelview Matrix
}

void reshape(int width, int height)
{
	if (height == 0)										// Prevent A Divide By Zero By
	{
		height = 1;										// Making Height Equal One
	}
	wHeight = height;
	wWidth = width;
	updateView(wHeight, wWidth);
}


float eye[] = { 0, 0, 8 };
float center[] = { 0, 0, 0 };


void redraw()
{

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glLoadIdentity();									// Reset The Current Modelview Matrix

	//�ӽ�����
	gluLookAt(  act.player.pos_vx(),  act.player.pos_vy(),act.player.pos_vz(),	//�ӵ�λ��
		act.player.x,  act.player.y,act.player.z,					//����Ϊ����
		0, 0, 1);				// X������

	//�ƹ�
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_LIGHTING);
	GLfloat white[] = { 1.0, 1.0, 1.0, 1.0 };
	GLfloat light_pos[] = { 5,5,5,1 };
	glLightfv(GL_LIGHT0, GL_POSITION, light_pos);
	glLightfv(GL_LIGHT0, GL_AMBIENT, white);
	glEnable(GL_LIGHT0);

	//�����ķ��飬��Ϊ��׼ 
	glutSolidCube(1.0);

	//��Ϊ��ɫ�ķ���
	glPushMatrix();
	glTranslated(act.player.x, act.player.y, act.player.z );//λ��ƽ��
	glRotated(-act.player.face_ang/acos(-1)*180.0, 0, 0, 1);//��ת������
	glutSolidCube(1.0);
	glPopMatrix();

	glutSwapBuffers();
}


////////////////////////////////////////////////////////

int main(int argc, char *argv[])
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_RGBA | GLUT_DEPTH | GLUT_DOUBLE);
	glutInitWindowSize(480, 480);
	int windowHandle = glutCreateWindow("Simple GLUT App");


	glutDisplayFunc(redraw);
	glutReshapeFunc(reshape);

	glutPassiveMotionFunc(MouseAction);
	glutMotionFunc(&(MouseAction));
	glutKeyboardFunc(KeyAction);
/*	glutEntryFunc(MouseEntry);*/
	glutIdleFunc(idle);

	glutMainLoop();
	return 0;
}
