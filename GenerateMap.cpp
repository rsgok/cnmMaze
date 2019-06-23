#include"GenerateMap.h"
#include<ctime>
#include<algorithm>
#include<iostream>


int * MazeMap::operator[](int x) const
{
	return map[x];
}
MazeType MazeMap::type(int x,int y)
{
	return MazeType(y / sizeY);
}


void MazeMap::m_Dig(int x, int y,int k)
{
	const static int DIGPROB = 2;
	map[x][y+k] = 0;
	if (x > 1 && map[x - 2][y + k] == -1 && rand() % DIGPROB == 0)
		map[x - 1][y + k] = 0, m_Dig(x - 2, y, k);
	if (y > 1 && map[x][y - 2 + k] == -1 && rand() % DIGPROB == 0)
		map[x][y - 1 + k] = 0, m_Dig(x, y - 2, k);
	if (x + 2 < sizeX && map[x + 2][y + k] == -1 && rand() % DIGPROB == 0)
		map[x + 1][y + k] = 0, m_Dig(x + 2, y, k);
	if (y + 2 < sizeY && map[x][y + 2 + k] == -1 && rand() % DIGPROB == 0)
		map[x][y + 1 + k] = 0, m_Dig(x, y + 2, k);
}

MazeMap::MazeMap() : mazeModelSize(10)
{
	map = new int *[sizeX];
	for (int i = 0; i < sizeX; ++i)
		map[i] = new int[sizeY*sizeNum];

	//srand(time(0));//随机种子
	for (int k = 0; k < sizeNum; ++k)
	{
		for (int i = 0; i < sizeX; ++i)
			for (int j = 0; j < sizeY; ++j)
				if ((i & 1) && (j & 1))
					map[i][j+k*sizeY] = -1;
				else  map[i][j+k*sizeY] = 1;
		for (int i = 1; i < sizeX; i += 2)
			for (int j = 1; j < sizeY; j += 2)
				if (map[i][j+k*sizeY] == -1)
				{
					if (i-2 > 0) map[i - 1][j+ k * sizeY] = 0;
					else if (j-2 >0) map[i][j - 1+ k * sizeY] = 0;
					m_Dig(i, j, k*sizeY);
				}
	}
	map[sizeX-2][sizeY] = map[sizeX-2][sizeY - 1] = 0;
	map[1][sizeY * 2] = map[1][sizeY * 2 - 1] = 0;

	

	for (int k = 0; k < sizeNum; ++k)
		for (int i = 0; i < sizeX; ++i)
			for (int j = 0; j < sizeY; ++j)
				if (map[i][j+k*sizeY])
					map[i][j+k*sizeY] = rand() % (mazeModelSize - 1) + 1;
	for (int i = 0; i < sizeX; ++i)
		map[i][0] = map[i][sizeY*sizeNum - 1] = -1;
	for (int i = 0; i < sizeY * sizeNum; ++i)
		map[0][i] = map[sizeX - 1][i] = -1;
}
MazeMap::~MazeMap()
{
	for (int i = 0; i < sizeX; ++i)
		delete map[i];
	delete map;
}


//for test
/*
int main()
{
	MazeMap test;
	for (int i = 0; i < 21; ++i)
	{
		for (int j = 0; j < 93; ++j)
			if (test[i][j]!=0) std::cout << test[i][j];
				else std::cout << " ";
			std::cout << std::endl;
	}
	system("pause");
}
*/

//废弃
/*
MazeMap::MazeMap()
{
	map = new int *[sizeX];
	for (int i = 0; i < sizeX; ++i)
		map[i] = new int[sizeY];
	for (int i = 0; i < sizeX; ++i)
		for (int j = 0; j < sizeY; ++j)
			map[i][j] = 0;

	//srand(time(0));//随机种子
	cut(0, sizeX, 0, sizeY);
	for (int i = 0; i < sizeX; ++i)
		 map[i][0] = map[i][sizeY-1] = 0;
	for (int i = 0; i < sizeY; ++i)
		map[0][i] = map[sizeX - 1][i] = 0;
}

void MazeMap::cut(int x1, int x2, int y1, int y2)
{
	const static int gateProb = 5; //打开出口后有 1/gateProb 的几率打开更多的通道

	if (x1+1 == x2 || y1+1 == y2) return;

	if (x2 - x1 > y2 - y1)  //选择长的边分割（感觉会比较优美？
	{
		int t = (x2 - x1 ) >> 1;
		t = (rand() % t) * 2 +1 + x1;

		for (int i = y1; i < y2; ++i)
			map[t][i] = 1;
		cut(x1, t, y1, y2);
		cut(t+1, x2, y1, y2);
	}
	else
	{
		int t = (y2 - y1) >> 1;
		t = (rand() % t) * 2 + 1 + y1;

		for (int i = x1; i < x2; ++i)
			map[i][t] = 1;
		cut(x1, x2, y1, t);
		cut(x1, x2, t+1, y2);
	}
	return;
}
*/