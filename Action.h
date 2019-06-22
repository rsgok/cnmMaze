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

	void go_forward(float speed);
	void go_backward(float speed);
	void go_left(float speed);
	void go_right(float speed);
};

enum Direction {
	W,//ǰ
	A,//��
	S,//��
	D//��
};

class Action {
public:	
	Figure player;//��ɫ
	int window_h, window_w;	//�������
	//�ٶ�
	const float maxSpeed ,Speed_a;
	float nowSpeed;
	//����
	bool dir_w, dir_a, dir_s, dir_d;
	//��Ծ
	//y = -x^2 +x
	const float jmp_g;
	float jmp_x;
	Action(float x, float y, float z, float vx, float vy, float vr) 
		:player(x, y, z,vx ,vy ,vr),maxSpeed(0.005),Speed_a(0.005),jmp_g(0.001)
	{
		nowSpeed = 0.0; dir_w = dir_a = dir_s = dir_d = 0;
	}
	void ViewAction(int x, int y);
	void setMoveDir(Direction dir, bool b);
	void MoveAction();
	void jmp();
	//void KeyAction(unsigned char k, int x, int y);
	

};

