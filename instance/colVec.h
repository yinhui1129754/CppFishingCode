#pragma once
class colVec
{
public:
	colVec();//构造函数
	~colVec();//析构函数
	bool colVec::obb(sprite **sp, sprite **sp2);//检查模式obb 
	bool colVec::obb(utils::useSpSt st1, utils::useSpSt st2);//检查模式obb 
	bool colVec::aabb(sprite **sp, sprite **sp2);//检查模式aabb 非向量模式
	void colVec::getShapePoints(sprite **sp,const int num);//获取形状的点
	void colVec::initVec();//将点转化为单位向量
	void colVec::getOneVec(const utils::usePoint &p1, const utils::usePoint &p2,int num);
	bool colVec::getVecProjection();//获取向量投影
	bool colVec::comparePoints(const int num);//对比点的信息判断是否碰撞
	void colVec::getSLCoordinateSystem(sprite **sp, const int num);//获取局部坐标系点信息未旋转
	void colVec::getShapePoints(const utils::useSpSt st, const int num);//以结构的形式获取点信息 方便预判断
	void colVec::getSLCoordinateSystem(const utils::useSpSt st, const int num);//以结构的形式获取点信息预判断
	void colVec::polarCoordinates(const utils::usePoint &p,float angle,float distance,utils::usePoint &cp);//极坐标位移
	float colVec::pointAngleInfo(const utils::usePoint point1, const utils::usePoint point2);//获取两点之间的角度
	float colVec::bezierCurve(float p0, float p1, float p2, float t); //贝塞尔曲线
private:
	vector <utils::usePoint> vec;//储存单位向量
	vector <vector<utils::usePoint>> points;//储存形状点的信息
	vector <utils::usePoint> proPoint;//投影的信息这里的点是储存的最大值和最小值
private:
	void colVec::clear(); //清空所有点的缓存
};

