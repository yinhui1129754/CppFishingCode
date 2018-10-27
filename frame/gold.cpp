#include "../stdafx.h"
#include "frame1.h"
#include "gold.h"


gold::gold()
{
	this->t = 0;
}

gold::gold(sprite * view) {
	this->view = view;
	this->t = 0;
};
gold::~gold()
{
}
void gold::getCenterPoint() {
	this->centerPoint.x = (this->endPoint.x - this->startPoint.x) / 2;
	this->centerPoint.y = (this->endPoint.y - this->startPoint.y) / 2;
	float angle = frame1::colObj->pointAngleInfo(this->startPoint, this->endPoint);
	int distance = 150;
	if (random() >= 0.5) {
		angle = angle - 90;
		distance = -150;
	}
	else {
		angle = angle + 90;
	}
	utils::usePoint buf;
	frame1::colObj->polarCoordinates(this->centerPoint, angle, 150, buf);
	this->centerPoint.x = buf.x;
	this->centerPoint.y = buf.y;
};
void gold::setX(float x) {
	this->view->setX(x);
}
void gold::setY(float y) {
	this->view->setY(y);
};
void gold::frameFun() {

	/*bool b1 = false;
	bool b2 = false;
	if (this->view->g_x <= this->endPoint.x-50) {
		this->view->setX((this->view->g_x + 5));
	}
	else if (this->view->g_x >= this->endPoint.x + 50) {
		this->view->setX((this->view->g_x - 5));
	}
	else {
		b1 = true;
	}
	if (this->view->g_y <= this->endPoint.y - 50) {
		this->view->setY(this->view->g_y + 5);
	}
	else if (this->view->g_y >= this->endPoint.y + 50) {
		this->view->setY(this->view->g_y - 5);
	}
	else {
		b2 = true;
	}
		if (b1 == true && b2 == true) {
		this->removeScren(this);
	}*/

	if (this->t <= 1) {
		this->t += 0.01;
		float x = frame1::colObj->bezierCurve(this->startPoint.x, this->centerPoint.x, this->endPoint.x, this->t);
		float y = frame1::colObj->bezierCurve(this->startPoint.y, this->centerPoint.y, this->endPoint.y, this->t);
		this->setX(x);
		this->setY(y);
	}
	else {
		this->removeScren(this);
	}
};