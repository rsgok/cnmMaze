#pragma once


//地图类型，生成网格地图
//当前暂定数格式为 0：墙 1：空地
class MazeMap {
	//地图大小（奇数会比较优美
	static const int sizeX = 10 * 2 + 1, sizeY = 40 * 2 + 1;
	int **map;

public:
	//随机生成地图
	MazeMap();
	//重载[]便于调用,支持直接对对象的[][]访问
	int * operator [] (int x) const;

private:
	//生成在给定区域内生成一段墙，用于生成迷宫。
	void cut(int x1, int x2, int y1, int y2);


};

