#include "../stdafx.h"
#include "fish.h"
#include "frame1.h"
#include "fishConfig.h"


fishConfig::fishConfig()
{
}
fishConfig::fishConfig(DemoApp * app, action * scene, colVec * colObj, sprite * img, void(*removeScene)(fish * b)) {

	this->app = (app);
	this->scene = (scene);
	this->colObj = (colObj);
	this->img = img;
	//定义鱼出来的角度信息 一个二维数组
	vector<int> typeA1;
	typeA1.push_back(0);
	typeA1.push_back(1);
	typeA1.push_back(2);
	this->type1.push_back(typeA1);
	vector<int> typeA2;
	typeA2.push_back(3);
	typeA2.push_back(4);
	typeA2.push_back(5);
	this->type1.push_back(typeA2);
	vector<int> typeA3;
	typeA3.push_back(3);
	typeA3.push_back(4);
	typeA3.push_back(5);
	typeA3.push_back(6);
	typeA3.push_back(7);
	typeA3.push_back(8);
	this->type1.push_back(typeA3);
	vector<int> typeA4;
	typeA4.push_back(0);
	typeA4.push_back(1);
	typeA4.push_back(2);
	typeA4.push_back(9);
	typeA4.push_back(10);
	typeA4.push_back(11);
	typeA4.push_back(12);
	typeA4.push_back(13);
	typeA4.push_back(14);
	this->type1.push_back(typeA4);
	vector<int> typeA5;
	typeA5.push_back(9);
	typeA5.push_back(10);
	typeA5.push_back(11);
	this->type1.push_back(typeA5);

	vector<int> typeA6;
	typeA6.push_back(6);
	typeA6.push_back(7);
	typeA6.push_back(8);
	this->type1.push_back(typeA6);
	this->removeScene = removeScene;
};

