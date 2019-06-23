#pragma once

//��ͼ����
enum MazeType {
	forest = 0,
	plain = 1,
	desert = 3
};
//�����ͼ
class MazeMap {
	
public:
	//��ͼ��С��������Ƚ�����
	static const int sizeX = 21, sizeY = 31, sizeNum = 3; 
	// ����ʱ������ɵ�ͼ
	MazeMap();
	~MazeMap();
	//����[]���ڵ���,֧��ֱ�ӶԶ����[][]����
	int * operator [] (int x) const;
	//��������(x,y) ��Ӧ�ĵ�ͼ����
	MazeType type(int x, int y);

private:
	int **map;
	const int mazeModelSize;
	//dfs�����Թ���
	void m_Dig(int x, int y,int k);

};

