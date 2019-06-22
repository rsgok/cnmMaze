#pragma once

#include<iostream>


//为了便于与地图坐标对应，我们面向x方向，上方是z，右手边是y
class Figure
{
public:
	float x, y, z;		//角色位置
	float vr, vx_ang, vy_ang;	//视点位置 x横向， y纵向
	float face_ang;		//角色朝向位置


	//计算返回视点坐标位置
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
	W,//前
	A,//左
	S,//后
	D//右
};

class Action {
public:	
	Figure player;//角色
	int window_h, window_w;	//鼠标坐标
	//速度
	const float maxSpeed ,Speed_a;
	float nowSpeed;
	//方向
	bool dir_w, dir_a, dir_s, dir_d;
	//跳跃
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

