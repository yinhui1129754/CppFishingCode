#pragma once
class DemoApp;
class action;
class colVec;
class gold;
class fish;
class bullet
{
public:
	bullet();
	bullet(DemoApp * app, action * scene, colVec  * colObj, sprite * bt, sprite * wang,  int hurt =1, float speed=8);
	~bullet();
	void changeType(string type);//改变显示状态
	void moveForword();//向前移动
	int frameFun(vector<fish *>*fishArr);//每一帧调用
	void isTest(vector<fish *>*fishArr);
	void bullet::createGold(fish * fs);
	void bullet::setX(float x);
	void bullet::setY(float y);
	bool bullet::inScreen();
	utils::useSpSt st1;//子弹结构一
	utils::useSpSt st2;//鱼结构二
public:
	string bulletType = "bt";//子弹当前显示状态
	sprite * view;//视图精灵
	sprite * bt;//炮台精灵
	sprite * wang; //网精灵
	int hurt = 0;
	int w_time = 20;
	float speed = 0;
	float angle = 0;
	void (*removeScene)(bullet * b);
	sprite * scInfo;
private:
	DemoApp * app;//游戏app
	action * scene;//游戏场景
	colVec * colObj;//游戏碰撞对象
};

