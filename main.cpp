//参考的框架
#include "global.h"
#include "wall.h"
#include "screenShot.h"

void DrawWalls();
void DrawObjs();
void DrawScene();
void Reshape(int width, int height);
void Redraw();
void Idle();
void Delay(int time);
void SetCamera(GLfloat x, GLfloat y);
void EnterWindow(int state);
void Init();

#define DEG_TO_RAD 0.017453
#define PI 3.141592654

#define TOPDOWN_CAM 0//第三人称
#define FOCUSED_CAM 1//第一人称

int cameraType = FOCUSED_CAM;
//GLfloat camaraZ = ...;

GLint SingleWall(GLfloat x, GLfloat z, GLint type)
{
	Wall p1(0, 0, 1);
	Wall p2(0, 0, 2);
	if (type == 1)//墙有两个方向
	{
		GLint lid = glGenLists(1);
		glNewList(lid, GL_COMPILE);

		glTranslatef(0, 0, -1);
		p1.DrawWall();
		glTranslatef(0, 0, 2);
		p1.DrawWall();
		glTranslatef(0, 0, -1);

		glEndList();
		return lid;
	}
	else {
		GLint lid = glGenLists(1);
		glNewList(lid, GL_COMPILE);
		//glRotatef(90 * type, 0, 1, 0);

		glTranslatef(-1, 0, 0);
		p2.DrawWall();
		glTranslatef(2, 0, 0);
		p2.DrawWall();
		glTranslatef(-1, 0, 0);

		glEndList();
		return lid;
	}
}

GLint WallList()
{
	GLint lid = glGenLists(10);
	glNewList(lid, GL_COMPILE);
	Wall p(0, 0, 1);
	glPushMatrix();
	glTranslatef(0, 0, -15);
	for (int i = 1; i <= 16; i++)//test
	{
		p.DrawWall();
		glTranslatef(0, 0, 2);
	}
	glPopMatrix();

	glEndList();
	return lid;
}

/*void DrawBarrier()
{
	glPushMatrix();
	glTranslatef(0, 0.5, 0);

	glPushMatrix();
	glTranslatef(-10, 0, 12);
	glCallList(singleLineList);
	glTranslatef(4, 0, 0);
	glCallList(singleLineList);
	glTranslatef(4, 0, 0);
	glCallList(singleLineList);
	glTranslatef(4, 0, 0);
	glCallList(singleLineList);
	glTranslatef(4, 0, 0);
	glCallList(singleLineList);
	glTranslatef(4, 0, 0);
	glCallList(singleLineList);
	glPopMatrix();
	//......

}*///对于迷宫内部的墙进行设置

/*void DrawWalls()
{

	glPushMatrix();
	glTranslatef(0, 0.5, 0);
	glTranslatef(-16, 0, 0);
	glCallList(wallList);
	glTranslatef(32, 0, 0);
	glCallList(wallList);
	glPopMatrix();

	//...
}*/

/*void DrawScene()
{
	DrawFloor();
	DrawInfo();
	if (!bshow){
		DrawBarrier();
		DrawWalls();
	}
	DrawObjs();

	glFlush();
}*/

void Reshape(int width, int height){
	currentSize[0] = width;
	currentSize[1] = height;
	centerPoint[0] = currentSize[0] / 2;
	centerPoint[1] = currentSize[1] / 2;
	if (currentSize[1] == 0)                                        // Prevent A Divide By Zero By
	{
		currentSize[1] = 1;                                        // Making currentSize[1] Equal One
	}

	glViewport(0, 0, currentSize[0], currentSize[1]);                        // Reset The Current Viewport

	glMatrixMode(GL_PROJECTION);                        // Select The Projection Matrix
	glLoadIdentity();                                    // Reset The Projection Matrix
	// Calculate The Aspect Ratio Of The Window
	gluPerspective(45.0f, (GLfloat)currentSize[0] / (GLfloat)currentSize[1], 0.1f, 100.0f);//透视投影
	glMatrixMode(GL_MODELVIEW);                            // Select The Modelview Matrix
	glLoadIdentity();
	gluOrtho2D(0, 100, 0, 100);
}

