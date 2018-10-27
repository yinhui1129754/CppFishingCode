#include "../stdafx.h"
#include"bullet.h"
#include "fish.h"
#include "fishConfig.h"
#include "gold.h"
#include "frame1.h"
#include "files.h"
//action * frame0::scene = NULL;
action *frame1::scene = NULL;
DemoApp * frame1::app = NULL;
colVec * frame1::colObj = NULL;
DisplayObject * frame1::maxBox = NULL;
DisplayObject * frame1::bottomBox = NULL;
DisplayObject * frame1::fishBox = NULL;
sprite * frame1::addBtn = NULL;
sprite * frame1::subtractBtn = NULL;
float frame1::zoom =1;
int frame1::nowScane = 0;
int frame1::nowPt = 0;
ticker * frame1::tk1 = NULL;
sprite * frame1::bk = NULL;
vector<sprite * >frame1::bgArr;
float frame1::timerFish = 0;
files * frame1::saveObj = new files();
vector<sprite * >frame1::ptArr;
vector<sprite * >frame1::bulletArr;
vector<bullet * >frame1::bulletArr2;
vector<fish *> frame1::fishArr;
vector<fishConfig *>frame1::fishConfigArr;
vector<sprite * >frame1::bulletWang;
oMap<string, sprite *> frame1::bottom;
HANDLE  frame1::hThred;
float frame1::allPower = 100;
float frame1::nowPower = 0;
vector <gold *> frame1::goldArr;
bool frame1::isDown = false;

