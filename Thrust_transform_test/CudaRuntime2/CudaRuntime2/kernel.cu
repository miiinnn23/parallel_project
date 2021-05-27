
#include "cuda_runtime.h"
#include "device_launch_parameters.h"

#include <stdio.h>
#include <stdlib.h>
#include "..\usr\include\GL\freeglut.h"
#include <vector>
#include "..\thrust\device_vector.h"
#include "..\thrust\host_vector.h"
//#include "..\thrust\transform.h"
#include <chrono>

using namespace std;
using namespace thrust;

int Width = 800;
int Height = 600;

struct Particle {
	double m;		// 질량
	double x[3];	// 위치
	double v[3];	// 속도
	double size;	// 크기
	double c[3];	// 색상
};

host_vector<Particle> HSystem;

void Render();
void Reshape(int w, int h);
void Mouse(int button, int state, int x, int y);
void Timer(int id);

void iter(double dt, device_vector<Particle> DSystem);

struct changeValue {
	__host__ __device__ Particle operator()(Particle p) {
		double Gravity[3] = { 0.0, -9.8, 0.0 };
		p.x[1] = p.x[1] + 0.1 * p.v[1];
		p.x[2] = p.x[2] + 0.1 * p.v[2];
		p.x[3] = p.x[3] + 0.1 * p.v[3];

		p.v[0] = p.v[0] + 0.1 * Gravity[0];
		p.v[1] = p.v[1] + 0.1 * Gravity[1];
		p.v[2] = p.v[2] + 0.1 * Gravity[2];

		return p;
	}
};

int main(int argc, char** argv) {
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);

	glutInitWindowSize(Width, Height);
	glutCreateWindow("Particle System");

	glutDisplayFunc(Render);
	glutReshapeFunc(Reshape);
	glutMouseFunc(Mouse);
	glutTimerFunc(10, Timer, 0);

	cudaSetDevice(0);
	//cudaMalloc((void**)&DevImage, sizeof(unsigned char) * Dim * Dim * 3);*/

	glutMainLoop();
	return 0;
}

void Reshape(int w, int h) {
	glViewport(0, 0, w, h);
}

// GPU 연산 필요한 부분
void iter(double dt, device_vector<Particle> DSystem) {
	device_vector<Particle>::iterator it = DSystem.begin();
	printf("ITER\n");
	int i = 0;
	while (it != DSystem.end()) {
		//Particle temp = *it;
		changeValue cv;
		thrust::transform(DSystem[i], DSystem[i+1], DSystem[i], cv);
		//transform(DSystem.begin(), DSystem.end(), DSystem.begin(), )
		
		/*if (it[0].operator Particle().x[1] < 0.0) {
			printf("????????????????????????????????????????????????????????????????\n");
			it = DSystem.erase(it);
			continue;
		}*/
		++it;
		i++;
	}
	
}

void Timer(int id) {
	device_vector<Particle> DSystem = HSystem;
	//DSystem = HSystem;
	double dt = 0.1;

	Particle* ptr = thrust::raw_pointer_cast(DSystem.data());

	dim3 gridsize((HSystem.size() - 1) / 32 + 1, (HSystem.size() - 1) / 32 + 1, 1);
	dim3 blocksize(32, 32, 1);

	//GPUiter<<<gridsize, blocksize>>>(dt, ptr)

	printf("TIMER\n");
	iter(dt, DSystem);
	cudaDeviceSynchronize();
	//HSystem = DSystem;
	thrust::copy(DSystem.begin(), DSystem.end(), HSystem.begin());

	glutPostRedisplay();
	glutTimerFunc(10, Timer, 0);
}

void Mouse(int button, int state, int x, int y) {
	printf("MOUSE\n");
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

		HSystem.push_back(p);
	}
}

void createParticle() {


	for (int i = 0; i < HSystem.size(); ++i) {
		printf("RENDER\n");
		glPointSize(HSystem[i].size);
		glBegin(GL_POINTS);
		glColor3dv(HSystem[i].c);
		glVertex3dv(HSystem[i].x);
		glEnd();
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

	//printf("RENDER\n");

	createParticle();
	//glDrawPixels(Dim, Dim, GL_RGB, GL_UNSIGNED_BYTE, Image);

	glutSwapBuffers();
}