#include <stdio.h>
#include <stdlib.h>
#include "..\usr\include\GL\freeglut.h"
#include <vector>

using namespace std;

int width = 800;
int height = 600;

void Render();
void Reshape(int w, int h);
void Mouse(int button, int state, int x, int y);

struct Vertex {
	double x[2]; //	위치
	double c[3]; // 색상
	double size;
};

vector<Vertex> Points;
GLint texture;

GLuint LoadTexture(const char* filename)
{
	GLuint texture;
	int w, h;
	unsigned char* data;

	FILE* file;
	fopen_s(&file, filename, "rb");

	if (file == NULL) return 0;

	w = 680;
	h = 460;
	data = (unsigned char*)malloc(w * h * 4 * sizeof(unsigned char));

	fread(data, w * h * 4, sizeof(unsigned char), file);
	fclose(file);

	for (int i = 0; i < w * h; ++i)
	{
		int index = i * 4;
		unsigned char R, G, B, A;
		R = data[index];
		G = data[index + 1];
		B = data[index + 2];
		A = data[index + 3];

		/*data[index] = R;
		data[index + 2] = B;*/

		//printf("%d(%d, %d, %d)\n", index, R, data[index + 1], B);
	}

	glGenTextures(1, &texture);
	glBindTexture(GL_TEXTURE_2D, texture);
	glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_REPLACE);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_NEAREST);

	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	gluBuild2DMipmaps(GL_TEXTURE_2D, 4, w, h, GL_RGBA, GL_UNSIGNED_BYTE, data);
	free(data);

	return texture;
}

int main(int argc, char** argv) {
	glutInit(&argc, argv);
	//glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
	glutInitDisplayMode(GLUT_RGBA);

	glutInitWindowSize(width, height);
	glutCreateWindow("aaa");
	texture = LoadTexture("..\\image2.bmp");

	glutDisplayFunc(Render);
	glutReshapeFunc(Reshape);
	glutMouseFunc(Mouse);

	glutMainLoop();
	return 0;
}

void Reshape(int w, int h) {
	glViewport(0, 0, w, h);
}

void Render() {
	glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT);

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluOrtho2D(0, width, 0, height);

	glMatrixMode(GL_MODELVIEW);
	/*glEnable(GL_POINT_SMOOTH);
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);*/
	glEnable(GL_TEXTURE_2D);

	glBegin(GL_POLYGON);
	{
		glColor3d(0.5, 1, 1);

		glTexCoord2d(0.0, 0.0);
		glNormal3f(0.0, 0.0, 1.0);
		glVertex2f(0, 0);

		glTexCoord2d(1.0, 0.0);
		glNormal3f(0.0, 0.0, 1.0);
		glVertex2f(800, 0);

		glTexCoord2d(1.0, 1.0);
		glNormal3f(0.0, 0.0, 1.0);
		glVertex2f(800, 600);

		glTexCoord2d(0.0, 1.0);
		glNormal3f(0.0, 0.0, 1.0);
		glVertex2f(0, 600);
	}
	glEnd();
	glDisable(GL_TEXTURE_2D);

	//glBegin(GL_QUADS);
	//{
	//	glColor3d(1, 1, 0.5);
	//	glVertex2d(400, 0);
	//	glVertex2d(800, 0);
	//	glVertex2d(800, 600);
	//	glVertex2d(400, 600);
	//}
	//glEnd();
	
	glEnable(GL_POINT_SMOOTH);
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	for (int i = 0; i < Points.size(); ++i) {
		glPointSize(Points[i].size);
		glBegin(GL_POINTS);
		glColor3dv(Points[i].c);
		glVertex3dv(Points[i].x);
		glEnd();
	}

	glFinish();
}

void Mouse(int button, int state, int x, int y) {
	if (state == GLUT_DOWN) {
		Vertex v;
		v.x[0] = x;
		v.x[1] = height - y;

		v.size = 10 + rand() / (double)RAND_MAX * 3.0f;

		v.c[0] = 0.5 + rand() / ((double)RAND_MAX * 2);
		v.c[1] = 0.5 + rand() / ((double)RAND_MAX * 2);
		v.c[2] = 0.5 + rand() / ((double)RAND_MAX * 2);

		Points.push_back(v);
	}
}