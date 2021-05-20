#include <stdio.h>
#include <stdlib.h>
#include "..\usr\include\GL\freeglut.h"
#include <vector>
#include <time.h>
#define NumParticle 100

using namespace std;

int Width = 800;
int Height = 600;

struct Particle {
	double m;		// 질량
	double x[3];	// 위치
	double v[3];	// 속도
	double size;	// 크기
	double c[3];	// 색상
	double age;		// 나이

	bool launch;		// 발사 여부
	double launchTime;	// 발사 시간
	double launchV[3];	// 발사 시간 동안의 속도
};

double downGravity[3] = { 0.0, -9.8, 0.0 };
double upGravity[3] = { 0.0, -1, 0.0 };
double ExtForce[3] = { 0.0, 0.0, 0.0 };
vector<Particle> PSystem;

void Render();
void Reshape(int w, int h);
void Mouse(int button, int state, int x, int y);
void Keyboard(unsigned char key, int x, int y);
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
	glutKeyboardFunc(Keyboard);
	glutTimerFunc(10, Timer, 0);

	glutMainLoop();
	return 0;
}

void Reshape(int w, int h) {
	glViewport(0, 0, w, h);
}

void iter(double dt, vector<Particle>::iterator it) {
	while (it != PSystem.end()) {
		// 파티클의 위치 계산
		/*it->x[0] = it->x[0] + dt * it->v[0];
		it->x[1] = it->x[1] + dt * it->v[1];
		it->x[2] = it->x[2] + dt * it->v[2];*/

		if (it->launch) {
			it->x[0] = it->x[0] + dt * it->launchV[0];
			it->x[1] = it->x[1] + dt * it->launchV[1];
			it->x[2] = it->x[2] + dt * it->launchV[2];

			it->launchV[0] = it->launchV[0] + dt * (upGravity[0]);
			it->launchV[1] = it->launchV[1] + dt * (upGravity[1]);
			it->launchV[2] = it->launchV[2] + dt * (upGravity[2]);
		}
		else {
			it->x[0] = it->x[0] + dt * it->v[0];
			it->x[1] = it->x[1] + dt * it->v[1];
			it->x[2] = it->x[2] + dt * it->v[2];

			it->v[0] = it->v[0] + dt * (downGravity[0] / it->m);
			it->v[1] = it->v[1] + dt * (downGravity[1] / it->m);
			it->v[2] = it->v[2] + dt * (downGravity[2] / it->m);
		}

		if (it->m > 19.9 && (it->age < 0.3 && it->age > 0.2)) {
			for (int i = 0; i < 50; i++) {
				Particle p;
				p.m = rand() / (double)RAND_MAX * 10.0;

				p.x[0] = it->x[0];
				p.x[1] = it->x[1];
				p.x[2] = 0.0;

				/*double theta = 2 * 3.14 * (double)i / (NumParticle / 2 - 1);*/
				double theta = 2 * 3.14 * (double)i / (50 - 1);
				double speed = rand() / (double)RAND_MAX * 10.0f;
				p.v[0] = speed * cos(theta);
				p.v[1] = speed * sin(theta);
				p.v[2] = 0.0;

				p.size = rand() / (double)RAND_MAX * 3.5;

				p.age = p.m;
				p.c[0] = it->c[0];
				p.c[1] = it->c[1];
				p.c[2] = it->c[2];

				p.launch = false;
				p.launchTime = 0.0f;
				p.age = p.m + p.launchTime;

				PSystem.push_back(p);
			}
		}

		it->age -= 0.1;

		if (it->launchV[1] < 0.0f) {
			it->launch = false;
		}

		if (it->age < 0.0) {
			it = PSystem.erase(it);
			continue;
		}
		/*if (it->x[1] < 0.0) {
			it->v[1] *= -1;
		}*/
		/*if (it->x[1] < 0.0) {
			it = PSystem.erase(it);
			continue;
		}*/
		++it;
	}
}

void Timer(int id) {
	clock_t st = clock();
	double dt = 0.1;
	vector<Particle>::iterator it = PSystem.begin();

	iter(dt, it);

	glutPostRedisplay();
	//printf("particle count = %d\n", PSystem.size());
	//printf("Elapsed time = %u ms\n", clock() - st);
	glutTimerFunc(10, Timer, 0);
}

void Mouse(int button, int state, int x, int y) {
	int randParticle = int(rand() * 20 / (double)RAND_MAX * NumParticle); // 20 <= randParticle <= 2000

	double r = rand() / (double)RAND_MAX * 1.4;
	double g = rand() / (double)RAND_MAX * 1.4;
	double b = rand() / (double)RAND_MAX * 1.4;
	double time = randParticle / (double)200.0f;

	double launchHeight = 15 + rand() / (double)RAND_MAX * 5.0f;

	for (int i = 0; i < randParticle; ++i) {
		Particle p;

		p.m = rand() / (double)RAND_MAX * 20.0;

		p.x[0] = x;
		p.x[1] = Height - y;
		p.x[2] = 0.0;

		double theta = 2 * 3.14 * (double)i / (randParticle - 1);
		double speed = rand() / (double)RAND_MAX * 10.0f;
		p.v[0] = speed * cos(theta);
		p.v[1] = speed * sin(theta);
		p.v[2] = 0.0;

		p.launchV[0] = 0.0f;
		p.launchV[1] = launchHeight;
		p.launchV[2] = 0.0f;

		p.size = rand() / (double)RAND_MAX * 5.0;

		p.c[0] = r;
		p.c[1] = g;
		p.c[2] = b;

		p.launch = true;
		p.launchTime = time;
		//p.age = p.m * 0.8 + p.launchTime;
		p.age = p.m + p.launchTime;

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

void Keyboard(unsigned char key, int x, int y) {
	if (key == 27) exit(1);

	if (key == '1') {
		ExtForce[0] = 100.0;
		ExtForce[1] = 0.0;
		ExtForce[2] = 0.0;
	}
	if (key == '2') {
		ExtForce[0] = -100.0;
		ExtForce[1] = 0.0;
		ExtForce[2] = 0.0;
	}
}