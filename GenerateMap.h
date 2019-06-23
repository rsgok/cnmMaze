#pragma once

//地图类型
enum MazeType {
	forest = 0,
	plain = 1,
	desert = 3
};
//网格地图
class MazeMap {
	
public:
	//地图大小（奇数会比较优美
	static const int sizeX = 21, sizeY = 31, sizeNum = 3; 
	// 构造时随机生成地图
	MazeMap();
	~MazeMap();
	//重载[]便于调用,支持直接对对象的[][]访问
	int * operator [] (int x) const;
	//返回坐标(x,y) 对应的地图种类
	MazeType type(int x, int y);

private:
	int **map;
	const int mazeModelSize;
	//dfs生成迷宫。
	void m_Dig(int x, int y,int k);

};

