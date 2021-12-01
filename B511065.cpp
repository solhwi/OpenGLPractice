#include "pch.h"
#include "OpenGLView.h"
#include <iostream>
#include <vector>
#include <random>
using namespace std;
#include "B511065.h"

void B511065::DrawSphere()
{ 
	glBegin(GL_LINES); // x��
	glColor3f(0.0, 1.0, 0.0); // green
	glVertex3f(10.0, 0.0, 0.0);
	glVertex3f(-10.0, 0.0, 0.0);
	glEnd();

	glBegin(GL_LINES); // y��
	glColor3f(1.0, 0.0, 0.0); // red
	glVertex3f(0.0, -10.0, 0.0);
	glVertex3f(0.0, 10.0, 0.0);
	glEnd();

	glBegin(GL_LINES); // z��
	glColor3f(0.0, 0.0, 1.0); // blue
	glVertex3f(0.0, 0.0, -10.0);
	glVertex3f(0.0, 0.0, 10.0);
	glEnd();

	glBegin(GL_TRIANGLE_STRIP); // �ﰢ�� ��Ʈ���� �̿��� ����� �簢�� �׸���
	glColor3f(0.0, 1.0, 1.0);
	glVertex3f(0.01, -0, -0.5);
	glVertex3f(0.5, 0, -0.5);
	glVertex3f(0.01, 0, 0.75);
	glEnd();

	glBegin(GL_TRIANGLE_STRIP); // �ﰢ�� ��Ʈ���� �̿��� ����� �簢�� �׸���
	glColor3f(0.0, 1.0, 1.0);
	glVertex3f(-0.5, 0, -0.5);
	glVertex3f(-0.01, 0, -0.5);
	glVertex3f(-0.01, 0, 0.75);
	glEnd();

	glBegin(GL_TRIANGLE_STRIP); // �ﰢ�� ��Ʈ���� �̿��� ����� �簢�� �׸���
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
	GLfloat light_pos[] = { 0.0, 0.0, 0.0, 1.0 }; // 1�� ���� ������ 0,0,0
	GLfloat light_ambient[] = { 0.0, 0.0, 0.0, 0.0 }; // �ֺ��� ������

	glLightfv(GL_LIGHT0, GL_POSITION, light_pos);
	glLightfv(GL_LIGHT0, GL_AMBIENT, light_ambient);
	glEnable(GL_LIGHT0); // 0�� ���� ���

	GLfloat light_pos2[] = { 3.0, 3.0, 6.0, 1.0 };
	GLfloat light_diffus[] = { 0.0, 0.0, 0.0, 0.0 };

	glLightfv(GL_LIGHT4, GL_POSITION, light_pos2); // 2�� ���� ������ 3, 3, 6
	glLightfv(GL_LIGHT4, GL_AMBIENT, light_diffus); // �л걤 ������
	glEnable(GL_LIGHT4); // 4�� ���� ���

	glEnable(GL_COLOR_MATERIAL); // ������ ���� �������� ������  
	glEnable(GL_LIGHTING); // ���� �ѱ�    
}

void B511065::Spotlight()
{
	GLfloat light_spot_dir[] = { 0.0, 0.0, -1.0 }; // ����Ʈ����Ʈ ����

	glLightfv(GL_LIGHT5, GL_SPOT_DIRECTION, light_spot_dir);
	glLightf(GL_LIGHT5, GL_SPOT_CUTOFF, 5); // ����Ʈ����Ʈ ���� ���� 5
	glLightf(GL_LIGHT5, GL_SPOT_EXPONENT, 1); // ����Ʈ����Ʈ ���� 1

	glEnable(GL_LIGHT5); // 3�� ���� ���
	glEnable(GL_COLOR_MATERIAL); // ������ ���� �������� ������  
	glEnable(GL_LIGHTING); // ���� �ѱ�   
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
	glPointSize(5.0f); // �� ũ�� ���ϰ�
	glBegin(GL_POINTS); // �� �׸��ڴ�

	for (const auto& star : stars) //
	{
		glColor3f(0.5f, 0.5f, 0.5f);
		glVertex3f(star.X, star.Y, star.Z);
	}
	
	glEnd();
}
