#include"Action.h"
#include<Windows.h>

float Figure::pos_vx()
{
	return x + vr*cos(vx_ang);
}
float Figure::pos_vy()
{
	return y + vr * sin(vx_ang);
}
float Figure::pos_vz()
{
	return z + vr * sin(vy_ang);
}

void Figure::viewmove(float x_ang, float y_ang)
{
	vx_ang -= x_ang; 
	if(abs(vy_ang+y_ang)<=acos(0)) vy_ang += y_ang;
}
void Figure::go_forward(float speed)
{
	//face_ang = -vx_ang;
	face_ang = vx_ang + acos(-1);
	x += speed * cos(face_ang);
	y += speed * sin(face_ang);
}
void Figure::go_backward(float speed)
{
	//face_ang = -vx_ang;
	face_ang = vx_ang + acos(-1);
	x -= speed * cos(face_ang);
	y -= speed * sin(face_ang);
}
void Figure::go_left(float speed)
{
	x += speed * cos(face_ang+acos(0));
	y += speed * sin(face_ang+acos(0));
}
void Figure::go_right(float speed)
{
	x += speed * cos(face_ang-acos(0));
	y += speed * sin(face_ang-acos(0));
}
void Figure::setViewFlag()
{
	viewFlag = !viewFlag;
}


void FixMousePos(int x, int y)
{
	POINT p;
	GetCursorPos(&p);
	SetCursorPos(p.x - x, p.y - y);
}

void Action::ViewAction(int x,int y)
{
	
	
	const static float MoveSensitivity_x = 0.1,
					   MoveSensitivity_y = 0.05;
	player.viewmove((x - window_w / 2)*MoveSensitivity_x, (y - window_h / 2)*MoveSensitivity_y);
	FixMousePos(x - window_w / 2, y - window_h / 2);
}
void Action::setMoveDir(Direction dir, bool b)
{
	switch (dir)
	{
	case Direction::W:
		dir_w = b;
		break;
	case Direction::A:
		dir_a = b;
		break;
	case Direction::S:
		dir_s = b;
		break;
	case Direction::D:
		dir_d = b;
		break;
	}
}

void Action::MoveAction()
{
	bool o = dir_w || dir_a || dir_s || dir_d;
	if (o)
		nowSpeed = min(maxSpeed, nowSpeed + Speed_a);                                                                                                                                                                                                                                                                                                                                                                                                        
	else
		nowSpeed = max(0, nowSpeed - Speed_a);
	if (nowSpeed > 0)
	{
		if (dir_w) player.go_forward(nowSpeed);
		if (dir_s) player.go_backward(nowSpeed);
		if (dir_a) player.go_left(nowSpeed);
		if (dir_d) player.go_right(nowSpeed);
	}
	//Jmp
	if (jmp_x > 0)
	{
		jmp_x = max(0, jmp_x - jmp_g);
		player.z = 4*(jmp_x - jmp_x * jmp_x);
	}
}
void Action::jmp()
{
	if (jmp_x <= 0) jmp_x = 1.0;
}