int frame1::usegold = 0;
vector<sprite *> frame1::jbNum;
void frame1::init(DemoApp ** app, colVec ** colObj) {
	frame1::scene = new action(*app);
	frame1::app = *app;
	frame1::colObj = *colObj;
	frame1::tk1 = new ticker();


	frame1::scene->addTicker(frame1::tk1);
	frame1::tk1->addFun(frame1::tk1FunC);
	//添加点击事件
	(*app)->use_onClick["frame1"] = frame1::onClick;
	(*app)->use_onMouseMove["frame1"] = frame1::mouseMove;
	(*app)->use_onKeyUp["frame1"] = frame1::onKeyUp;
	(*app)->use_onMouseDown["frame1"] = frame1::onMouseDown;
	(*app)->use_onClose["frame1"] = frame1::onClose;
	frame1::hThred = CreateThread(NULL, 0, (LPTHREAD_START_ROUTINE)frame1::tk1Fun, NULL, CREATE_SUSPENDED, NULL);
	if (frame1::hThred == NULL) {
		MessageBox(NULL, L"asd", L"asd", MB_OK);
	}
	
	//初始容器
	frame1::maxBox = new DisplayObject(0, 0);
	frame1::bottomBox = new DisplayObject(0, 0);
	frame1::fishBox = new DisplayObject(0, 0);
	scene->addChild((sprite*)frame1::maxBox);
	frame1::maxBox->addChild((sprite*)frame1::fishBox);
	frame1::maxBox->addChild((sprite*)frame1::bottomBox);
	frame1::bottom["yin"] = new sprite(*app,L"img/glod/coinAni1.png");
	frame1::bottom["jin"] = new sprite(*app,L"img/glod/coinAni2.png");
	frame1::bottom["pdSend"] = new sprite(*app, L"img/pwoerPd/pd.png");
	frame1::bottom["pdBoom"] = new sprite(*app, L"img/pwoerPd/cl.png");
	frame1::bottom["bar"] = new sprite(*app, L"img/Interface/energy-bar.png");
	frame1::saveObj->getFile(L"_save.sva");
	frame1::saveObj->readFile();
	if (frame1::saveObj->s == "") {
		frame1::usegold = 1000;
	}
	else {
		frame1::usegold = frame1::saveObj->num;
	}
	
	//设置场景
	frame1::bgArr.push_back(new sprite(*app,L"img/Interface/1a.jpg"));
	frame1::bgArr.push_back(new sprite(*app,L"img/Interface/1b.jpg"));
	frame1::bgArr.push_back(new sprite(*app,L"img/Interface/1c.jpg"));
	frame1::bgArr.push_back(new sprite(*app,L"img/Interface/1d.jpg"));
	frame1::bgArr.push_back(new sprite(*app,L"img/Interface/1e.jpg"));
	frame1::bgArr.push_back(new sprite(*app,L"img/Interface/1f.jpg"));
	//炮台
	frame1::ptArr.push_back(frame1::initAmt1(L"img/bullet/cannon1.png", 74, 74, 5));
	frame1::ptArr.push_back(frame1::initAmt1(L"img/bullet/cannon2.png", 74, 76, 5));
	frame1::ptArr.push_back(frame1::initAmt1(L"img/bullet/cannon3.png", 74, 76, 5));
	frame1::ptArr.push_back(frame1::initAmt1(L"img/bullet/cannon4.png", 74, 83, 5));
	frame1::ptArr.push_back(frame1::initAmt1(L"img/bullet/cannon5.png", 74, 85, 5));
	frame1::ptArr.push_back(frame1::initAmt1(L"img/bullet/cannon6.png", 74, 90, 5));
	frame1::ptArr.push_back(frame1::initAmt1(L"img/bullet/cannon7.png", 74, 94, 5));
	//子弹
	frame1::bulletArr.push_back(new sprite(*app, L"img/bullet/bullet1.png"));
	frame1::bulletArr.push_back(new sprite(*app, L"img/bullet/bullet2.png"));
	frame1::bulletArr.push_back(new sprite(*app, L"img/bullet/bullet3.png"));
	frame1::bulletArr.push_back(new sprite(*app, L"img/bullet/bullet4.png"));
	frame1::bulletArr.push_back(new sprite(*app, L"img/bullet/bullet5.png"));
	frame1::bulletArr.push_back(new sprite(*app, L"img/bullet/bullet6.png"));
	frame1::bulletArr.push_back(new sprite(*app, L"img/bullet/bullet7.png"));
	//网
	frame1::bulletWang.push_back(new sprite(*app, L"img/bullet/web1s.png"));
	frame1::bulletWang.push_back(new sprite(*app, L"img/bullet/web2s.png"));
	frame1::bulletWang.push_back(new sprite(*app, L"img/bullet/web3s.png"));
	frame1::bulletWang.push_back(new sprite(*app, L"img/bullet/web4s.png"));
	frame1::bulletWang.push_back(new sprite(*app, L"img/bullet/web5s.png"));
	frame1::bulletWang.push_back(new sprite(*app, L"img/bullet/web6s.png"));
	frame1::bulletWang.push_back(new sprite(*app, L"img/bullet/web7s.png"));

	//鱼 
	frame1::initFishConfig(L"img/fish/fish1.png",0,55,37,4, 4 * 37,4,2,15);
	frame1::initFishConfig(L"img/fish/fish2.png", 0, 78, 64, 4, 4 * 64, 4,8,15);
	frame1::initFishConfig(L"img/fish/fish3.png", 0, 72, 56, 4, 4 * 56, 4, 30,4,55);
	frame1::initFishConfig(L"img/fish/fish4.png", 0, 77, 59, 4, 4 * 59, 4, 20, 5, 40);
	frame1::initFishConfig(L"img/fish/fish5.png", 0, 107, 122, 4, 4 * 122, 4, 15, 5, 30);
	frame1::initFishConfig(L"img/fish/fish6.png", 0, 105, 79, 8, 8 * 79, 4, 25, 5, 55);
	frame1::initFishConfig(L"img/fish/fish7.png", 0, 92, 151, 6, 6 * 151, 4, 45, 3, 75);
	frame1::initFishConfig(L"img/fish/fish8.png", 0, 174, 126, 8, 8 * 126, 4, 60, 3, 85);
	frame1::initFishConfig(L"img/fish/fish10.png", 0, 178, 187, 6, 6 * 187, 4, 80, 2, 94);
	frame1::initFishConfig(L"img/fish/fish9.png", 0, 166, 183, 8, 8 * 183, 4, 70, 2, 90);
	frame1::initFishConfig(L"img/fish/shark1.png", 0, 509, 270, 8, 8 * 270, 4, 90, 2, 95);
	frame1::initFishConfig(L"img/fish/shark2.png", 0, 516, 273, 8, 8 * 273, 4, 100, 1, 96);
	frame1::initFishConfig(L"img/fish/fish12.png", 0, 215, 211, 14, 14 * 211, 1, 110, 1, 97);
	frame1::initFishConfig(L"img/fish/fish11.png", 0, 274,100, 32, 32 * 100, 1, 120, 1, 98);
}
//地址 游泳开始帧的y 宽度 高度 游泳帧数量 死亡开始帧Y 死亡帧的数量 获得的金币
fishConfig *  frame1::initFishConfig(LPWSTR url, int swimY, int w, int h, int swimNum, int deathY, int deathNum,int getGold, int maxFish, int deathInt) {
	fishConfig * fc1 = new fishConfig(
		frame1::app, frame1::scene, frame1::colObj,
		new sprite(frame1::app, url),
		frame1::removeFish
	);
	frame1::fishConfigArr.push_back(fc1);
	fc1->startYSwim = swimY;
	fc1->fishW = w;
	fc1->fishH = h;
	fc1->swimNum = swimNum;
	fc1->startYDeath = deathY;
	fc1->deathNum = deathNum;
	fc1->getGold = getGold;
	fc1->maxFish = maxFish;
	fc1->deathInt = deathInt;
	return fc1;
};
void frame1::visible() {
	
	frame1::fishBox->addChild(frame1::bgArr[frame1::nowScane]);
	frame1::bgArr[frame1::nowScane]->width = frame1::app->width;
	frame1::bgArr[frame1::nowScane]->height = frame1::app->height;

	if (frame1::jbNum.size() == 0) {

		//背景
		
		frame1::bk = new sprite(frame1::app, L"img/Interface/back.png");
		frame1::bk->setId("back");
		frame1::maxBox->addChild(frame1::bk);
		frame1::bk->setX(15);
		frame1::bk->setY(20);
		frame1::bk->zoom = 0.5;
		//炮台
		frame1::initPt();
		for (int i = 0;i < 10;i++) {
			sprite * l_spInit = new sprite(frame1::app, L"img/glod/coinText.png");
			frame1::jbNum.push_back(l_spInit);
			u_rect * rc = new u_rect();
			rc->x = 0;
			rc->y = 0;
			rc->width = 36;
			rc->height = 49;
			l_spInit->frame = rc;
			l_spInit->width = 36;
			l_spInit->height = 49;
			frame1::bottomBox->addChild(l_spInit);
			l_spInit->zoom = 0.5;
			l_spInit->setX((136 - i * 24));
			l_spInit->setY(45);
		}
	}

	//启动计时器
	frame1::tk1->start();
	ResumeThread(frame1::hThred);
};
void frame1::initPt() {
	sprite * bg = new sprite(frame1::app, L"img/Interface/bottom-bar.png");
	frame1::addBtn = new sprite(frame1::app, L"img/Interface/cannon_plus.png");
	frame1::subtractBtn = new sprite(frame1::app, L"img/Interface/cannon_minus.png");
	
	bg->zoom = frame1::zoom;
	bg->setId("ptBg");
	frame1::bottomBox->addChild(bg);
	frame1::bottomBox->setX(frame1::app->width/2-bg->getWidth()/2);
	frame1::bottomBox->setY(frame1::app->height-bg->getHeight());
	frame1::bottomBox->addChild(frame1::bottom["bar"]);
	frame1::bottom["bar"]->setX(543);
	frame1::bottom["bar"]->setY(44);
	frame1::bottomBox->addChild(frame1::addBtn);
	frame1::bottomBox->addChild(frame1::subtractBtn);
	frame1::initPt2();
}
void frame1::initPt2() {
	frame1::bottom["pt"] = frame1::ptArr[frame1::nowPt];
	frame1::bottom["bullet"] = frame1::bulletArr[frame1::nowPt];
	frame1::bottom["wang"] = frame1::bulletWang[frame1::nowPt];
	frame1::bottomBox->addChild(frame1::bottom["pt"]);
	frame1::bottom["pt"]->pivot.y = 1;
	frame1::bottom["pt"]->setX((frame1::bottomBox->getChildById("ptBg"))->getWidth() / 2 + frame1::bottom["pt"]->getWidth() / 100 * 10);

	frame1::addBtn->setX(frame1::bottom["pt"]->x + frame1::bottom["pt"]->getWidth()/2 - frame1::addBtn->getWidth()/2+100);
	frame1::subtractBtn->setX(frame1::bottom["pt"]->x + frame1::bottom["pt"]->getWidth() / 2 - frame1::addBtn->getWidth() / 2 - 100);
	frame1::addBtn->setY(frame1::bottomBox->getChildById("ptBg")->getHeight()/3+10);
	frame1::subtractBtn->setY(frame1::bottomBox->getChildById("ptBg")->getHeight()/3+10);

}
sprite *  frame1::initAmt1(LPWSTR url, int w, int h,int frame, float zoom) {
		sprite * amtTest = new sprite(frame1::app, url);
		amtTest->width = w;
		amtTest->height = h;
		amtTest->zoom = zoom;
		amtTest->speedTime = 50;
		amtTest->spriteType = "animateSprite";
		for (int i = 0;i < frame;i++) {
			u_rect a = { 0,h*i,w,h};
			amtTest->frameArr.push_back(a);
		}
		return amtTest;
};
void frame1::initAmt2(sprite * v,int startY, int w, int h, int frame, float zoom) {
	vector<u_rect> arr;
	v->width = w;
	v->height = h;
	v->spriteType = "animateSprite";
	v->speedTime = 50;
	v->zoom = zoom;
	for (int i = 0;i < frame;i++) {
		u_rect a = { 0,h*i,w,h };
		arr.push_back(a);
	}
	v->frameArr = arr;
};
void frame1::drawGoldNum() {
	string a1 = g_concat(frame1::usegold, "");

	int len = a1.length();
	if (len > 6) {
		for (int d = 6;d < len;d++) {
			frame1::jbNum[d]->visible = true;
		}
	}
	else {
		for (int d = 6;d < 10;d++) {
			frame1::jbNum[d]->visible = false;
		}
	}
	for (int i = len - 1,  q = 0;i >= 0;i--,q++) {
		int a2 = a1[q]-48;
		frame1::jbNum[i]->frame->x = a2 * 36;
	}
	for (int e = len;e < 9;e++) {
		frame1::jbNum[e]->frame->x = 0;
	}

};
void frame1::tk1FunC(DemoApp **app, ticker * tk) {
	frame1::timerFish += 15;
	unsigned int i = 0;
	unsigned int  len = frame1::fishConfigArr.size() - 5 + frame1::nowScane;
	for (i = 0;i < len;i++) {

		frame1::fishConfigArr[i]->frameFun(&frame1::fishArr, frame1::fishBox);
	}
	for (i = 0;i < frame1::fishArr.size();i++) {
		if (frame1::timerFish >= 200) {

			if (!frame1::fishArr[i]->inScreen()) {
				frame1::fishArr[i]->changeType("death");
			}
			if (i == len - 1) {
				frame1::timerFish = 0;
			}
		}
		frame1::fishArr[i]->frameFun();
	}
	for (i = 0;i < frame1::goldArr.size();i++) {
		frame1::goldArr[i]->frameFun();
	}
	for (i = 0;i < frame1::bulletArr2.size();i++) {
		if (frame1::bulletArr2[i]->bulletType == "bt") {
			frame1::bulletArr2[i]->moveForword();
		}
	}
	frame1::drawGoldNum();
}
DWORD WINAPI   frame1::tk1Fun() {
	/*
	string a = "";
	for (unsigned int q = 0;q < frame1::fishConfigArr.size();q++) {
	a=g_concat(a, "鱼");
	a = g_concat(a, q);
	a = g_concat(a, ":    ");
	a = g_concat(a, frame1::fishConfigArr[q]->fishConfigArr.size());
	a = g_concat(a, "\n");
	}
	(*app)->content->drawText(a, 0, 0);*/
	while (true) {
		Sleep(15);
		unsigned int i = 0;
		for (i = 0;i < frame1::bulletArr2.size();i++) {
			if (frame1::bulletArr2[i]->frameFun(&frame1::fishArr) == 1) {
				i--;
			};
		}
	}

	return  1;

}

