#pragma once
#include"GenerateMap.h"
#include"GL/glut.h"
namespace MiniMap {
	
	
	void redrawMap(Action act,const MazeMap &mazemap)
	{
		glClear(GL_COLOR_BUFFER_BIT);
		glLoadIdentity();
		//����ɫ
		glClearColor((float)0x66 / 0xff, (float)0xcc / 0xff, (float)0xff / 0xff, 0.1f);
		const int windowSize = 2.5;
		glOrtho(-windowSize, windowSize,-windowSize, windowSize,-1,1);
		gluLookAt(0, 0, 1, 0, 0, 0, 1, 0, 0);

		glPushMatrix();
		glRotated(-act.player.face_ang / acos(-1)*180.0, 0, 0, 1);//��ת������
 		glTranslated(-act.player.x, -act.player.y,0);//λ��ƽ��
		glBegin(GL_QUADS);
		glColor3f(1.0f, 1.0f, 1.0f); 
		for (int i = 0; i < mazemap.sizeX;++i)
			for (int j = 0; j < mazemap.sizeY*mazemap.sizeNum; ++j)
				if (mazemap[i][j] == 0)
				{
					glVertex2f(i+0.0,j+0.0); 
					glVertex2f(i+0.0,j+1.0);
					glVertex2f(i+1.0,j+1.0);
					glVertex2f(i+1.0,j+0.0);
				}
		glEnd();
		glPopMatrix();

		glPushMatrix();
		glColor3f(0.0f, 1.0f, 1.0f); 
		glBegin(GL_TRIANGLES);
		glVertex2f(0,0.2);
		glVertex2f(0, -0.2);
		glVertex2f(0.3, 0);
		glEnd();
		glPopMatrix();
		glBegin(GL_QUADS);
		glColor3f((float)0x66 / 0xff, (float)0xcc / 0xff, (float)0xff / 0xff);
		glVertex3f(-windowSize, windowSize,0);
		glVertex3f(-windowSize, windowSize - 0.3,0);
		glVertex3f(windowSize, windowSize - 0.3,0);
		glVertex3f(windowSize, windowSize,0);

		glVertex2f(-windowSize, -windowSize);
		glVertex2f(-windowSize + 0.3, -windowSize);
		glVertex2f(-windowSize + 0.3, windowSize);
		glVertex2f(-windowSize, windowSize);

		glVertex2f(-windowSize, -windowSize);
		glVertex2f(-windowSize, -windowSize + 0.3);
		glVertex2f(windowSize, -windowSize + 0.3);
		glVertex2f(windowSize, -windowSize);

		glVertex2f(windowSize, -windowSize);
		glVertex2f(windowSize - 0.3, -windowSize);
		glVertex2f(windowSize - 0.3, windowSize);
		glVertex2f(windowSize, windowSize);
		glColor3f(1.0f, 1.0f, 1.0f);
		glVertex2f(-windowSize, windowSize);
		glVertex2f(-windowSize, windowSize-0.1);
		glVertex2f(windowSize, windowSize-0.1);
		glVertex2f(windowSize, windowSize);

		glVertex2f(-windowSize, -windowSize);
		glVertex2f(-windowSize + 0.1, -windowSize);
		glVertex2f(-windowSize + 0.1, windowSize);
		glVertex2f(-windowSize, windowSize);

		glVertex2f(-windowSize, -windowSize);
		glVertex2f(-windowSize, -windowSize + 0.1);
		glVertex2f(windowSize, -windowSize + 0.1);
		glVertex2f(windowSize, -windowSize);

		glVertex2f(windowSize, -windowSize);
		glVertex2f(windowSize - 0.1, -windowSize);
		glVertex2f(windowSize - 0.1, windowSize);
		glVertex2f(windowSize, windowSize);

		

		glEnd();
		
		glutSwapBuffers();
	}

};