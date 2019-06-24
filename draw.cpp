#include "draw.h"
draw::draw()
{
	for (int i = 0; i < 15; i++)
	{
		objlist.push_back(make_pair(i, 0));
	}
}
void draw::loadElement(int num) {
	tinyobj::attrib_t attrib;
	std::vector<tinyobj::shape_t> shapes;
	std::vector<tinyobj::material_t> materials;
	std::string warn, err;

	string filename,modelPath;
	switch (num)
	{
	case 100:
		filename = "man.obj";
		break;
	case 0:
		filename = "road.obj";
		break;
	case 1:
		filename = "cat.obj";
		break;
	case 2:
		filename = "deer.obj";
		break;
	case 3:
		filename = "tree3.obj";
		break;
	case 4:
		filename = "12281_Container_v2_L2.obj";
		break;
	case 5:
		filename = "Rock1.obj";
		break;
	case 6:
		filename = "rose.obj";
		break;
	case 7:
		filename = "tree1.obj";
		break;
	case 8:
		filename = "tree2.obj";
		break;
	case 9:
		filename = "well_OBJ.obj";
		break;
	case 10:
		filename = "wood.obj";
		break;
	}
	modelPath = "assets/" + filename;
	if (!tinyobj::LoadObj(&attrib, &shapes, &materials, &warn, &err, modelPath.c_str())) {
		throw std::runtime_error(warn + err);
	}
	std::cout << "[LoadOBJ] # of vertices  : " << (attrib.vertices.size() / 3) << std::endl;
	std::cout << "[LoadOBJ] # of normals   : " << (attrib.normals.size() / 3) << std::endl;
	std::cout << "[LoadOBJ] # of texcoords : " << (attrib.texcoords.size() / 2) << std::endl;
	std::cout << "[LoadOBJ] # of shapes in .obj : " << shapes.size() << std::endl;
	std::cout << "[LoadOBJ] # of materials in .obj : " << materials.size() << std::endl;


	GLint lid = glGenLists(1);
	glNewList(lid, GL_COMPILE);
	{
		// Loop over shapes
		glBegin(GL_TRIANGLES);
		for (size_t s = 0; s < shapes.size(); s++) {
			// Loop over faces(polygon)
			size_t index_offset = 0;
			for (size_t f = 0; f < shapes[s].mesh.num_face_vertices.size(); f++) {
				int fv = shapes[s].mesh.num_face_vertices[f];

				// Loop over vertices in the face.
				for (size_t v = 0; v < fv; v++) {
					// access to vertex
					tinyobj::index_t idx = shapes[s].mesh.indices[index_offset + v];
					tinyobj::real_t vx = attrib.vertices[3 * idx.vertex_index + 0];
					tinyobj::real_t vy = attrib.vertices[3 * idx.vertex_index + 1];
					tinyobj::real_t vz = attrib.vertices[3 * idx.vertex_index + 2];
					tinyobj::real_t nx = attrib.normals[3 * idx.normal_index + 0];
					tinyobj::real_t ny = attrib.normals[3 * idx.normal_index + 1];
					tinyobj::real_t nz = attrib.normals[3 * idx.normal_index + 2];
					//tinyobj::real_t tx = attrib.texcoords[2 * idx.texcoord_index + 0];
					//tinyobj::real_t ty = attrib.texcoords[2 * idx.texcoord_index + 1];
					// Optional: vertex colors
					//tinyobj::real_t red = attrib.colors[3 * idx.vertex_index + 0];
					//tinyobj::real_t green = attrib.colors[3 * idx.vertex_index + 1];
					//tinyobj::real_t blue = attrib.colors[3 * idx.vertex_index + 2];

					//printf("v:%.2f,%.2f,%.2f\n", vx, vy, vz);

					glVertex3f(vx, vy, vz);
					glNormal3f(nx, ny, nz);
					//glTexCoord2f(tx, ty);

				}
				index_offset += fv;

				// per-face material
				shapes[s].mesh.material_ids[f];
			}
		}
		glEnd();
	}
	glEndList();

	objlist[num].second = lid;

	printf("obj load\n");
}

void draw::drawElement(int num) {
	glCallList(objlist[num].second);
}