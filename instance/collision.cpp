#include "../stdafx.h"
#include "../render/sprite.h"
#include "collision.h"


collision::collision()
{
}


collision::~collision()
{
}
utils::usePoint collision::getPivotPoint(sprite ** sp) {
	utils::usePoint a = { 0,0 };
	a.x = (*sp)->g_x + (*sp)->pivot.x*(*sp)->getWidth();
	a.y = (*sp)->g_y + (*sp)->pivot.y*(*sp)->getHeight();
	return a;
};
utils::usePoint collision::getPivotLocal(sprite ** sp) {
	utils::usePoint a = { 0,0 };
	a.x = (*sp)->g_x-( (*sp)->g_x + (*sp)->pivot.x*(*sp)->getWidth());
	a.y = (*sp)->g_y - ((*sp)->g_y + (*sp)->pivot.y*(*sp)->getHeight());
	return a;
};
float collision::pointAngleInfo(const utils::usePoint point1, const utils::usePoint point2) {
	if (point2.x == point1.x&&point2.y == point1.y) {
		return 0;
	}
	if (point2.x>point1.x&&point2.y>point1.y) {//第一象限
		return atan((point2.y - point1.y) / (point2.x - point1.x)) / M_PI * 180.0f;
	}
	else if (point2.x<point1.x&&point2.y>point1.y) {
		return atan((point1.x - point2.x) / (point2.y - point1.y)) / M_PI * 180.0f + 90;
	}
	else if (point2.x<point1.x&&point2.y<point1.y) {
		return atan((point1.y - point2.y) / (point1.x - point2.x)) / M_PI * 180.0f + 180;
	}
	else if (point2.x>point1.x&&point2.y<point1.y) {
		return atan((point2.x - point1.x) / (point1.y - point2.y)) / M_PI * 180.0f + 270;
	}
	if (point2.x == point1.x&&point2.y>point1.y) {
		return 90;
	}
	else if (point2.x == point1.x&&point2.y<point1.y) {
		return 270;
	}
	else if (point2.x>point1.x&&point2.y == point1.y) {
		return 360;
	}
	else {
		return 180;
	}
};
float collision::getRotate(sprite ** sp) {
	utils::usePoint localPoint = this->getPivotLocal(sp);
	float angle = 0;
	if (localPoint.x>0 && localPoint.y == 0) {
		return 0;
	}
	else if (localPoint.y<0 && localPoint.x == 0) {
		return 90;
	}
	else if (localPoint.x<0 && localPoint.y == 0) {
		return 180;
	}else if (localPoint.x == 0 && localPoint.y>0) {
		return 270;
	}
	if (localPoint.x>0 && localPoint.y<0) {
		angle = atan(abs(localPoint.y) / abs(localPoint.x)) * 180.0f / M_PI;
	}
	else if (localPoint.x<0 && localPoint.y<0) {
		angle = atan(abs(localPoint.x) / abs(localPoint.y)) * 180.0f / M_PI + 90;
	}
	else if (localPoint.x<0 && localPoint.y>0) {
		angle = atan(abs(localPoint.y) / abs(localPoint.x)) * 180.0f / M_PI + 180;
	}
	else if (localPoint.x>0 && localPoint.y>0) {
		angle = atan(abs(localPoint.x) / abs(localPoint.y)) * 180.0f / M_PI + 270;
	}
	return round(angle);
};
utils::usePoint collision::getRotatePoint(sprite ** sp) {
	utils::usePoint a = { 0,0 };
	utils::usePoint getRotatePoint = this->getPivotPoint(sp);
	int newRotate = (((*sp)->angle % 360) + 360) % 360;
	a.x = ((*sp)->g_x - getRotatePoint.x)*cos((newRotate / 180.0f * M_PI)) - ((*sp)->g_y - getRotatePoint.y)*sin((newRotate / 180.0f * M_PI)) + getRotatePoint.x;
	a.y = ((*sp)->g_x - getRotatePoint.x)*sin((newRotate / 180.0f * M_PI)) + ((*sp)->g_y - getRotatePoint.y)*cos((newRotate / 180.0f * M_PI)) + getRotatePoint.y;
	return a;
};
utils::usePoint collision::getRotatePoint2(utils::usePoint getRotatePoint, utils::usePoint p2, int angle) {
	utils::usePoint a = { 0,0 };
	int newRotate = ((angle % 360) + 360) % 360;
	a.x = ((float)cos((newRotate / 180.0f) * M_PI))*(float)(p2.x - getRotatePoint.x) - (p2.y - getRotatePoint.y)*(float)(sin((newRotate / 180.0f * M_PI))) + (float)getRotatePoint.x;
	a.y = (float)(p2.x - getRotatePoint.x)*(float)(sin((newRotate / 180.0f * M_PI)) )+ (float)(p2.y - getRotatePoint.y)*(float)(cos((newRotate / 180.0f * M_PI))) + (float)getRotatePoint.y;
	
	a.x = round(a.x);
	a.y = round(a.y);
	return a;
};
utils::usePoint collision::transitionPoint(const utils::usePoint p1, const int x, const int y) {
	utils::usePoint a = { 0,0 };
	a.x = p1.x + x;
	a.y = p1.y + y;
	return a;
};
utils::usePoint collision::polarCoordinates(const utils::usePoint point, const int ale, const int distance) {
	float angle = (ale % 360 + 360) % 360;
	utils::usePoint p2 = { 0, 0 };
	if (angle>0 && angle<90) {
		p2.x = point.x + cos((angle * 2 * M_PI / 360.0f))*distance;
		p2.y = point.y + sin((angle * 2 * M_PI / 360.0f))*distance;
	}else if (angle>90 && angle<180) {
		p2.x = point.x - sin(((angle - 90) * 2 * M_PI / 360.0f))*distance;
		p2.y = point.y + cos(((angle - 90) * 2 * M_PI / 360.0f))*distance;
	}else if (angle>180 && angle<270) {
		p2.x = point.x - cos(((angle - 180) * 2 * M_PI / 360.0f))*distance;
		p2.y = point.y - sin(((angle - 180) * 2 * M_PI / 360.0f))*distance;
	}else if (angle>270 && angle<360) {
		p2.x = point.x + sin(((angle - 270) * 2 * M_PI / 360.0f))*distance;
		p2.y = point.y - cos(((angle - 270) * 2 * M_PI / 360.0f))*distance;
	}
	if (angle == 0 || angle == 360) {
		p2.x = point.x + distance;
		p2.y = point.y;
	}
	else if (angle == 90) {
		p2.x = point.x;
		p2.y = point.y + distance;
	}
	else if (angle == 180) {
		p2.x = point.x - distance;
		p2.y = point.y;
	}
	else if (angle == 270) {
		p2.x = point.x;
		p2.y = point.y - distance;
	}
	return p2;
};
vector <utils::usePoint> collision::getRotatePoints(sprite **sp) {
	vector <utils::usePoint> arr;
	arr.push_back(this->getRotatePoint(sp));
	arr.push_back(this->polarCoordinates(arr[0], (*sp)->angle, (*sp)->getWidth()));
	arr.push_back(this->polarCoordinates(arr[1], (*sp)->angle + 90, (*sp)->getHeight()));
	arr.push_back(this->polarCoordinates(arr[0], (*sp)->angle + 90, (*sp)->getHeight()));
	return arr;
};
float collision::getKeyMax(const vector <utils::usePoint> arr, const string key) {
	float max = 0;
	if (key == "x") {
		for (unsigned int i = 0;i < arr.size();i++) {
			if (i == 0) {
				max = arr[i].x;
			}
			if (arr[i].x > max) {
				max = arr[i].x;
			}
		}
	}
	else if (key == "y") {
		for (unsigned int i = 0;i < arr.size();i++) {
			if (i == 0) {
				max = arr[i].y;
			}
			if (arr[i].x > max) {
				max = arr[i].x;
			}
		}
	}
	return max;
}
float collision::getKeyMin(const vector <utils::usePoint> arr, const string key) {
	float max = 0;
	if (key == "x") {
		for (unsigned int i = 0;i < arr.size();i++) {
			if (i == 0) {
				max = arr[i].x;
			}
			if (arr[i].x < max) {
				max = arr[i].x;
			}
		}
	}
	else if (key == "y") {
		for (unsigned int i = 0;i < arr.size();i++) {
			if (i == 0) {
				max = arr[i].y;
			}
			if (arr[i].x < max) {
				max = arr[i].x;
			}
		}
	}
	return max;
}
bool collision::isXj(float a1, float a2, float b1, float b2) {

	if (a1 < a2 && b1 < b2) {
		if (a2 < b1 || a1 > b2) {
			return false;
		}
		else {
			return true;
		}
	}
};
void collision::getPoint1Arr(sprite **sp1, vector <utils::usePoint> &pointArr1) {
	utils::usePoint a1 = {
		-(*sp1)->getWidth()*(*sp1)->pivot.x,
		-(*sp1)->getHeight()*(*sp1)->pivot.y
	};
	utils::usePoint a2 = {
		-(*sp1)->getWidth()*(*sp1)->pivot.x+ (*sp1)->getWidth(),
		-(*sp1)->getHeight()*(*sp1)->pivot.y
	};
	utils::usePoint a3 = {
		-(*sp1)->getWidth()*(*sp1)->pivot.x + (*sp1)->getWidth(),
		-(*sp1)->getHeight()*(*sp1)->pivot.y + (*sp1)->getHeight()
	};
	utils::usePoint a4 = {
		-(*sp1)->getWidth()*(*sp1)->pivot.x,
		-(*sp1)->getHeight()*(*sp1)->pivot.y + (*sp1)->getHeight()
	};
	pointArr1.push_back(a1);
	pointArr1.push_back(a2);
	pointArr1.push_back(a3);
	pointArr1.push_back(a4);
}
bool collision::obbTest(sprite **sp1, sprite **sp2) {

	utils::usePoint globalPoint = this->getPivotPoint(sp1);
	vector <utils::usePoint> pointArr1;
	this->getPoint1Arr(sp1, pointArr1);
	vector <utils::usePoint> pointArr2 = this->getRotatePoints(sp2);

	for (unsigned int i = 0;i<pointArr2.size();i++) {
		pointArr2[i] = this->getRotatePoint2(globalPoint, pointArr2[i], -(*sp1)->angle);
		pointArr2[i] = this->transitionPoint(pointArr2[i], -globalPoint.x, -globalPoint.y);
	}

	utils::usePoint xdSp1 = {
		this->getKeyMin(pointArr1,"x"),
		this->getKeyMax(pointArr1,"x")
	};
	utils::usePoint xdSp2 = {
		this->getKeyMin(pointArr2,"x"),
		this->getKeyMax(pointArr2,"x")
	};

	utils::usePoint ydSp1 = {
		this->getKeyMin(pointArr1,"y"),
	    this->getKeyMax(pointArr1,"y")
	};
	utils::usePoint ydSp2 = {
		this->getKeyMin(pointArr2,"y"),
		this->getKeyMax(pointArr2,"y")
	};
	if (this->isXj(xdSp1.x, xdSp1.y, xdSp2.x, xdSp2.y) && this->isXj(ydSp1.x, ydSp1.y, ydSp2.x, ydSp2.y)) {
		return true;
	}
	else {
		return false;
	};
};
bool collision::obb(sprite **sp1, sprite ** sp2) {
	if (this->obbTest(sp1, sp2) && this->obbTest(sp2, sp1)) {
		return true;
	}
	else {
		return false;
	}
};