#include <stdio.h>
#include <stdlib.h>
#include "..\usr\include\GL\freeglut.h"
#include <vector>
#include <time.h>
#define NumParticle 1000

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

	double hist[15][3];	// 불꽃놀이 자취 형성

	bool launch;		// 발사 여부
	double launchTime;	// 발사 시간
	double launchV[3];	// 발사 시간 동안의 속도
};

vector<Particle> PSystem;

int mouseCount = 0;

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
	glutCreateWindow("Firework Simulation(CPU)");

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
	int count = 0;
	while (it != PSystem.end()) {
		// 파티클의 위치 계산

		if (it->launch) {	// 발사되는 동안의 위치 & 속도벡터 계산
			it->x[0] = it->x[0] + dt * it->launchV[0];
			it->x[1] = it->x[1] + dt * it->launchV[1];
			it->x[2] = it->x[2] + dt * it->launchV[2];

			it->launchV[1] = it->launchV[1] + dt * (-1.2);

			for (int j = 0; j < 15; j++) {	// 자취 저장
				for (int k = 0; k < 3; k++) {
					it->hist[j][k] = it->x[k];
				}
			}

			if (it->launchV[1] < 0.0f) {	// 발사 종료 조건
				it->launch = false;
			}
		}
		else {	// 폭발하는 동안의 위치 & 속도벡터 계산
			for (int j = 14; j > 0; j--) {	// 자취 저장
				for (int k = 0; k < 3; k++) {
					it->hist[j][k] = it->hist[j - 1][k];
				}
			}
			for (int k = 0; k < 3; k++) {
				it->hist[0][k] = it->x[k];
			}

			it->x[0] = it->x[0] + dt * it->v[0];
			it->x[1] = it->x[1] + dt * it->v[1];
			it->x[2] = it->x[2] + dt * it->v[2];

			it->v[1] = it->v[1] + dt * (-9.8 / it->m);
		}

		it->age -= 0.1;

		if (it->age < 0.0) {	// 삭제 조건
			it = PSystem.erase(it);
			continue;
		}

		if (it->m > 19.9 && (it->age < 0.3 && it->age > 0.2)) { // 추가 불꽃놀이 생성 조건
			double x0 = it->x[0];
			double x1 = it->x[1];

			double c[3] = { it->c[0], it->c[1], it->c[2] };
			for (int i = 0; i < 500; i++) {
				Particle p;
				p.m = rand() / (double)RAND_MAX * 10.0;

				p.x[0] = x0;
				p.x[1] = x1;
				p.x[2] = 0.0;

				for (int j = 0; j < 15; j++) {
					for (int k = 0; k < 3; k++) {
						p.hist[j][k] = p.x[k];
					}
				}

				double theta = 2 * 3.14 * (double)i / (500 - 1);
				double speed = rand() / (double)RAND_MAX * 10.0f;
				p.v[0] = speed * cos(theta);
				p.v[1] = speed * sin(theta);
				p.v[2] = 0.0;

				p.size = rand() / (double)RAND_MAX * 3.5;

				p.age = p.m;
				p.c[0] = c[0];
				p.c[1] = c[1];
				p.c[2] = c[2];

				p.launch = false;
				p.launchTime = 0.0f;
				p.age = p.m + p.launchTime;

				PSystem.push_back(p);
			}
		}
		count++;
		it = PSystem.begin() + count;
	}
}

long max = 0;

void Timer(int id) {
	clock_t st = clock();
	double dt = 0.1;
	vector<Particle>::iterator it = PSystem.begin();

	iter(dt, it);

	glutPostRedisplay();

	long time = clock() - st;
	max = (time > max) ? time : max;

	if (mouseCount != 0 && PSystem.empty()) {
		printf("clicked %d times : max time = %u ms\n", mouseCount, max);
		max = 0;
		mouseCount = 0;
	}
	glutTimerFunc(10, Timer, 0);
}

void Mouse(int button, int state, int x, int y) {
	mouseCount++;
	int randParticle = 700 + int(rand() / (double)RAND_MAX * NumParticle); // 700 < randParticle < 1700

	double r = 0.5 + rand() / ((double)RAND_MAX * 2); // 밝은 색을 내기 위하여 색 값은 0.5 ~ 1.0 사이로 설정
	double g = 0.5 + rand() / ((double)RAND_MAX * 2);
	double b = 0.5 + rand() / ((double)RAND_MAX * 2);
	double time = randParticle / (double)100.0f;	// 수명은 생성되는 파티클 수에 비례

	double launchSpeed = 15 + (double)randParticle / 200;	// 발사 속도 역시 생성되는 파티클 수에 비례

	for (int i = 0; i < randParticle; ++i) {
		Particle p;

		p.m = rand() / (double)RAND_MAX * 20.0;

		p.x[0] = x;
		p.x[1] = Height - y;
		p.x[2] = 0.0;

		for (int j = 0; j < 15; j++) {
			for (int k = 0; k < 3; k++) {
				p.hist[j][k] = p.x[k];
			}
		}

		double theta = 2 * 3.14 * (double)i / (randParticle - 1);
		double speed = rand() / (double)RAND_MAX * 10.0f;
		p.v[0] = speed * cos(theta);
		p.v[1] = speed * sin(theta);
		p.v[2] = 0.0;

		p.launchV[0] = 0.0f;
		p.launchV[1] = launchSpeed;
		p.launchV[2] = 0.0f;

		p.size = rand() / (double)RAND_MAX * 5.0;

		p.c[0] = r;
		p.c[1] = g;
		p.c[2] = b;

		p.launch = true;
		p.launchTime = time;
		p.age = p.m + p.launchTime * 1.2;

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
		glLineWidth(PSystem[i].size);	// 불꽃놀이 잔상
		glBegin(GL_LINE_STRIP);
		for (int j = 14; j > 0; j--) {
			glVertex3dv(PSystem[i].hist[j]);
		}
		glEnd();

		glPointSize(PSystem[i].size);	// 입자
		glBegin(GL_POINTS);
		glColor3dv(PSystem[i].c);
		glVertex3dv(PSystem[i].x);
		glEnd();
	}

	glutSwapBuffers();
}

void Keyboard(unsigned char key, int x, int y) {
	if (key == 27) exit(1);
}