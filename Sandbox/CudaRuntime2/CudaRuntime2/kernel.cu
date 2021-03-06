
#include "cuda_runtime.h"
#include "device_launch_parameters.h"
#include "curand_kernel.h"

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "..\usr\include\GL\glew.h"
#include "..\usr\include\GL\freeglut.h"
#include "cuda_gl_interop.h"
#include <vector>
#include <time.h>
#include "thrust/device_vector.h"
#include "thrust/host_vector.h"
#include "thrust/copy.h"
#include <chrono>

#define NumParticle 1000
#define TILE_WIDTH 32

using namespace std;

int Width = 800;
int Height = 600;
GLuint gl_pbo;					// 픽셀 버퍼를 가르키는 OpenGL 핸들 
cudaGraphicsResource* cuda_pbo;	// 픽셀 버퍼를 가르키는 CUDA 핸들 
uchar4* pDevImage;

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

int mouseCount = 0;
long timeMax = 0;

//double downGravity[3] = { 0.0, -9.8, 0.0 };
//double upGravity[3] = { 0.0, -1.2, 0.0 };
//double ExtForce[3] = { 0.0, 0.0, 0.0 };
vector<Particle> PSystem;


void Render();
void Reshape(int w, int h);
void Mouse(int button, int state, int x, int y);
void Keyboard(unsigned char key, int x, int y);
void Timer(int id);
void Close();

void iter(double dt, vector<Particle>::iterator it);

//__device__ int getRand(curandState* s, int A, int B);
__global__ void myKernel(Particle* ptr, double dt, int width);
//__global__ void beforePushBackKernel(Particle* ptr, double a);
//__global__ void createParticle(int randParticle, Particle* firstPtr, double r, double g, double b, double time, double launchSpeed, int x, int y);

int main(int argc, char** argv) {
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);

	glutInitWindowSize(Width, Height);
	glutCreateWindow("Particle System");

	glutDisplayFunc(Render);
	glutReshapeFunc(Reshape);
	glutMouseFunc(Mouse);
	glutKeyboardFunc(Keyboard);
	glutTimerFunc(1, Timer, 0);
	glutCloseFunc(Close);

	glewInit();

	// OpenGL과 연동할 GPU 선택
	cudaSetDevice(3);
	cudaGLSetGLDevice(3);

	// 1. 픽셀 버퍼에 대한 핸들을 생성하여 버퍼를 바인딩
	glGenBuffers(1, &gl_pbo);
	glBindBuffer(GL_PIXEL_UNPACK_BUFFER_ARB, gl_pbo);

	// 2. 픽셀 버퍼 할당
	//	파라미터 설명:
	//		NULL: 초기화 데이터 없음
	//		GL_DYNAMIC_DRAW_ARB: 버퍼가 반복적으로 수정될 것임	
	glBufferData(GL_PIXEL_UNPACK_BUFFER_ARB, Height * Width * sizeof(uchar4), NULL, GL_DYNAMIC_DRAW_ARB);


	glutMainLoop();
	return 0;
}

void Reshape(int w, int h) {
	glViewport(0, 0, w, h);
}

void Close() {
	cudaDeviceReset();

	// 픽셀 버퍼의 바인딩을 해제하고 핸들을 제거한다.
	glBindBuffer(GL_PIXEL_UNPACK_BUFFER_ARB, 0);
	glDeleteBuffers(1, &gl_pbo);
}

//__global__ void childKernel(Particle* ptr, int i, int j, int width) {
//	ptr[i * width + j].hist[blockIdx][threadIdx] = ptr[i * width + j].x[threadIdx];
//}

__global__ void myKernel(Particle* ptr, double dt, int width) {
	int i = blockIdx.y * TILE_WIDTH + threadIdx.y;
	int j = blockIdx.x * TILE_WIDTH + threadIdx.x;

	if (i < width && j < width) {
		if (ptr[i * width + j].launch) {
			ptr[i * width + j].x[0] = ptr[i * width + j].x[0] + dt * ptr[i * width + j].launchV[0];
			ptr[i * width + j].x[1] = ptr[i * width + j].x[1] + dt * ptr[i * width + j].launchV[1];
			ptr[i * width + j].x[2] = ptr[i * width + j].x[2] + dt * ptr[i * width + j].launchV[2];

			ptr[i * width + j].launchV[1] = ptr[i * width + j].launchV[1] + dt * (-1.2);

			/*childKernel << <15, 3 >> > (ptr, i, j, width);
			cudaDeviceSynchronize();
			__syncthreads();*/
			for (int m = 0; m < 15; m++) {
				for (int k = 0; k < 3; k++) {
					ptr[i * width + j].hist[m][k] = ptr[i * width + j].x[k];
				}
			}
			

			if (ptr[i * width + j].launchV[1] < 0.0f) {
				ptr[i * width + j].launch = false;
			}
		}
		else {
			for (int m = 14; m > 0; m--) {
				for (int k = 0; k < 3; k++) {
					ptr[i * width + j].hist[m][k] = ptr[i * width + j].hist[m - 1][k];
				}
			}
			for (int k = 0; k < 3; k++) {
				ptr[i * width + j].hist[0][k] = ptr[i * width + j].x[k];
			}

			ptr[i * width + j].x[0] = ptr[i * width + j].x[0] + dt * ptr[i * width + j].v[0];
			ptr[i * width + j].x[1] = ptr[i * width + j].x[1] + dt * ptr[i * width + j].v[1];
			ptr[i * width + j].x[2] = ptr[i * width + j].x[2] + dt * ptr[i * width + j].v[2];

			ptr[i * width + j].v[1] = ptr[i * width + j].v[1] + dt * (-9.8 / ptr[i * width + j].m);
		}

		ptr[i * width + j].age -= 0.1;
	}
}


