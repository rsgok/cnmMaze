#include"GenerateMap.h"
#include<ctime>
#include<algorithm>
#include<iostream>

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

int * MazeMap::operator[](int x) const
{
	return map[x];
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


/*
int main()
{
	MazeMap test;
	for (int i = 0; i < 21; ++i)
	{
		for (int j = 0; j < 81; ++j)
			if (test[i][j]) std::cout << "  ";
			else std::cout << "##";
		std::cout << std::endl;
	}
	system("pause");
}*/