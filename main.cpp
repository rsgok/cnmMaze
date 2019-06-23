#include<iostream>
#include<algorithm>
#include <cstdlib>
#include<cstdio>
#include "gl/glut.h"
#include"Action.h"
#include"MiniMap.h"
#include"GenerateMap.h"
using namespace std;

//����
int MainWindow;//������
int MapWindow_min; //��ͼ����(С
int MapWindow_max; //��ͼ����(��
bool MapFlag = 0; //0:С��ͼ  1:���ͼ

//��Ϊ����
Action act(1.5, 1.5, 0, 0, 1, 5);
//��ͼ
MazeMap mazemap;
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
	case 'v':
		act.player.setViewFlag();
		break;
	case ' ':
		act.jmp();
		break;
	case 27:
		exit(0);
	case 'm':
		MapFlag = ! MapFlag;
		break;
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
void MapKeyAction(unsigned char k, int x, int y)
{
	switch (k)
	{
	case 'm':
		MapFlag = !MapFlag;
		break;

	}
}

////////////////////////////////////////////////////////for test





void reshape(int width, int height)
{
	glViewport(0, 0, width, height);					// Reset The Current Viewport
	glMatrixMode(GL_PROJECTION);						// Select The Projection Matrix
	glLoadIdentity();									// Reset The Projection Matrix
	float whRatio = (GLfloat)width / (GLfloat)height;
	gluPerspective(45.0f, whRatio, 0.1f, 100.0f);
	glMatrixMode(GL_MODELVIEW);
}


void redrawMain(Action act,const MazeMap &Map)
{
	
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glLoadIdentity();									// Reset The Current Modelview Matrix
	

	//�ӽ�����
	if (act.player.CamFlag())
	{
		gluLookAt(act.player.D_x() - act.player.D_vx()/5*2, act.player.D_y() - act.player.D_vy() / 5 * 2, act.player.D_z() - act.player.D_vz() / 5 * 2,	//�ӵ�λ��
			-2*act.player.D_vx(), -2*act.player.D_vy(), -2*act.player.D_vz(),					//����Ϊ����
			0, 1, 0);				// X������
	}
	else
	{
		gluLookAt(act.player.D_vx(), act.player.D_vy(), act.player.D_vz(),	//�ӵ�λ��
			act.player.D_x(), act.player.D_y(), act.player.D_z(),					//����Ϊ����
			0, 1, 0);				// X������
	}

	

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
	glTranslated(act.player.D_x(), act.player.D_y(), act.player.D_z() );//λ��ƽ��
	glRotated(-act.player.face_ang/acos(-1)*180.0, 0, 1, 0);//��ת������
	glutSolidCube(1.0);
	glPopMatrix();

	glutSwapBuffers();

}
////////////////////////////////////////////////////////

void redraw()
{
	//�ƶ����� 
	act.MoveAction();
	glutSetWindow(MainWindow);
	redrawMain(act,mazemap);
//	glutSetWindow(MapWindow_min);
//	MiniMap::redrawMap(act,mazemap);
//	glutSetWindow(MapWindow_max);
//	MiniMap::redrawMap(act, mazemap);
	if (MapFlag == 0)
	{
		glutSetWindow(MapWindow_min);
		glutShowWindow();
		glutSetWindow(MapWindow_max);
		glutHideWindow();
	}
	else
	{
		glutSetWindow(MapWindow_min);
		glutHideWindow();
		glutSetWindow(MapWindow_max);
		glutShowWindow();
	}
	glutSetWindow(MainWindow);
	//		glutSetWindow(MainWindow);
	int aaa = glutGetWindow();
	int bbb = 1;
}
void redrawMap()
{
	MiniMap::redrawMap(act, mazemap);
}
int main(int argc, char *argv[])
{
	//Ĭ�ϳ�ʼ��С
	const int InitWidth = 1280, InitHeight = 960;
	act.window_h = InitHeight;
	act.window_w = InitWidth;
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_RGBA | GLUT_DEPTH | GLUT_DOUBLE);
	glutInitWindowPosition(0, 0);
	glutInitWindowSize(InitWidth,InitHeight);

	//������
	MainWindow = glutCreateWindow("MAZE!");
	//ȫ�� 
	//glutFullScreen();
	//��ͼ
	glutDisplayFunc(redraw);
	glutReshapeFunc(reshape);
	//���
	glutSetCursor(GLUT_CURSOR_NONE);
	glutPassiveMotionFunc(MouseAction);
	glutMotionFunc(MouseAction);
	//����
	glutSetKeyRepeat(GLUT_KEY_REPEAT_OFF);
	glutKeyboardFunc(KeyAction);
	glutKeyboardUpFunc(KeyUpAction);
	glutIdleFunc(idle);

	//��ͼ����

	MapWindow_min = glutCreateSubWindow(MainWindow, InitWidth - min(InitWidth, InitHeight) / 6, InitHeight - min(InitWidth, InitHeight) / 6, 
										min(InitWidth, InitHeight) / 6, min(InitWidth, InitHeight) / 6);
	glutDisplayFunc(redrawMap);
	glutReshapeFunc(reshape);
	//���
	glutSetCursor(GLUT_CURSOR_NONE);
	glutPassiveMotionFunc(MouseAction);
	glutMotionFunc(MouseAction);
	//����
	glutSetKeyRepeat(GLUT_KEY_REPEAT_OFF);
	glutKeyboardFunc(KeyAction);
	glutKeyboardUpFunc(KeyUpAction);
	glutIdleFunc(idle);
	
	MapWindow_max = glutCreateSubWindow(MainWindow, (InitWidth - min(InitWidth, InitHeight))/2.0, (InitHeight - min(InitWidth, InitHeight))/2.0, 
										min(InitWidth, InitHeight), min(InitWidth, InitHeight) );
	
	glutDisplayFunc(redrawMap);
	glutReshapeFunc(reshape);
	//���
	glutSetCursor(GLUT_CURSOR_NONE);
	glutPassiveMotionFunc(MouseAction);
	glutMotionFunc(MouseAction);
	//����
	glutSetKeyRepeat(GLUT_KEY_REPEAT_OFF);
	glutKeyboardFunc(KeyAction);
	glutKeyboardUpFunc(KeyUpAction);
	glutIdleFunc(idle);

	glutSetWindow(MainWindow);
	//glutIdleFunc(idle);
	glutMainLoop();
	return 0;
}

