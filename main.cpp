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
using namespace std;

//����
int MainWindow;//������
int MapWindow_min; //��ͼ����(С
int MapWindow_max; //��ͼ����(��
bool MapFlag = 0; //0:С��ͼ  1:���ͼ

int basicSceneList;

//��Ϊ����
Action act(1.5, 1.5, 0, 0, 1, 1);
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



void DrawObjs(int i) {
	glPushMatrix();
	glScalef(0.1, 0.1, 0.1);
	glRotatef(0, 0, 90,0);
	glCallList(myObjList[i]);
	glPopMatrix();
}

void DrawMap() {
	int x = mazemap.sizeX, y = mazemap.sizeY*mazemap.sizeNum;
	mydraw Draw;
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
		/*	if (n >= 0) 
			{
				glPushMatrix();
				glTranslatef(j + 0.5, 0, i + 0.5);
				objList.drawElement(n);
				glPopMatrix();
			}*/
		
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
	if (act.player.CamFlag())
	{
		gluLookAt(act.player.D_x() - act.player.D_vx() / 5 * 2, act.player.D_y() - act.player.D_vy() / 5 * 2, act.player.D_z() - act.player.D_vz() / 5 * 2,	//�ӵ�λ��
			-2 * act.player.D_vx(), -2 * act.player.D_vy(), -2 * act.player.D_vz(),					//����Ϊ����
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
	//��������
	glCallList(basicSceneList);

/*	//�����ķ��飬��Ϊ��׼ 
	for (int i = 0; i < mazemap.sizeX; ++i)
		for (int j = 0; j < mazemap.sizeY*mazemap.sizeNum; ++j)
			if (mazemap[i][j]>=0)
			{
				int MMM = mazemap[i][j] + 1;
				glPushMatrix();
				glTranslated(j+0.5,0,i+0.5);
				glScaled(objSize[MMM][0]*2,objSize[MMM][1],objSize[MMM][0]*2);
				glutSolidCube(1.0);
				glPopMatrix();
			}
			else
			{
				glPushMatrix();
				glTranslated(j + 0.5, 2, i + 0.5);
				glScaled(1,4,1);
				glutSolidCube(1.0);
				glPopMatrix();
			}*/

	//��Ϊ��ɫ�ķ���
	glPushMatrix();
	glTranslated(act.player.D_x(), act.player.D_y(), act.player.D_z() );//λ��ƽ��
	glRotated(act.player.face_ang/acos(-1)*180.0, 0, 1, 0);//��ת������
	glScaled(0.6,0.6,0.6);
	glutSolidCube(1.0);
	glPopMatrix();


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
		objList.loadElement(i);
	}

	basicSceneList = game.drawScene();

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

	glutMainLoop();
	return 0;
}

