#pragma once


//��ͼ���ͣ����������ͼ
//��ǰ�ݶ�����ʽΪ 0��ǽ 1���յ�
class MazeMap {
	//��ͼ��С��������Ƚ�����
	static const int sizeX = 10 * 2 + 1, sizeY = 40 * 2 + 1;
	int **map;

public:
	//������ɵ�ͼ
	MazeMap();
	//����[]���ڵ���,֧��ֱ�ӶԶ����[][]����
	int * operator [] (int x) const;

private:
	//�����ڸ�������������һ��ǽ�����������Թ���
	void cut(int x1, int x2, int y1, int y2);


};

