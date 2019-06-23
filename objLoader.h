#pragma once
#include <string>
#include <vector>
#include <GL/glut.h>

using namespace std;

struct Point {
	double x;
	double y;
	double z;
};
struct Face {
	int V[3];
	int T[3];
	int N[3];
};
struct Texture {
	double tu;
	double tv;
};
struct nVector {
	double nx;
	double ny;
	double nz;
};

class objLoader
{
public:
	void load(string filename);
	void draw();

public:
	vector<Point> V; // point data set
	vector<Face> F; // face data set
	vector<Texture> VT; // texture
	vector<nVector> VN; // normal vector
};