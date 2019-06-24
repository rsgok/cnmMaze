#include<iostream>
#include<algorithm>
#include <cstdlib>
#include<cstdio>
#include "gl/glut.h"
#include"Action.h"
#include"MiniMap.h"
#include"GenerateMap.h"
#include "global.h"
#include "wall.h"
#include "initgame.h"
#include "draw.h"
#include "screenShot.h"
using namespace std;

//����
int MainWindow;//������
int MapWindow_min; //��ͼ����(С
int MapWindow_max; //��ͼ����(��
bool MapFlag = 0; //0:С��ͼ  1:���ͼ

int basicSceneList;

//��Ϊ����
Action act(1.5, 1.5, 0, 0, 1,1);
//��ͼ
MazeMap mazemap;
draw objDraw;
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
		if(act.player.CamFlag()) act.player.vr =8;
		else act.player.vr = 1;
		break;
	case ' ':
		act.jmp();
		break;
	case 27:
		exit(0);
		break;
	case 'c':
		SnapScreen(1200,800);
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
void MouseClick(int button, int state, int x, int y)
{
	const float Delt_vr = 0.1;
	switch (button)
	{
	case 3:
		act.player.vr -= Delt_vr;
		break;
	case 4:
		act.player.vr += Delt_vr;
		break;
	}
}


////////////////////////////////////////////////////////for test



void DrawObjs(int i) {
	glPushMatrix();
	glScalef(0.042, 0.042, 0.042);
	//glRotatef(0, 0, 90,0);
	objDraw.drawElement(i);
	glPopMatrix();
}

void DrawMap() {
	int x = mazemap.sizeX, y = mazemap.sizeY*mazemap.sizeNum;
	for (int i = 0; i < x; ++i) {
		for (int j = 0; j < y; ++j) {
			glBegin(GL_LINES);
			glVertex3f(j, 0, i);
			glVertex3f(j, 0, i + 1);
			glVertex3f(j, 0, i);
			glVertex3f(j + 1, 0, i);
			glVertex3f(j + 1, 0, i + 1);
			glVertex3f(j + 1, 0, i);
			glVertex3f(j + 1, 0, i + 1);
			glVertex3f(j, 0, i + 1);
			glEnd();
			int n = mazemap[i][j];
			if (n >= 0&&act.InView(i,j)) 
			{
				glPushMatrix();
				glTranslatef(j + 0.5, 0, i + 0.5);
				DrawObjs(n);
				glPopMatrix();
			}
		
		}
	}
}



void reshape(int width, int height)
{
	glViewport(0, 0, width, height);					// Reset The Current Viewport
	glMatrixMode(GL_PROJECTION);						// Select The Projection Matrix
	glLoadIdentity();									// Reset The Projection Matrix
	float whRatio = (GLfloat)width / (GLfloat)height;
	gluPerspective(45.0f, whRatio, 0.1f, 100.0f);
	glMatrixMode(GL_MODELVIEW);
}

void redrawMain(Action act, const MazeMap &Map)
{

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glLoadIdentity();									// Reset The Current Modelview Matrix


	//�ӽ�����
	const float Delt_y =0.3;
	if (act.player.CamFlag())
	{
		
		gluLookAt(act.player.D_x() , act.player.D_y() +0.4, act.player.D_z(),	//�ӵ�λ��
			 -act.player.D_vx() + 2 * act.player.D_x() + 0.4,  -act.player.D_vy() + 2 * act.player.D_y(),  -act.player.D_vz() + 2 * act.player.D_z(),					//����Ϊ����
			0, 1, 0);				// X������
	}
	else
	{
		
		gluLookAt(act.player.D_vx(), Delt_y + act.player.D_vy(), act.player.D_vz(),	//�ӵ�λ��
			act.player.D_x(), Delt_y + act.player.D_y(), act.player.D_z(),					//����Ϊ����
			0, 1, 0);				// X������
	}



	//�ƹ�
	
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_LIGHTING);
	GLfloat white[] = { 0.1, 0.1, 0.1, 1.0 };
	GLfloat light_pos[] = { 5,5,5,-1 };
	glLightfv(GL_LIGHT0, GL_POSITION, light_pos);
	glLightfv(GL_LIGHT0, GL_AMBIENT, white);
	glEnable(GL_LIGHT0);
	//��������
	glCallList(basicSceneList);
	if (act.player.CamFlag() == 0)
	{
		glPushMatrix();
		glTranslated(act.player.D_x(), act.player.D_y(), act.player.D_z());//λ��ƽ��
		glRotated(act.player.face_ang / acos(-1)*180.0 - 45.0, 0, 1, 0);//��ת������
		glScaled(0.6, 0.6, 0.6);
		DrawObjs(100);
		glPopMatrix();
	}
	


	DrawMap();

	glutSwapBuffers();

}
////////////////////////////////////////////////////////

void redraw()
{
	//�ƶ����� 
	act.MoveAction(mazemap);
	glutSetWindow(MainWindow);
	redrawMain(act,mazemap);
	glutSetWindow(MapWindow_min);
	MiniMap::redrawMap(act,mazemap);
	glutSetWindow(MainWindow);
}

int main(int argc, char *argv[])
{
	//Ĭ�ϳ�ʼ��С
	const int InitWidth = 1200, InitHeight =800;
	act.window_h = InitHeight;
	act.window_w = InitWidth;
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_RGBA | GLUT_DEPTH | GLUT_DOUBLE);
	glutInitWindowPosition(0, 0);
	glutInitWindowSize(InitWidth,InitHeight);

	//������
	MainWindow = glutCreateWindow("MAZE!");
	//��ͼ
	glutDisplayFunc(redraw);
	glutReshapeFunc(reshape);
	initGame game;
	game.loadGame();
	for (int i = 0; i<=10; i++)
	{
		objDraw.loadElement(i);
	}
	objDraw.loadElement(100);

	basicSceneList = game.drawScene();

	//���
	glutSetCursor(GLUT_CURSOR_NONE);
	glutPassiveMotionFunc(MouseAction);
	glutMotionFunc(MouseAction);
	glutMouseFunc(MouseClick);
	//����
	glutSetKeyRepeat(GLUT_KEY_REPEAT_OFF);
	glutKeyboardFunc(KeyAction);
	glutKeyboardUpFunc(KeyUpAction);
	glutIdleFunc(idle);

	//��ͼ����

	MapWindow_min = glutCreateSubWindow(MainWindow, InitWidth - min(InitWidth, InitHeight) / 6, InitHeight - min(InitWidth, InitHeight) / 6, 
										min(InitWidth, InitHeight) / 6, min(InitWidth, InitHeight) / 6);

	glutMainLoop();
	return 0;
}

