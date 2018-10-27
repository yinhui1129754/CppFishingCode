#include "../stdafx.h"
#include "colVec.h"
//#include "frame0.h"

colVec::colVec()
{
	//分配预留点

	this->vec.resize(8);
	this->points.resize(2);
	this->points[0].resize(4);
	this->points[0][0] = { 0,0 };
	this->points[0][1] = { 0,0 };
	this->points[0][2] = { 0,0 };
	this->points[0][3] = { 0,0 };
	this->points[1].resize(4);
	this->points[1][0] = { 0,0 };
	this->points[1][1] = { 0,0 };
	this->points[1][2] = { 0,0 };
	this->points[1][3] = { 0,0 };
	this->proPoint.resize(8);
	for (int i = 0;i < 8;i++) {
		this->proPoint[i] = { 0,0 };
		this->vec[i] = { 0,0 };
	}
}


colVec::~colVec()
{
	this->clear();
}
float colVec::bezierCurve(float p0, float p1, float p2, float t) {
	return (1 - t)*(1 - t)*p0 + 2 * t*(1 - t)*p1 + t*t*p2;
}

void colVec::clear() {
	this->vec.clear();
	this->points[0].clear();
	this->points[1].clear();
	this->points.clear();
	this->proPoint.clear();
}
void colVec::getSLCoordinateSystem(sprite **sp, const int num) {
	utils::usePoint &l_a = this->points[num][0];
	sprite l_sp = **sp;
	l_a.x = l_sp.g_x + l_sp.pivot.x*l_sp.getWidth();
	l_a.y = l_sp.g_y + l_sp.pivot.y*l_sp.getHeight();
};
void colVec::getSLCoordinateSystem(const  utils::useSpSt st, const int num) {
	utils::usePoint &l_a = this->points[num][0];
	utils::useSpSt  l_sp = st;
	l_a.x = l_sp.x + l_sp.pivotX*l_sp.width;
	l_a.y = l_sp.y + l_sp.pivotY*l_sp.height;
};
void colVec::getShapePoints(sprite **sp, const int num) {
	float l_o = (*sp)->angle * M_PI / 180.0f;//角度转化为弧度
	float l_sin = sin(l_o);
	float l_cos = cos(l_o);
	sprite l_sp = **sp;
	
	//转化旋转后的点
	this->getSLCoordinateSystem(sp, num);
	utils::usePoint &l_a = this->points[num][0];
	float l_x = (l_sp.g_x - l_a.x);
	float l_y = (l_sp.g_y - l_a.y);
	l_a.x = (l_x*l_cos - l_y*l_sin + l_a.x);
	l_a.y = (l_x*l_sin+ l_y*l_cos+ l_a.y);

	this->polarCoordinates(l_a, l_sp.angle, l_sp.getWidth(), this->points[num][1]);
	this->polarCoordinates(this->points[num][1], l_sp.angle+90, l_sp.getHeight(), this->points[num][2]);

	this->polarCoordinates(l_a, l_sp.angle+90, l_sp.getHeight(), this->points[num][3]);
	/*测试用代码查看点是否获取正确*/
	/*frame0::p1.push_back(this->points[num][0]);
	frame0::p1.push_back(this->points[num][1]);
	frame0::p1.push_back(this->points[num][2]);
	frame0::p1.push_back(this->points[num][3]);*/
};
void colVec::getShapePoints(const utils::useSpSt st,const int num) {
	float l_o = st.angle * M_PI / 180.0f;//角度转化为弧度
	float l_sin = sin(l_o);
	float l_cos = cos(l_o);
	utils::useSpSt  l_sp = st;

	//转化旋转后的点
	this->getSLCoordinateSystem(l_sp, num);
	utils::usePoint &l_a = this->points[num][0];
	float l_x = (l_sp.x - l_a.x);
	float l_y = (l_sp.y - l_a.y);
	l_a.x = (l_x*l_cos - l_y*l_sin + l_a.x);
	l_a.y = (l_x*l_sin + l_y*l_cos + l_a.y);

	this->polarCoordinates(l_a, l_sp.angle, l_sp.width, this->points[num][1]);
	this->polarCoordinates(this->points[num][1], l_sp.angle + 90, l_sp.height, this->points[num][2]);
	this->polarCoordinates(l_a, l_sp.angle + 90, l_sp.height, this->points[num][3]);
	/*测试用代码查看点是否获取正确*/
	/*frame0::p1.push_back(this->points[num][0]);
	frame0::p1.push_back(this->points[num][1]);
	frame0::p1.push_back(this->points[num][2]);
	frame0::p1.push_back(this->points[num][3]);*/
};
void colVec::initVec() {
	unsigned int len = this->points[0].size()-1;
	unsigned int len2 = len + 1;
	unsigned int len3 = this->points[1].size();
	unsigned int i = 0;
	for (i = 0;i < len;i++) {
		this->getOneVec(this->points[0][i], this->points[0][i+1],i);
		this->getOneVec(this->points[1][i], this->points[1][i + 1], i+len2);
	}

	this->getOneVec(this->points[0][len], this->points[0][0], len);
	this->getOneVec(this->points[1][len], this->points[1][0], len + len3);
};
void colVec::getOneVec(const utils::usePoint &p1,const utils::usePoint &p2, int num) {
	float l_m = 0;
	this->vec[num].x = p1.x - p2.x;
	this->vec[num].y = p1.y - p2.y;
	l_m = sqrt(pow(this->vec[num].x, 2) + pow(this->vec[num].y, 2));
	this->vec[num].x = this->vec[num].x / l_m;
	this->vec[num].y = this->vec[num].y / l_m;

};
void colVec::polarCoordinates(const utils::usePoint &p, float angle, float distance, utils::usePoint &cp) {
	float l_o = angle*M_PI / 180;
	cp.x = p.x + cos(l_o)*distance;
	cp.y = p.y + sin(l_o)*distance;
};
bool colVec::getVecProjection() {
	unsigned int len = this->vec.size();
	for (unsigned int i = 0;i < len;i++) {
		if (!this->comparePoints(i)) {
			return false;
		};
	}
	return true;
};
bool colVec::comparePoints(const int num) {
	unsigned int l_i = 0;
	unsigned int len = this->points[0].size();
	unsigned int len2 = this->points[1].size();
	float min1 = 0;
	float max1 = 0;
	float min2 = 0;
	float max2 = 0;
	float c_B = 0;
	for (l_i = 0;l_i < len;l_i++) {
		c_B = this->points[0][l_i].x * this->vec[num].x + this->points[0][l_i].y * this->vec[num].y;
		if (c_B < min1||l_i==0) {
			min1 = c_B;
		}
		if (c_B > max1 || l_i == 0) {
			max1 = c_B;
		}
		c_B = this->points[1][l_i].x * this->vec[num].x + this->points[1][l_i].y * this->vec[num].y;
		if (c_B < min2 || l_i == 0) {
			min2 = c_B;
		}
		if (c_B > max2 || l_i == 0) {
			max2 = c_B;
		}
	}
	return max1 >min2 && max2> min1;
};
bool colVec::obb(sprite **sp, sprite **sp2) {

	this->getShapePoints(sp, 0);
	this->getShapePoints(sp2, 1);
	this->initVec();

	return this->getVecProjection();
};
bool colVec::obb(utils::useSpSt st1, utils::useSpSt st2) {

	this->getShapePoints(st1, 0);
	this->getShapePoints(st2, 1);
	this->initVec();

	return this->getVecProjection();
};
float colVec::pointAngleInfo(const utils::usePoint point1, const utils::usePoint point2) {
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
}
bool colVec::aabb(sprite **sp, sprite **sp2) {
	sprite l_sp1 = **sp;
	sprite l_sp2 = **sp2;
	if (l_sp1.x < l_sp2.x + l_sp2.width &&
		l_sp1.x + l_sp1.width > l_sp2.x &&
		l_sp1.y < l_sp2.y + l_sp2.height &&
		l_sp1.height + l_sp1.y > l_sp2.y) {
		return true;
	}else {
		return false;
	}
};