fishConfig::~fishConfig()
{
}
void fishConfig::frameFun(vector<fish *>* fishArr, DisplayObject *ds) {

	if (this->createTimmer <= 0) {
		this->createTimmer = this->createAllTimmer + this->createTimmerInt;
		for (int i = 0;i < this->createNum;i++) {
			this->createFish(fishArr, ds);
		}
	}
	else {
		this->createTimmer--;
	}
};
void fishConfig::setType(fish* l_fs, int type,int angType) {
	//解释鱼的角度信息
	if (type == 0) {
		l_fs->setX(-l_fs->view->width);
		l_fs->setY(0);
	}
	else if (type == 1) {
		l_fs->setX(this->app->width+l_fs->view->width);
		l_fs->setY(0);
	}
	else if (type == 2) {
		l_fs->setX(this->app->width + l_fs->view->width);
		l_fs->setY(this->app->height/2);
	}
	else if (type == 3) {

		l_fs->setX(-l_fs->view->width);
		l_fs->setY(this->app->height/2);
	}
	else if (type == 4) {
		l_fs->setX(-l_fs->view->width);
		l_fs->setY(this->app->height );
	}
	else if (type == 5) {
		l_fs->setX(this->app->width + l_fs->view->width);
		l_fs->setY(this->app->height);
	}
	//0-2 0-90度 3-5 90-180度 6-8 180-270度 9-11 270-360度 12-14 305-405度
	if (angType == 0) {
		l_fs->minAngle = 10 + random() * 90;
		l_fs->maxAngle = 90 + random() * 90;
	}
	else if (angType == 1) {
		l_fs->minAngle = 10 + random() * 30;
		l_fs->maxAngle = 60 + random() * 30;
	}
	else if (angType == 2) {
		l_fs->minAngle = 10 + random() * 10;
		l_fs->maxAngle = 20 + random() * 30;
	}
	else if (angType == 3) {
		l_fs->minAngle = 120 + random() * 20;
		l_fs->maxAngle = 140 + random() * 20;
		l_fs->view->angle = 135;
	}
	else if (angType == 4) {
		l_fs->minAngle = 160 + random() * 20;
		l_fs->maxAngle = 180 + random() * 20;
		l_fs->view->angle = 135;
	}
	else if (angType == 5) {
		l_fs->minAngle = 90 + random() * 45;
		l_fs->maxAngle = 135 + random() * 45;
		l_fs->view->angle = 135;
	}
	else if(angType == 6) {
		l_fs->minAngle = 180 + random() * 20;
		l_fs->maxAngle = 200 + random() * 20;
		l_fs->view->angle = 225;
	}
	else if (angType == 7) {
		l_fs->minAngle = 220 + random() * 20;
		l_fs->maxAngle = 240 + random() * 20;
		l_fs->view->angle = 225;
	}
	else if (angType == 8) {
		l_fs->minAngle = 240 + random() * 20;
		l_fs->maxAngle = 260 + random() * 270;
		l_fs->view->angle = 225;
	}
	else if (angType == 9) {
		l_fs->minAngle = 270 + random() * 20;
		l_fs->maxAngle = 290 + random() * 20;
		l_fs->view->angle = 305;
	}
	else if (angType == 10) {
		l_fs->minAngle = 290 + random() * 20;
		l_fs->maxAngle = 310 + random() * 20;
		l_fs->view->angle = 305;
	}
	else if (angType == 11) {
		l_fs->minAngle = 300 + random() * 20;
		l_fs->maxAngle = 340 + random() * 20;
		l_fs->view->angle = 305;
	}
	else if (angType == 12) {
		l_fs->minAngle = 305 + random() * 20;
		l_fs->maxAngle = 325 + random() * 20;
		l_fs->view->angle = 360;
	}
	else if (angType == 13) {
		l_fs->minAngle = 345 + random() * 20;
		l_fs->maxAngle = 365 + random() * 20;
		l_fs->view->angle = 360;
	}
	else if (angType == 14) {
		l_fs->minAngle = 365 + random() * 20;
		l_fs->maxAngle = 385 + random() * 20;
		l_fs->view->angle = 360;
	}

};
void fishConfig::createFish(vector<fish *> * fishArr, DisplayObject *ds) {
	if (this->fishConfigArr.size() > this->maxFish) {

		return;
	}
	//创建鱼这个对象
	fish * l_fs = new fish(app,scene,colObj,img,round(3+random()*3));
	//设置鱼的排泄
	l_fs->removeScene = this->removeScene;
	//设置鱼的游动动画
	this->setFishFrame(l_fs, startYSwim,fishW,fishH, swimNum,0,zoom);
	//设置鱼的死亡动画
	this->setFishFrame(l_fs, startYDeath, fishW, fishH, deathNum,1, zoom);
	//默认鱼一来就是游动的
	l_fs->view->frameArr = l_fs->swim;
	//随机调用一种鱼的出现方式
	float l_ran = random();
	float l_ran2 = random();
	unsigned int len1 = round(l_ran*(this->type1.size()-1));
	unsigned int len2 = round(l_ran2*(this->type1[len1].size() - 1));
	this->setType(l_fs, len1, this->type1[len1][len2]);

	//设置鱼的屏幕信息 一定要判断鱼游出去了就排泄掉
	l_fs->scInfo->width = this->app->width + l_fs->view->getWidth() * 2 + 100;
	l_fs->scInfo->height = this->app->height + l_fs->view->getHeight() * 2 + 100;
	l_fs->scInfo->setX(-l_fs->view->getWidth() - 50);
	l_fs->scInfo->setX(-l_fs->view->getHeight() - 50);
	l_fs->getGold = this->getGold;
	l_fs->deathInt = this->deathInt;
	l_fs->speed = this->speed*random()+2;
	//加入场景进行渲染
	ds->addChild(l_fs->view);
	fishArr->push_back(l_fs);
	this->fishConfigArr.push_back(l_fs);
	l_fs->createClass = this;
};
void fishConfig::setFishFrame(fish * fs, int startY, int w, int h, int num,int type,float zoom) {
	if (fs->view->width != w|| fs->view->height != h) {
		fs->view->width = w;
		fs->view->height = h;
		fs->view->zoom = zoom;
		fs->view->speedTime = 50;
		fs->view->spriteType = "animateSprite";
	}
	vector<u_rect  > arr;
	for (int i = 0;i < num;i++) {
		u_rect a = { 0,startY+h*i,w,h };
		arr.push_back(a);
	}
	if (type == 0) {
		fs->swim = arr;
	}
	else if (type == 1) {
		fs->death = arr;
	}
};