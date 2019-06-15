#include"Action.h"

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
void Figure::go_forward()
{
	face_ang = -vx_ang;
	x += speed * -cos(face_ang);
	y += speed * sin(face_ang);
}
void Figure::go_backward()
{
	face_ang = -vx_ang;
	x -= speed * -cos(face_ang);
	y -= speed * sin(face_ang);
}
void Figure::go_left()
{
	x += speed * -cos(face_ang-acos(0));
	y += speed * sin(face_ang-acos(0));
}
void Figure::go_right()
{
	x += speed * -cos(face_ang+acos(0));
	y += speed * sin(face_ang+acos(0));
}



void Action::MouseAction(int x,int y)
{
	const static float MoveSensitivity_x = 0.1,
					   MoveSensitivity_y = 0.05;
	player.viewmove((x - mouse_x)*MoveSensitivity_x, (y - mouse_y)*MoveSensitivity_y);
	mouse_x = x; mouse_y = y;
}
void Action::KeyAction(unsigned char k, int x, int y)
{
	switch (k)
	{
		case 'w':
			player.go_forward();
			break;
		case 's':
			player.go_backward();
			break;
		case 'a':
			player.go_left();
			break;
		case 'd':
			player.go_right();
			break;

	}
		
}