#include"Action.h"
#include<Windows.h>

float objSize[12][2] = { {0.5,1.0}, {0,0}, {0.25,0.5},{0.5,1},{0.5,1},{0.5,1},{0.4,0.8},{0,0},{0.025,0.05},{0.15,0.3},{0.3,0.6},{0.15,0.3} };

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
	return z + vr * sin(viewFlag?min(vy_ang,0.2): max(vy_ang, -0.2));
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
	
	
	const static float MoveSensitivity_x = 0.01,
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

void Action::MoveAction(const MazeMap &Mmap)
{
	float M_x = player.x, M_y = player.y, M_z = player.z;
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
	if (player.Collision(Mmap))
	{
		player.x = M_x;
		player.y = M_y;
		player.z = M_z;
	}

	//Jmp

	M_x = player.x, M_y = player.y, M_z = player.z;
	if (jmp_x > -0.5)
	{
		player.z -= 4 * (jmp_x - jmp_x * jmp_x);
		jmp_x = max(0, jmp_x - jmp_g);
		player.z += 4*(jmp_x - jmp_x * jmp_x);
	}
	else
	{
		player.z -= jmp_g;
	}
	if (player.Collision(Mmap))
	{
		player.x = M_x;
		player.y = M_y;
		player.z = M_z;
	}
	
}
void Action::jmp()
{
	if (jmp_x <= 0) jmp_x = 1.0;
}
bool Figure::Collision(const MazeMap &Mmap)
{
	int X = x, Y = y;
	int st_x[9] = { 0,0,0,-1,-1,-1,1,1,1 },
		st_y[9] = { 0,-1,1,0,-1,1,0,-1,1 };
	if (z < 0) return true;
	for (int t = 0; t < 9; ++t) if(Mmap[X+st_x[t]][Y+st_y[t]]!=0)
	if(X+st_x[t]>=0&&X+st_x[t]<Mmap.sizeX&&Y+st_y[t]>=0&&Y+st_y[t]<Mmap.sizeY*Mmap.sizeNum)
	{
		int Mobj = Mmap[X + st_x[t]][Y + st_y[t]] + 1;
		float XX = X + 0.5 + st_x[t], YY = Y + 0.5 + st_y[t];
		if(z>=0&&z<=objSize[Mobj][1])
		if (figSize + objSize[Mobj][0] > sqrt((XX - x)*(XX - x) + (YY - y)*(YY - y)))
			return true;
	}
	return false;
}
bool Action::InView(float Ix, float Iy)
{
	if (abs(Ix - player.x) + abs(Iy - player.y) <= 2) return true;
	return abs(Ix-player.x)+abs(Iy-player.y)<=5 
		&&(Ix - player.x)*(player.pos_vx() - player.x) + (Iy - player.y)*(player.pos_vy() - player.y)<=0;
}