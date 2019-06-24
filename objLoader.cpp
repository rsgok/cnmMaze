#pragma warning(disable : 4996)
#include "objLoader.h"
#include <iostream>
#include <fstream>
#include <sstream>

using namespace std;

void objLoader::load(string filename)
{
	ifstream ifs(filename);
	string s;
	Face *f;
	Point *v;
	nVector *vn;
	Texture *vt;
	while (getline(ifs, s))
	{
		if (s.length() < 2)continue;
		if (s[0] == 'v') {
			if (s[1] == 't') {
				istringstream in(s);
				vt = new Texture();
				string head;
				in >> head >> vt->tu >> vt->tv;
				VT.push_back(*vt);
			}
			else if (s[1] == 'n') {
				istringstream in(s);
				vn = new nVector();
				string head;
				in >> head >> vn->nx >> vn->ny >> vn->nz;
				VN.push_back(*vn);
			}
			else {
				istringstream in(s);
				v = new Point();
				string head;
				in >> head >> v->x >> v->y >> v->z;
				V.push_back(*v);
			}
		}
		else if (s[0] == 'f') {
			for (int k = 0; k<= s.size() - 1; k++) {
				if (s[k] == '/') { s[k] = ' '; 
				if(s[k+1]=='/')
					s.insert(k+1, "0");
				if (s[k - 1] == ' ')
					s.insert(k + 1, "0");
				}
			}
			istringstream in(s);
			f = new Face();
			string head;
			in >> head;
			int i = 0;
			while (i < 3)
			{
				if (V.size() != 0)
				{
					in >> f->V[i];
					f->V[i] -= 1;
				}
				if (VT.size() != 0)
				{
					in >> f->T[i];
					f->T[i] -= 1;
				}
				if (VN.size() != 0)
				{
					in >> f->N[i];
					f->N[i] -= 1;
				}
				i++;
			}
			F.push_back(*f);
		}
	}
}

void objLoader::draw()
{
	glPushMatrix();
	glTranslated(0,0,0);
	glBegin(GL_TRIANGLES);	

	glColor3f(1.0, 0, 0);// ����������
	for (int i = 0; i < F.size(); i++)
	{
		//if (VT.size() != 0)glTexCoord2f(VT[F[i].T[0]].tu, VT[F[i].T[0]].tv);  //����	
		//if (VN.size() != 0)glNormal3f(VN[F[i].N[0]].nx, VN[F[i].N[0]].ny, VN[F[i].N[0]].nz);//������
		glVertex3f(V[F[i].V[0]].x, V[F[i].V[0]].y, V[F[i].V[0]].z);		// �϶���

		//if (VT.size() != 0)glTexCoord2f(VT[F[i].T[1]].tu, VT[F[i].T[1]].tv);  //����
		//if (VN.size() != 0)glNormal3f(VN[F[i].N[1]].nx, VN[F[i].N[1]].ny, VN[F[i].N[1]].nz);//������
		glVertex3f(V[F[i].V[1]].x, V[F[i].V[1]].y, V[F[i].V[1]].z);		// ����

		//if (VT.size() != 0)glTexCoord2f(VT[F[i].T[2]].tu, VT[F[i].T[2]].tv);  //����
		//if (VN.size() != 0)glNormal3f(VN[F[i].N[2]].nx, VN[F[i].N[2]].ny, VN[F[i].N[2]].nz);//������
		glVertex3f(V[F[i].V[2]].x, V[F[i].V[2]].y, V[F[i].V[2]].z);		// ����
	}
	glEnd();										// �����λ��ƽ���	
	glPopMatrix();
}