#include<iostream>
#include <stdlib.h>
#include "gl/glut.h"
#include"Action.h"


//窗口
int MainWindow;//主窗口
int MapWindow; //地图窗口
//行为控制
Action act(1, 1, 0, 1, 1, 5);
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
	//移动处理 
	act.MoveAction();

	//视角设置
	gluLookAt(  act.player.pos_vx(),  act.player.pos_vy(),act.player.pos_vz(),	//视点位置
		act.player.x,  act.player.y,act.player.z,					//中心为人物
		0, 0, 1);				// X轴向上

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
	glTranslated(act.player.x, act.player.y, act.player.z );//位置平移
	glRotated(-act.player.face_ang/acos(-1)*180.0, 0, 0, 1);//旋转面向方向
	glutSolidCube(1.0);
	glPopMatrix();

	glutSwapBuffers();
	

}

void redrawmap()
{
	glutSetWindow(MapWindow);
	glClearColor((float)0x66/0xff, (float)0xcc/0xff, (float)0xff/0xff,0.1f); //将背景颜色设置为黑色和不透明 
	glClear(GL_COLOR_BUFFER_BIT);         //清除颜色缓冲区（背景）

	//绘制以原点 
	glBegin(GL_QUADS);//为中心的红色1x1正方形;              //每组4个顶点组成一个四元组 
	glColor3f(1.0f,0.0f,0.0f); //红色 
	glVertex2f(-0.5f, -0.5f);    // x，y
	glVertex2f(0.5f, - 0.5f);
	glVertex2f(0.5f,0.5f);
	glVertex2f(-0.5f, 0.5f);
	glEnd();

	glFlush();  //现在渲染
}

////////////////////////////////////////////////////////

int main(int argc, char *argv[])
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_RGBA | GLUT_DEPTH | GLUT_DOUBLE);
	glutInitWindowPosition(0, 0);
	glutInitWindowSize(1280,960);
	MainWindow = glutCreateWindow("Simple GLUT App");
	
	//绘图
	glutDisplayFunc(redraw);
	glutReshapeFunc(reshape);

	//鼠标
	glutPassiveMotionFunc(MouseAction);
	glutMotionFunc(&(MouseAction));
	//键盘
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

