#include <stdio.h>
#include <stdlib.h>
#include "..\usr\include\GL\freeglut.h"
#include <vector>

using namespace std;

int Width = 800;
int Height = 600;

struct Particle {
	double m;		// 질량
	double x[3];	// 위치
	double v[3];	// 속도
	double size;	// 크기
	double c[3];	// 색상
};

double Gravity[3] = { 0.0, -9.8, 0.0 };
vector<Particle> PSystem;

void Render();
void Reshape(int w, int h);
void Mouse(int button, int state, int x, int y);
void Timer(int id);

void iter(double dt, vector<Particle>::iterator it);

int main(int argc, char** argv) {
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);

	glutInitWindowSize(Width, Height);
	glutCreateWindow("Particle System");

	glutDisplayFunc(Render);
	glutReshapeFunc(Reshape);
	glutMouseFunc(Mouse);
	glutTimerFunc(10, Timer, 0);

	glutMainLoop();
	return 0;
}

void Reshape(int w, int h) {
	glViewport(0, 0, w, h);
}

// GPU 연산 필요한 부분
void iter(double dt, vector<Particle>::iterator it) {
	while (it != PSystem.end()) {
		it->x[0] = it->x[0] + dt * it->v[0];
		it->x[1] = it->x[1] + dt * it->v[1];
		it->x[2] = it->x[2] + dt * it->v[2];

		it->v[0] = it->v[0] + dt * Gravity[0];
		it->v[1] = it->v[1] + dt * Gravity[1];
		it->v[2] = it->v[2] + dt * Gravity[2];

		if (it->x[1] < 0.0) {
			it = PSystem.erase(it);
			continue;
		}
		++it;
	}
}

void Timer(int id) {
	double dt = 0.1;
	vector<Particle>::iterator it = PSystem.begin();

	iter(dt, it);

	glutPostRedisplay();
	glutTimerFunc(10, Timer, 0);
}

void Mouse(int button, int state, int x, int y) {
	int NumParticle = 1000;
	for (int i = 0; i < NumParticle; ++i) {
		Particle p;

		p.m = rand() / (double)RAND_MAX * 10.0;

		p.x[0] = x;
		p.x[1] = Height - y;
		p.x[2] = 0.0;

		double theta = 2 * 3.14 * (double)i / (NumParticle - 1);
		double speed = rand() / (double)RAND_MAX * 10.0f;
		p.v[0] = speed * cos(theta);
		p.v[1] = speed * sin(theta);
		p.v[2] = 0.0;

		p.size = rand() / (double)RAND_MAX * 5.0;
		p.c[0] = rand() / (double)RAND_MAX;
		p.c[1] = rand() / (double)RAND_MAX;
		p.c[2] = rand() / (double)RAND_MAX;

		PSystem.push_back(p);
	}
}

void Render() {
	glClearColor(0.0, 0.0, 0.0, 0.0);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(0.0, Width, 0.0, Height, -10.0, 10.0);

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	glEnable(GL_POINT_SMOOTH);
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	for (int i = 0; i < PSystem.size(); ++i) {
		glPointSize(PSystem[i].size);
		glBegin(GL_POINTS);
		glColor3dv(PSystem[i].c);
		glVertex3dv(PSystem[i].x);
		glEnd();
	}

	glutSwapBuffers();
}