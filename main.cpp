#include<iostream>
#include <stdlib.h>
#include "gl/glut.h"
#include"Action.h"


//����
int MainWindow;//������
int MapWindow; //��ͼ����
//��Ϊ����
Action act(1, 1, 0, 1, 1, 5);
//�ص�����
void idle()
{
	glutPostRedisplay();
}

void  MouseAction(int x, int y)
{
	glutSetWindow(MainWindow);
	act.ViewAction(x, y);
}

void KeyAction(unsigned char k, int x, int y)
{
	switch (k)
	{
	case 'w':
		act.setMoveDir(Direction::W,1);
		break;
	case 's':
		act.setMoveDir(Direction::S, 1);
		break;
	case 'a':
		act.setMoveDir(Direction::A, 1);
		break;
	case 'd':
		act.setMoveDir(Direction::D, 1);
		break;
	case ' ':
		act.jmp();
		break;
	case 27:
		exit(0);
/*	case 'm':
		MapChange();
		break;*/
	}
}
void KeyUpAction(unsigned char k, int x, int y)
{
	switch (k)
	{
	case 'w':
		act.setMoveDir(Direction::W, 0);
		break;
	case 's':
		act.setMoveDir(Direction::S, 0);
		break;
	case 'a':
		act.setMoveDir(Direction::A, 0);
		break;
	case 'd':
		act.setMoveDir(Direction::D, 0);
		break;

	}
}

////////////////////////////////////////////////////////for test



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
	act.window_h = height;
	act.window_w = width;
	updateView(act.window_h, act.window_w);
}


void redraw()
{
	glutSetWindow(MainWindow);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glLoadIdentity();									// Reset The Current Modelview Matrix
	//�ƶ����� 
	act.MoveAction();

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
	glPushMatrix();
	glScalef(1.0, 1.0, 2.0);
	glutSolidCube(1.0);
	glPopMatrix();

	//��Ϊ��ɫ�ķ���
	glPushMatrix();
	glTranslated(act.player.x, act.player.y, act.player.z );//λ��ƽ��
	glRotated(-act.player.face_ang/acos(-1)*180.0, 0, 0, 1);//��ת������
	glutSolidCube(1.0);
	glPopMatrix();

	glutSwapBuffers();
	

}

void redrawmap()
{
	glutSetWindow(MapWindow);
	glClearColor((float)0x66/0xff, (float)0xcc/0xff, (float)0xff/0xff,0.1f); //��������ɫ����Ϊ��ɫ�Ͳ�͸�� 
	glClear(GL_COLOR_BUFFER_BIT);         //�����ɫ��������������

	//������ԭ�� 
	glBegin(GL_QUADS);//Ϊ���ĵĺ�ɫ1x1������;              //ÿ��4���������һ����Ԫ�� 
	glColor3f(1.0f,0.0f,0.0f); //��ɫ 
	glVertex2f(-0.5f, -0.5f);    // x��y
	glVertex2f(0.5f, - 0.5f);
	glVertex2f(0.5f,0.5f);
	glVertex2f(-0.5f, 0.5f);
	glEnd();

	glFlush();  //������Ⱦ
}

////////////////////////////////////////////////////////

int main(int argc, char *argv[])
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_RGBA | GLUT_DEPTH | GLUT_DOUBLE);
	glutInitWindowPosition(0, 0);
	glutInitWindowSize(1280,960);
	MainWindow = glutCreateWindow("Simple GLUT App");
	
	//��ͼ
	glutDisplayFunc(redraw);
	glutReshapeFunc(reshape);

	//���
	glutPassiveMotionFunc(MouseAction);
	glutMotionFunc(&(MouseAction));
	//����
	glutSetKeyRepeat(GLUT_KEY_REPEAT_OFF);	
	glutKeyboardFunc(KeyAction);
	glutKeyboardUpFunc(KeyUpAction);
	glutIdleFunc(idle);

	glutInitDisplayMode(GLUT_RGBA | GLUT_DEPTH);
	MapWindow = glutCreateSubWindow(MainWindow, 0,0, 200, 200);
	glutDisplayFunc(redrawmap);


	glutIdleFunc(idle);
	glutMainLoop();
	return 0;
}

