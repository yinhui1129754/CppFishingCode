#pragma once
class action;
class DemoApp;
class colVec;
class bullet;
class fish;
class gold;
class files;
class fishConfig;
namespace frame1 {
	extern action * scene;//当前场景的场景对象
	extern DemoApp * app;//游戏app
	extern colVec *colObj;//碰撞对象 提供obb  aabb 相关碰撞算法 <obb 采用向量>

	extern float zoom;//场景所有精灵用的zoom
	extern int nowScane;//当前关数
	extern int nowPt;//当前炮台的显示
	extern oMap<string, sprite *> bottom;//底部精灵组合
	extern ticker * tk1; //场景计时器
	extern float timerFish;//周期判断鱼是否游出屏幕
	extern int usegold;
	extern files * saveObj;
	extern sprite * bk;

	extern vector<sprite *> jbNum;
	extern vector<sprite * > bgArr;//所有关数的背景 
	extern vector<sprite * > ptArr;//炮台Arr
	extern vector<sprite * > bulletArr;//子弹Arr Img
	extern vector<bullet * > bulletArr2;//子弹Arr
	extern vector<sprite * > bulletWang;//子弹Arr Img
	extern vector <fish *> fishArr;//鱼数组
	extern vector <fishConfig *>fishConfigArr;//创建鱼的对象数组
	extern vector <gold *> goldArr;
	extern bool isDown; //在触发鼠标抬起事件之前是否在切换炮台按钮里面按下了鼠标 如果是就为true否则为false
	extern DisplayObject * maxBox;//最大容器
	extern DisplayObject * bottomBox;//底部容器
	extern DisplayObject * fishBox; //鱼群容器
	extern sprite * addBtn;//切换炮台 加
	extern sprite * subtractBtn;//切换炮台 减
	extern  void drawGoldNum();
	extern void init(DemoApp ** app, colVec ** colObj);//场景初始化调用
	extern void visible();//场景显示调用
	extern void onClick(int x, int y);//场景点击事件
	extern void onClose();//场景点击事件
	extern void onMouseDown(int x, int y);//场景鼠标按下事件
	//extern void onMouseUp(int x, int y);//场景鼠标抬起事件
	extern void onKeyUp(int x);//场景点击事件
	extern void initPt();//初始炮台
	extern void initPt2();//初始化炮台位置
	extern sprite* initAmt1(LPWSTR url,int w,int h,int frame,float zoom=1);//初始化单帧动画
	extern void initAmt2(sprite * v,int startY, int w, int h, int frame, float zoom);
	extern DWORD WINAPI tk1Fun();//计时器每一帧调用函数
	extern void tk1FunC(DemoApp ** app, ticker *tk);
	extern void mouseMove(int x,int y);//鼠标移动触发函数
	extern void frameSpriteInfo(sprite ** sp, int type);
	extern void removeBullet(bullet * bt);//排泄子弹
	extern void removeFish(fish * b);//排泄鱼
	extern void removeGold(gold * b);//排泄金币
	extern float allPower;
	extern float nowPower;
	extern HANDLE  hThred;
	extern 	fishConfig *  initFishConfig(LPWSTR url,int swimY,int w,int h ,int swimNum,int deathY,int deathNum,int getGold,int maxFish = 30,int deathInt=10);//初始化创建鱼对象
}