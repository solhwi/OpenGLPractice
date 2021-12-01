#pragma once

#include <iostream>
#include <vector>
#include <random>
using namespace std;

class Star
{
public:
	float X = 0, Y = 0, Z = 0;
	Star() {};
	Star(float x, float y, float z) : X(x), Y(y), Z(z){}
};

class B511065
{
public:
	void DrawSphere();
	void Destroy();
	void Initialize();
	void Light();
	void Spotlight();

	void ChangeCameraMode(int mode);
	void SetCameraPos(double x, double y, double z) 
	{
		this->posX = x;
		this->posY = y;
		this->posZ = z;
	}

	void SetCameraRotateX(double d)
	{
		rotationX -= d;
	}

	void SetCameraRotateY(double d)
	{
		rotationY += d;
	}

	void SetCameraRotateZ(double d)
	{
		rotationZ -= d;
	}

	void SetLocation(double x = 0, double y = 0, double z = 0)
	{
		locationX = x;
		locationY = y;
		locationZ = z;
	}

	void CameraMove(CPoint p);

	void DrawStars();

	void Clear()
	{
		locationX = 0, locationY = 0, locationZ = 0;
		
		isCameraRotate = false;

		speed = 0;
	}

public:
	int cameraMode = 0;
	double posX = 6, posY = 3, posZ = 3;
	double rotationX = 0, rotationY = 0, rotationZ = 0;
	double locationX = 0, locationY = 0, locationZ = 0;

	CPoint startPoint;
	bool isCameraRotate = false;

	double speed = 0;
	vector<Star> stars;
};

