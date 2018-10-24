#pragma once
//这是一个老版本的碰撞判断 已经淘汰
extern class sprite;
extern class collision
{
public:
	collision();
	~collision();
	//获取旋转中心相对于窗口坐标系
	utils::usePoint getPivotPoint(sprite ** sp);
	//获取精灵坐标左上角的位置
	utils::usePoint getPivotLocal(sprite ** sp);
	//获取旋转角度 相对于精灵坐标系
	float getRotate(sprite ** sp);
	//获取旋转过后精灵的左上角坐标
	utils::usePoint getRotatePoint(sprite ** sp);
	//获取旋转后的点
	utils::usePoint getRotatePoint2(utils::usePoint p1,utils::usePoint p2,int angle);
	//坐标位移
	utils::usePoint transitionPoint(utils::usePoint p1, int x, int y);
	//极坐标位移
	utils::usePoint polarCoordinates(utils::usePoint point,int angle,int distance);
	vector <utils::usePoint> getRotatePoints(sprite **sp);
	float getKeyMax(vector <utils::usePoint> arr,string key);
	float getKeyMin(vector <utils::usePoint> arr, string key);
	bool isXj(float a1, float a2, float b1, float b2);
	void collision::getPoint1Arr(sprite **sp1, vector <utils::usePoint> &pointArr1);
	bool obbTest(sprite **sp1, sprite ** sp2);
	bool obb(sprite **sp1, sprite ** sp2);
	float pointAngleInfo(utils::usePoint point1, utils::usePoint point2);
};

