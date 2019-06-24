#ifndef _WALL_H_
#define _WALL_H_

#include <string.h>
#include <gl/glut.h>
#include "texture.h"

class Wall {
private:
	GLint type = 1;//���������ǽ
	GLfloat posX = 0;
	GLfloat posZ = 0;
	GLfloat length = 1;
	GLfloat thickness = 0.1;
	GLfloat height = 2;
	GLuint * wallTex = (GLuint*)malloc(sizeof(GLuint));
public:
	~Wall() {}

	Wall(GLfloat posx = 0, GLfloat posz = 0, GLfloat Type = 1) {
		type = Type;
		posX = posx;
		posZ = posz;
	}

	void DrawWall() {
		texload(wallTex, (char*)"images/wall.bmp");
		glPushMatrix();
		glTranslatef(posX, 0, posZ);
		if (type != 1)
			glRotatef(90, 0, 1, 0);
		glEnable(GL_TEXTURE_2D);
		glBindTexture(GL_TEXTURE_2D, *wallTex);

		glBegin(GL_QUADS);
		glTexCoord2i(1, 1); glVertex3f(thickness, height, length);
		glTexCoord2i(0, 1); glVertex3f(thickness, -height, length);
		glTexCoord2i(0, 0); glVertex3f(thickness, -height, -length);
		glTexCoord2i(1, 0); glVertex3f(thickness, height, -length);
		glEnd();

		glBegin(GL_QUADS);
		glTexCoord2i(1, 1); glVertex3f(-thickness, height, length);
		glTexCoord2i(0, 1); glVertex3f(-thickness, -height, length);
		glTexCoord2i(0, 0); glVertex3f(-thickness, -height, -length);
		glTexCoord2i(1, 0); glVertex3f(-thickness, height, -length);
		glEnd();

		glBegin(GL_QUADS);
		glTexCoord2i(1, 1); glVertex3f(thickness, height, length);
		glTexCoord2i(0, 1); glVertex3f(-thickness, height, length);
		glTexCoord2i(0, 0); glVertex3f(-thickness, height, -length);
		glTexCoord2i(1, 0); glVertex3f(thickness, height, -length);
		glEnd();

		glBegin(GL_QUADS);
		glTexCoord2i(1, 1); glVertex3f(thickness, -height, length);
		glTexCoord2i(0, 1); glVertex3f(-thickness, -height, length);
		glTexCoord2i(0, 0); glVertex3f(-thickness, -height, -length);
		glTexCoord2i(1, 0); glVertex3f(thickness, -height, -length);
		glEnd();

		glBegin(GL_QUADS);
		glTexCoord2i(1, 1); glVertex3f(thickness, height, -length);
		glTexCoord2i(0, 1); glVertex3f(-thickness, height, -length);
		glTexCoord2i(0, 0);	glVertex3f(-thickness, -height, -length);
		glTexCoord2i(1, 0);	glVertex3f(thickness, -height, -length);
		glEnd();

		glBegin(GL_QUADS);
		glTexCoord2i(1, 1); glVertex3f(thickness, height, length);
		glTexCoord2i(0, 1);	glVertex3f(-thickness, height, length);
		glTexCoord2i(0, 0);	glVertex3f(-thickness, -height, length);
		glTexCoord2i(1, 0);	glVertex3f(thickness, -height, length);
		glEnd();

		glPopMatrix();
		glDisable(GL_TEXTURE_2D);
	}
};

#endif