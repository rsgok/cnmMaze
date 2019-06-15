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

	const float speed = 1;
	void go_forward();
	void go_backward();
	void go_left();
	void go_right();
};

class Action {
public:	
	Figure player;//角色
	int mouse_x, mouse_y;	//鼠标坐标
	bool MouseIn;			//鼠标是否在窗口内


	Action() {};
	Action(float x, float y, float z, float vx, float vy, float vr) :player(x, y, z,vx ,vy ,vr) {
		mouse_x = 0; mouse_y = 0; MouseIn = 1;
	}
	void MouseAction(int x, int y);
	void KeyAction(unsigned char k, int x, int y);
	/*
	
	{

	}

	//GLUT_LEFT      鼠标离开窗口
	//GLUT_ENTERED  鼠标进入窗口
	void MouseEntry(int state)
	{

	}*/

};

