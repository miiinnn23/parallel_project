
#include "cuda_runtime.h"
#include "device_launch_parameters.h"

#include <stdio.h>
#include <stdlib.h>
#include "..\usr\include\GL\freeglut.h"
#include <vector>
#include <time.h>
#include "thrust/device_vector.h"
#include "thrust/host_vector.h"
#include "thrust/copy.h"

#define NumParticle 1000
#define TILE_WIDTH 32

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
};

double Gravity[3] = { 0.0, -9.8, 0.0 };
double ExtForce[3] = { 0.0, 0.0, 0.0 };
vector<Particle> PSystem;

void Render();
void Reshape(int w, int h);
void Mouse(int button, int state, int x, int y);
void Keyboard(unsigned char key, int x, int y);
void Timer(int id);

void iter(double dt, vector<Particle>::iterator it);

__global__ void myKernel(Particle* ptr, double dt, int width);

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

__global__ void myKernel(Particle* ptr, double dt, int width) {
	int i = blockIdx.y * TILE_WIDTH + threadIdx.y;
	int j = blockIdx.x * TILE_WIDTH + threadIdx.x;
	//int i = blockDim.x * blockIdx.x + threadIdx.x;

	//if (i < width) {
	//	ptr[i].x[0] = ptr[i].x[0] + dt * ptr[i].v[0];
	//	ptr[i].x[1] = ptr[i].x[1] + dt * ptr[i].v[1];
	//	ptr[i].x[2] = ptr[i].x[2] + dt * ptr[i].v[2];

	//	ptr[i].v[1] = ptr[i].v[1] + dt * (-9.8 / ptr[i].m);
	//	ptr[i].age -= 0.1;
	//	//if(i == 0) printf("ptr[%d].age = %f\n", i, ptr[i].age);
	//}
	if (i < width && j < width) {
		/*if (i == 0 && j == 0) {
			printf("ptr[%d].age = %f\n", i * width + j, ptr[i * width + j].age);
		}*/
		ptr[i * width + j].x[0] = ptr[i * width + j].x[0] + dt * ptr[i * width + j].v[0];
		ptr[i * width + j].x[1] = ptr[i * width + j].x[1] + dt * ptr[i * width + j].v[1];
		ptr[i * width + j].x[2] = ptr[i * width + j].x[2] + dt * ptr[i * width + j].v[2];

		ptr[i * width + j].v[1] = ptr[i * width + j].v[1] + dt * (-9.8 / ptr[i * width + j].m);

		ptr[i * width + j].age -= 0.1;
	}
}

void iter(double dt, vector<Particle>::iterator it) {
	int count = 0;
	thrust::device_vector<Particle> DSystem = PSystem;

	if (!PSystem.empty()) {
		dim3 dimGrid((PSystem.size() - 1) / TILE_WIDTH + 1, (PSystem.size() - 1) / TILE_WIDTH + 1);
		dim3 dimBlock(TILE_WIDTH, TILE_WIDTH);

		Particle* raw_ptr = thrust::raw_pointer_cast(&DSystem[0]);

		//myKernel << <1, PSystem.size() >> > (raw_ptr, dt, PSystem.size());
		myKernel << <dimGrid, dimBlock>> > (raw_ptr, dt, PSystem.size());

		thrust::copy(DSystem.begin(), DSystem.end(), PSystem.begin());
	}

	while (it != PSystem.end()) {
		if (it->age < 0.0) {
			it = PSystem.erase(it);
			continue;
		}

		count++;
		it = PSystem.begin() + count;
	}
}

void Timer(int id) {
	clock_t st = clock();
	double dt = 0.1;

	//thrust::device_vector<Particle> DSystem = PSystem;
	vector<Particle>::iterator it = PSystem.begin();

	iter(dt, it);

	glutPostRedisplay();
	printf("particle count = %d\n", PSystem.size());
	//printf("Elapsed time = %u ms\n", clock() - st);
	glutTimerFunc(10, Timer, 0);
}

void Mouse(int button, int state, int x, int y) {
	int randParticle = int(rand() / (double)RAND_MAX * NumParticle);

	double r = rand() / (double)RAND_MAX * 1.4;
	double g = rand() / (double)RAND_MAX * 1.4;
	double b = rand() / (double)RAND_MAX * 1.4;
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

		p.size = rand() / (double)RAND_MAX * 3.5;

		p.age = p.m * 0.8;
		p.c[0] = r;
		p.c[1] = g;
		p.c[2] = b;

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