void iter(double dt, vector<Particle>::iterator it) {

	int count = 0;
	thrust::device_vector<Particle> DSystem = PSystem;

	

	if (!PSystem.empty()) {
		int size = PSystem.size();
		Particle* raw_ptr = thrust::raw_pointer_cast(&DSystem[0]);
		myKernel << <((size - 1) / TILE_WIDTH + 1, (size - 1) / TILE_WIDTH + 1), (TILE_WIDTH, TILE_WIDTH) >> > (raw_ptr, dt, PSystem.size());

		thrust::copy(DSystem.begin(), DSystem.end(), PSystem.begin());
	}

	while (it != PSystem.end()) {
		if (it->age < 0.0) {
			it = PSystem.erase(it);
			continue;
		}
		if (it->m > 19.9 && (it->age < 0.3 && it->age > 0.2)) {
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

void Timer(int id) {
	clock_t st = clock();
	double dt = 0.1;

	vector<Particle>::iterator it = PSystem.begin();

	iter(dt, it);

	glutPostRedisplay();

	long time = clock() - st;
	if (mouseCount != 1) {
		timeMax = (time > timeMax) ? time : timeMax;
	}

	if (mouseCount != 0 && PSystem.empty()) {
		printf("clicked %d times : max time = %u ms\n", mouseCount, timeMax);
		timeMax = 0;
		mouseCount = 0;
	}
	glutTimerFunc(1, Timer, 0);
}

//__global__ void createParticle(int randParticle, Particle* firstPtr, double r, double g, double b, double time, double launchSpeed, int x, int y) {
//	int Height = 600;
//	int i = blockIdx.y * TILE_WIDTH + threadIdx.y;
//	int j = blockIdx.x * TILE_WIDTH + threadIdx.x;
//
//	int id = threadIdx.x + blockDim.x * blockIdx.x;
//	unsigned int seed = id;
//	curandState s;
//	curand_init(seed, 0, 0, &s);
//
//	double random_max = 32767;
//	int randNum = getRand(&s, 0, (int)random_max); // 0~9 까지 난수 생성
//	
//	firstPtr[i * TILE_WIDTH + j].x[0] = x;
//	firstPtr[i * TILE_WIDTH + j].x[1] = Height - y;
//	firstPtr[i * TILE_WIDTH + j].x[2] = 0.0;
//
//	double theta = 2 * 3.14 * (double)(i*TILE_WIDTH + j) / (randParticle - 1);
//	double speed = randNum / random_max * 10.0f;
//	firstPtr[i * TILE_WIDTH + j].v[0] = speed * cos(theta);
//	firstPtr[i * TILE_WIDTH + j].v[1] = speed * sin(theta);
//	firstPtr[i * TILE_WIDTH + j].v[2] = 0.0;
//
//	firstPtr[i * TILE_WIDTH + j].launchV[0] = 0.0f;
//	firstPtr[i * TILE_WIDTH + j].launchV[1] = launchSpeed;
//	firstPtr[i * TILE_WIDTH + j].launchV[2] = 0.0f;
//
//	firstPtr[i * TILE_WIDTH + j].size = randNum / random_max * 5.0;
//
//	firstPtr[i * TILE_WIDTH + j].c[0] = r;
//	firstPtr[i * TILE_WIDTH + j].c[1] = g;
//	firstPtr[i * TILE_WIDTH + j].c[2] = b;
//
//	firstPtr[i * TILE_WIDTH + j].launch = true;
//	firstPtr[i * TILE_WIDTH + j].launchTime = time;
//	firstPtr[i * TILE_WIDTH + j].age = firstPtr[i * TILE_WIDTH + j].m + firstPtr[i * TILE_WIDTH + j].launchTime * 1.2;
//}


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

	cudaGraphicsGLRegisterBuffer(&cuda_pbo, gl_pbo, cudaGraphicsMapFlagsNone);

	// 4. 픽셀 버퍼를 CUDA 시스템에 매핑하고, 매핑된 GPU 주소(pDevImage)를 구함
	size_t size;
	cudaGraphicsMapResources(1, &cuda_pbo, NULL);
	cudaGraphicsResourceGetMappedPointer((void**)&pDevImage, &size, cuda_pbo);
	
	for (int i = 0; i < PSystem.size(); ++i) {
		glLineWidth(PSystem[i].size);
		glBegin(GL_LINE_STRIP);
		//glColor3d(PSystem[i].c[0] * 0.8, PSystem[i].c[1] * 0.8, PSystem[i].c[2] * 0.8);
		for (int j = 14; j > 0; j--) {
			glVertex3dv(PSystem[i].hist[j]);
		}
		glEnd();

		glPointSize(PSystem[i].size);
		glBegin(GL_POINTS);
		glColor3dv(PSystem[i].c);
		glVertex3dv(PSystem[i].x);
		glEnd();
	}
	glDrawPixels(Width, Height, GL_RGBA, GL_UNSIGNED_BYTE, 0);
	glFinish();

	// 5. GPU 리소스를 해제한다.
	cudaGraphicsUnmapResources(1, &cuda_pbo, NULL);
	cudaGraphicsUnregisterResource(cuda_pbo);

	glutSwapBuffers();
}

void Keyboard(unsigned char key, int x, int y) {
	if (key == 27) exit(1);
}