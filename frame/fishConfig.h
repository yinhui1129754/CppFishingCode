#pragma once
class fish;
class fishConfig
{
public:
	fishConfig();
	fishConfig(DemoApp * app, action * scene, colVec * colObj,sprite * img, void(*removeScene)(fish * b));//构造函数
	~fishConfig();//析构函数
	void setFishFrame(fish * fs, int startY, int w, int h, int num, int type, float zoom = 1);//设置鱼的帧信息
	void createFish(vector<fish *> * fishArr, DisplayObject *ds);//创建鱼
	void frameFun(vector<fish *> * fishArr, DisplayObject *ds);//每一帧fishConfig应该做的操作
	void fishConfig::setType(fish* l_fs, int type,int setType);//随机获取一种鱼出现的类型并进行相关解释
	void(*removeScene)(fish * b);//移出创建鱼进行的操作
public:
	int createNum = 4;//一次创建创建的鱼的数量
	int getGold = 2;//这种鱼死亡的时候创建的金币
	int createTimmerInt = 0;//创建时间相关
	int startYSwim = 0;//这种鱼游泳开始帧的位置
	int startYDeath= 0;//这种鱼死亡开始帧的位置
	int swimNum = 0;//这种鱼游泳的帧数
	int deathNum = 0;//这种鱼死亡的帧数
	vector<fish * > fishConfigArr;//缓存创建的鱼的数组
	int maxFish = 30; //这种类型的鱼创建的最大数量
	int fishW = 0;//这种类型的鱼的宽度
	int fishH = 0;//这种类型的鱼的高度
	int deathInt = 10;//设置鱼的死亡概率 越大越不容易死 不能大于100
	float speed = 2;//设置鱼的速度
	float zoom=1;//这种类型的鱼的缩放
private:
	sprite * img;//储存图片的精灵
	int createTimmer = 30;//创建时间间隔
	int createAllTimmer = 30;//创建总时间
	DemoApp * app;//游戏app对象
	action * scene;//场景对象
	colVec * colObj;//碰撞对象
	vector <vector<int>> type1;//处理鱼的角度信息
};

