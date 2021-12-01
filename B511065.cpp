#include "pch.h"
#include "OpenGLView.h"
#include <iostream>
#include <vector>
#include <random>
using namespace std;
#include "B511065.h"

void B511065::DrawSphere()
{ 
	glBegin(GL_LINES); // x축
	glColor3f(0.0, 1.0, 0.0); // green
	glVertex3f(10.0, 0.0, 0.0);
	glVertex3f(-10.0, 0.0, 0.0);
	glEnd();

	glBegin(GL_LINES); // y축
	glColor3f(1.0, 0.0, 0.0); // red
	glVertex3f(0.0, -10.0, 0.0);
	glVertex3f(0.0, 10.0, 0.0);
	glEnd();

	glBegin(GL_LINES); // z축
	glColor3f(0.0, 0.0, 1.0); // blue
	glVertex3f(0.0, 0.0, -10.0);
	glVertex3f(0.0, 0.0, 10.0);
	glEnd();

	glBegin(GL_TRIANGLE_STRIP); // 삼각형 스트립을 이용해 전면부 사각형 그리기
	glColor3f(0.0, 1.0, 1.0);
	glVertex3f(0.01, -0, -0.5);
	glVertex3f(0.5, 0, -0.5);
	glVertex3f(0.01, 0, 0.75);
	glEnd();

	glBegin(GL_TRIANGLE_STRIP); // 삼각형 스트립을 이용해 전면부 사각형 그리기
	glColor3f(0.0, 1.0, 1.0);
	glVertex3f(-0.5, 0, -0.5);
	glVertex3f(-0.01, 0, -0.5);
	glVertex3f(-0.01, 0, 0.75);
	glEnd();

	glBegin(GL_TRIANGLE_STRIP); // 삼각형 스트립을 이용해 전면부 사각형 그리기
	glColor3f(0.0, 1.0, 1.0);
	glVertex3f(0, 0, 0.75);
	glVertex3f(0, 0, -0.5);
	glVertex3f(0, -0.5, -0.5);
	glEnd();

}

void B511065::Destroy()
{
	
}

void B511065::Initialize()
{
	std::random_device rd; 
	std::mt19937 mersenne(rd()); // Create a mersenne twister, seeded using the random device 
	std::uniform_int_distribution<> die(-500, 500);

	for (int i = 0; i < 1000; i++)
	{
		double x = die(mersenne), y = die(mersenne), z = die(mersenne);
		stars.push_back(Star(x, y, z));
	}
}

void B511065::Light()
{
	GLfloat light_pos[] = { 0.0, 0.0, 0.0, 1.0 }; // 1번 광원 포지션 0,0,0
	GLfloat light_ambient[] = { 0.0, 0.0, 0.0, 0.0 }; // 주변광 설정값

	glLightfv(GL_LIGHT0, GL_POSITION, light_pos);
	glLightfv(GL_LIGHT0, GL_AMBIENT, light_ambient);
	glEnable(GL_LIGHT0); // 0번 조명 사용

	GLfloat light_pos2[] = { 3.0, 3.0, 6.0, 1.0 };
	GLfloat light_diffus[] = { 0.0, 0.0, 0.0, 0.0 };

	glLightfv(GL_LIGHT4, GL_POSITION, light_pos2); // 2번 광원 포지션 3, 3, 6
	glLightfv(GL_LIGHT4, GL_AMBIENT, light_diffus); // 분산광 설정값
	glEnable(GL_LIGHT4); // 4번 조명 사용

	glEnable(GL_COLOR_MATERIAL); // 재질의 색을 폴리곤의 색으로  
	glEnable(GL_LIGHTING); // 조명 켜기    
}

void B511065::Spotlight()
{
	GLfloat light_spot_dir[] = { 0.0, 0.0, -1.0 }; // 스포트라이트 방향

	glLightfv(GL_LIGHT5, GL_SPOT_DIRECTION, light_spot_dir);
	glLightf(GL_LIGHT5, GL_SPOT_CUTOFF, 5); // 스포트라이트 절단 각도 5
	glLightf(GL_LIGHT5, GL_SPOT_EXPONENT, 1); // 스포트라이트 지수 1

	glEnable(GL_LIGHT5); // 3번 조명 사용
	glEnable(GL_COLOR_MATERIAL); // 재질의 색을 폴리곤의 색으로  
	glEnable(GL_LIGHTING); // 조명 켜기   
}

void B511065::ChangeCameraMode(int mode)
{
	if (mode > 2) return;

	Clear();
	cameraMode = mode;
}

void B511065::CameraMove(CPoint p)
{
	SetCameraRotateY((p.x - startPoint.x) / 100);
	SetCameraRotateX(-(p.y - startPoint.y) / 100);
}

void B511065::DrawStars()
{
	glPointSize(5.0f); // 점 크기 정하고
	glBegin(GL_POINTS); // 점 그리겠다

	for (const auto& star : stars) //
	{
		glColor3f(0.5f, 0.5f, 0.5f);
		glVertex3f(star.X, star.Y, star.Z);
	}
	
	glEnd();
}