void Redraw(){
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glLoadIdentity();

	if (cameraType == FOCUSED_CAM)
		gluLookAt(m_PosX, m_PosY, m_PosZ,
			m_PosX + camera.xeye, m_PosY + camera.yeye, m_PosZ + camera.zeye,
			0.0, 1.0, 0.0);
	/*else if(cameraType == TOPDOWN_CAM)
		gluLookAt(...);*/

	glEnable(GL_DEPTH_TEST);
	glEnable(GL_LIGHTING);

	GLfloat lightDirection[] = { camera.xeye, camera.yeye + 0.5, camera.zeye };

	GLfloat white[] = { 1.0, 1.0, 1.0, 1.0 };
	GLfloat light_pos[] = { 5, 5, 5, -1 };
	GLfloat spot_direction[] = { -1, -1, -1, 1 };
	GLfloat light_diffuse[] = { 1, 1, 1, 1.0 };
	GLfloat light_specular[] = { 1, 1, 1, 1.0 };

	glLightfv(GL_LIGHT5, GL_DIFFUSE, light_diffuse);
	glLightfv(GL_LIGHT5, GL_SPECULAR, light_specular);
	glLightfv(GL_LIGHT5, GL_SPOT_DIRECTION, spot_direction);
	glLightfv(GL_LIGHT5, GL_POSITION, light_pos);
	glLightfv(GL_LIGHT5, GL_AMBIENT, white);

	GLfloat mpos[] = { m_PosX, m_PosY, m_PosZ,1 };
	glLightfv(GL_LIGHT2, GL_POSITION, (const GLfloat*)mpos);
	glLightf(GL_LIGHT2, GL_SPOT_CUTOFF, 25.0);
	glLightfv(GL_LIGHT2, GL_SPOT_DIRECTION, lightDirection);
	glLightf(GL_LIGHT2, GL_SPOT_EXPONENT, lightS);
	glLightfv(GL_LIGHT2, GL_AMBIENT, white);
	glEnable(GL_LIGHT2);
	DrawScene();

	glutSwapBuffers();
}

void Idle()
{
	glutPostRedisplay();
}

void Delay(int time)
{
	clock_t now = clock();
	while (clock() - now < time);
}

void SetCamera(GLfloat x, GLfloat y)         /*x，y 是水平方向和竖直方向的改变量*/
{
	GLfloat alpha, fy;                  /*和它的名字一样，不过是单位是弧度*/
	if ((polar.fy + y) > 5.0f && (polar.fy + y) < 175.0f)
	{     /*定义竖直偏角只能在5°到175°之间*/
		polar.alpha += x;                  /*根据鼠标移动的方向设置新的球坐标*/
		polar.fy += y;

		if (polar.alpha > 360.0f) polar.alpha -= 360.0f;
		if (polar.alpha < 0.0f) polar.alpha += 360.0f;

		alpha = polar.alpha*DEG_TO_RAD;
		fy = polar.fy*DEG_TO_RAD;            /*角度转弧度*/
		camera.xeye = polar.r * sin(fy) * cos(alpha);       /*极坐标转直角坐标*/
		camera.zeye = polar.r * sin(fy) * sin(alpha);
		camera.yeye = -polar.r * cos(fy);
	}
}

void Key(unsigned char k, int x, int y)
{
	switch (k) {
	/*case '1':
		cameraType = TOPDOWN_CAM;
		break;*/
	case '2':
		cameraType = FOCUSED_CAM;
		break;
	case 'p'://snape  screen
		SnapScreen(initialSize[0], initialSize[1]);
		break;
	case 'i':
		bshow = !bshow;
		break;
	case 'o':
		lightOn = !lightOn;
		if (lightOn)
			glEnable(GL_LIGHT5);
		else
			glDisable(GL_LIGHT5);
		break;
	case 27:
		exit(0);
		break;
	//case 
	default:break;
	}
}

void EnterWindow(int state) {
	if (state == GLUT_LEFT)
	{//pick another window case the following actions such as pause
	}
	else if (state == GLUT_ENTERED)  //initialize the position of the cursor
		SetCursorPos(centerPoint[0], centerPoint[1]);
}

void Init() {
	glGenTextures(20, Tex);

	GLuint* tmp = Tex;

	//texload(tmp, "1.bmp");
	//texload(++tmp, "2.bmp");
	//...

	wallList = WallList();
	singleLineList = SingleWall(0, 0, 2);
	singleColumnList = SingleWall(0, 0, 1);

	//GLuint texture[5];
	centerPoint[0] = currentSize[0] / 2;
	centerPoint[1] = currentSize[1] / 2;
	previousPoint[0] = centerPoint[0];
	previousPoint[1] = centerPoint[1];
	SetCamera(0.0f, 0.0f);
	ShowCursor(false);
}

int main(int argc, char *argv[])
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_RGBA | GLUT_DEPTH | GLUT_DOUBLE);

	currentSize[0] = initialSize[0];
	currentSize[1] = initialSize[1];
	glutInitWindowPosition(GetSystemMetrics(SM_CXSCREEN) / 2 - initialSize[0] / 2, GetSystemMetrics(SM_CYSCREEN) / 2 - initialSize[1] / 2);
	glutInitWindowSize(initialSize[0], initialSize[1]);  //set initial size of the window
	//glutInitWindowSize(GetSystemMetrics(SM_CXSCREEN), GetSystemMetrics(SM_CYSCREEN));
	glutCreateWindow(argv[0]);
	//glutMenuStateFunc(void(*func)(int state));  //use the menu
	//glutTimerFunc(unsigned int millis, void(*func)(int value), int value);  //do the func when time ends(disposable)
	Init();
	glutDisplayFunc(Redraw);
	glutReshapeFunc(Reshape);
	glutEntryFunc(EnterWindow);  //callback when the mouse enters into the window or moves out of it
	glutKeyboardFunc(Key);
	glutIdleFunc(Idle);
	//glutMouseFunc(Mouse);
	//glutPassiveMotionFunc(MouseMove); //change view direction when the mouse moves
	glutMainLoop();
	return 0;
}