//每一个精灵每一帧的处理函数
void frame1::frameSpriteInfo(sprite ** sp, int type) {

}
void frame1::removeBullet(bullet * b) {

	frame1::fishBox->removeChild(b->view);
	utils::vecRemove(frame1::bulletArr2, b);
	delete  b;
}
void frame1::removeFish(fish * b) {
	frame1::fishBox->removeChild(b->view);
	utils::vecRemove(frame1::fishArr, b);
	utils::vecRemove(b->createClass->fishConfigArr, b);
	delete b;
};
void frame1::removeGold(gold * b) {
	frame1::maxBox->removeChild(b->view);
	utils::vecRemove(frame1::goldArr, b);
	frame1::usegold += b->goldNum;

	delete b;
};
void frame1::onClick(int x, int y) {
	if (frame1::bk->inRect(frame1::app->mouse)) {
		frame1::app->nowScene = 2;
		frame1::fishBox->removeChild(frame1::bgArr[frame1::nowScane]);
	}
	if (frame1::isDown == true) {
		frame1::addBtn->img = frame1::app->content->getSoucre(L"img/Interface/cannon_plus.png");
		frame1::subtractBtn->img = frame1::app->content->getSoucre(L"img/Interface/cannon_minus.png");
		frame1::isDown = false;
	}
	if (frame1::addBtn->inRect(frame1::app->mouse)) {
		frame1::bottomBox->removeChild(frame1::bottom["pt"]);
		if (frame1::nowPt + 1 > 6) {
			frame1::nowPt=0;
		}
		else {
			frame1::nowPt++;
		}
		
		frame1::initPt2();
		return;
	}
	if (frame1::subtractBtn->inRect(frame1::app->mouse)) {
		frame1::bottomBox->removeChild(frame1::bottom["pt"]);
		if (frame1::nowPt - 1 < 0) {
			frame1::nowPt = 6;
		}
		else {
			frame1::nowPt--;
		}
		frame1::initPt2();
		return;
	}
	frame1::usegold -= (frame1::nowPt + 1);
	bullet * b = new bullet(frame1::app, frame1::scene, frame1::colObj, frame1::bottom["bullet"],
	frame1::bottom["wang"]);
	frame1::fishBox->addChild(b->view);
	b->hurt = frame1::nowPt + 3;
	b->view->pivot.x = 0.5;
	b->view->pivot.y = 1;
	b->view->angle = frame1::bottom["pt"]->angle;
	b->setX(frame1::bottom["pt"]->g_x+ (frame1::bottom["pt"]->getWidth()/2-b->view->getWidth()/2));
	b->setY(frame1::bottom["pt"]->g_y+ frame1::bottom["pt"]->getHeight()-b->view->getHeight());
	
	frame1::bulletArr2.push_back(b);
	b->removeScene = frame1::removeBullet;
}
void frame1::onMouseDown(int x, int y) {
	frame1::isDown = true;
	if (frame1::addBtn->inRect(frame1::app->mouse)) {
		frame1::addBtn->img = frame1::app->content->getSoucre(L"img/Interface/cannon_plus_down.png");
	}
	if (frame1::subtractBtn->inRect(frame1::app->mouse)) {
		frame1::subtractBtn->img = frame1::app->content->getSoucre(L"img/Interface/cannon_minus_down.png");
	}
};

void frame1::onKeyUp(int code) {
	if (code == 27) {//抬起esc键的操作
		//frame1::app->cancelFullSreen();
	}

};
void frame1::mouseMove(int x, int y) {
	if (frame1::addBtn->inRect(frame1::app->mouse)|| frame1::subtractBtn->inRect(frame1::app->mouse)) {
		return;
	}
	utils::usePoint p1 = {
		x,y
	};
	utils::usePoint p2 = {
		frame1::bottom["pt"]->g_x + frame1::bottom["pt"]->getWidth()/2,
		frame1::bottom["pt"]->g_y + frame1::bottom["pt"]->getHeight()
	};
	float angleTest = frame1::colObj->pointAngleInfo(p2,p1);

	frame1::bottom["pt"]->angle = round(angleTest+90);
}
void frame1::onClose() {
	frame1::saveObj->num = frame1::usegold;
	frame1::saveObj->writeFile();
};