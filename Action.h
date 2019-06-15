#pragma once

#include<iostream>


//Ϊ�˱������ͼ�����Ӧ����������x�����Ϸ���z�����ֱ���y
class Figure
{
public:
	float x, y, z;		//��ɫλ��
	float vr, vx_ang, vy_ang;	//�ӵ�λ�� x���� y����
	float face_ang;		//��ɫ����λ��


	//���㷵���ӵ�����λ��
	float pos_vx();
	float pos_vy();
	float pos_vz();

	Figure(){};
	Figure(float x, float y, float z, float vx, float vy, float vr):x(x),y(y),z(z),vx_ang(vx),vy_ang(vy),vr(vr) {
		face_ang = -vx_ang;
	}
	void viewmove(float x_ang, float y_ang);

	const float speed = 1;
	void go_forward();
	void go_backward();
	void go_left();
	void go_right();
};

class Action {
public:	
	Figure player;//��ɫ
	int mouse_x, mouse_y;	//�������
	bool MouseIn;			//����Ƿ��ڴ�����


	Action() {};
	Action(float x, float y, float z, float vx, float vy, float vr) :player(x, y, z,vx ,vy ,vr) {
		mouse_x = 0; mouse_y = 0; MouseIn = 1;
	}
	void MouseAction(int x, int y);
	void KeyAction(unsigned char k, int x, int y);
	/*
	
	{

	}

	//GLUT_LEFT      ����뿪����
	//GLUT_ENTERED  �����봰��
	void MouseEntry(int state)
	{

	}*/

};

