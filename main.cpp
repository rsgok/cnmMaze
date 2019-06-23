#include<iostream>
#include<algorithm>
#include <cstdlib>
#include<cstdio>
#include "gl/glut.h"
#include"Action.h"
#include"MiniMap.h"
#include"GenerateMap.h"
using namespace std;

//窗口
int MainWindow;//主窗口
int MapWindow; //地图窗口
//行为控制
Action act(1.5, 1.5, 0, 0, 1, 5);
//地图
MazeMap mazemap;
//回调函数
void idle()
{
	glutPostRedisplay();
}

void  MouseAction(int x, int y)
{
	glutSetWindow(MainWindow);
	act.ViewAction(x, y);
}
void WindowChange(int &WindowID, const Action &act, int topWindow);
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
		WindowChange(MapWindow,act,MainWindow);
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
		WindowChange(MapWindow, act, MainWindow);
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


void redrawMain(Action act,const MazeMap &Map)
{
	
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glLoadIdentity();									// Reset The Current Modelview Matrix
	

	//视角设置
	if (act.player.CamFlag())
	{
		gluLookAt(act.player.D_x() - act.player.D_vx()/5*2, act.player.D_y() - act.player.D_vy() / 5 * 2, act.player.D_z() - act.player.D_vz() / 5 * 2,	//视点位置
			-2*act.player.D_vx(), -2*act.player.D_vy(), -2*act.player.D_vz(),					//中心为人物
			0, 1, 0);				// X轴向上
	}
	else
	{
		gluLookAt(act.player.D_vx(), act.player.D_vy(), act.player.D_vz(),	//视点位置
			act.player.D_x(), act.player.D_y(), act.player.D_z(),					//中心为人物
			0, 1, 0);				// X轴向上
	}

	

	//灯光
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_LIGHTING);
	GLfloat white[] = { 1.0, 1.0, 1.0, 1.0 };
	GLfloat light_pos[] = { 5,5,5,1 };
	glLightfv(GL_LIGHT0, GL_POSITION, light_pos);
	glLightfv(GL_LIGHT0, GL_AMBIENT, white);
	glEnable(GL_LIGHT0);

	//不动的方块，作为基准 
	glPushMatrix();
	glScalef(1.0, 1.0, 2.0);
	glutSolidCube(1.0);
	glPopMatrix();

	//作为角色的方块
	glPushMatrix();
	glTranslated(act.player.D_x(), act.player.D_y(), act.player.D_z() );//位置平移
	glRotated(-act.player.face_ang/acos(-1)*180.0, 0, 1, 0);//旋转面向方向
	glutSolidCube(1.0);
	glPopMatrix();

	glutSwapBuffers();

}
////////////////////////////////////////////////////////

void redraw()
{
	//移动处理 
	act.MoveAction();
	glutSetWindow(MainWindow);
	redrawMain(act,mazemap);
	//glutSetWindow(MapWindow);
	//MiniMap::redrawMap(act,mazemap);
}
void WindowChange(int &WindowID, const Action &act, int topWindow)
{
	static bool flag = 0;
	flag = !flag;
	glutDestroyWindow(WindowID);
	if (flag)
	{
		int windowSize = std::min(act.window_h, act.window_w)*0.9;
		WindowID = glutCreateSubWindow(topWindow, (act.window_w - windowSize) >> 1, (act.window_h - windowSize) >> 1, windowSize, windowSize);
	}
	else
	{
		int windowSize = std::min(act.window_h, act.window_w) / 6;
		WindowID = glutCreateSubWindow(topWindow, act.window_w - windowSize, act.window_h - windowSize, windowSize, windowSize);
	}
	glutSetWindow(MapWindow);
	glutSetCursor(GLUT_CURSOR_NONE);
	glutDisplayFunc(redraw);
	glutKeyboardFunc(MapKeyAction);
	glutIdleFunc(idle);
}
int main(int argc, char *argv[])
{
	//默认初始大小
	const int InitWidth = 1280, InitHeight = 960;
	act.window_h = InitHeight;
	act.window_w = InitWidth;
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_RGBA | GLUT_DEPTH | GLUT_DOUBLE);
	glutInitWindowPosition(0, 0);
	glutInitWindowSize(InitWidth,InitHeight);
	MainWindow = glutCreateWindow("Simple GLUT App");
	MapWindow = glutCreateSubWindow(MainWindow, InitWidth - min(InitWidth, InitHeight) / 6, InitHeight - min(InitWidth, InitHeight) / 6, min(InitWidth, InitHeight) / 6, min(InitWidth, InitHeight) / 6);

	glutSetWindow(MainWindow);
	//绘图
	glutDisplayFunc(redraw);
	glutReshapeFunc(reshape);

	//鼠标
	glutSetCursor(GLUT_CURSOR_NONE);
	glutPassiveMotionFunc(MouseAction);
	glutMotionFunc(MouseAction);
	//键盘
	glutSetKeyRepeat(GLUT_KEY_REPEAT_OFF);	
	glutKeyboardFunc(KeyAction);
	glutKeyboardUpFunc(KeyUpAction);
	glutIdleFunc(idle);

	glutSetWindow(MapWindow);
	glutSetCursor(GLUT_CURSOR_NONE);
	glutDisplayFunc(redraw);
	glutKeyboardFunc(MapKeyAction);
	glutIdleFunc(idle);
/*
	//绘图
	glutReshapeFunc(reshape);
	//鼠标
	//键盘
	glutSetKeyRepeat(GLUT_KEY_REPEAT_OFF);
	*/

	glutMainLoop();
	return 0;
}

