#include "../stdafx.h"
#include "gold.h"
#include "fish.h"
#include "bullet.h"
#include "frame1.h"

template<typename t>
void log(const t &v1) {
	stringstream ss;
	ss << v1;
	LPWSTR a = g_chartowchar2(ss.str().c_str());
	OutputDebugString(a);
}

bullet::bullet()
{
}


bullet::~bullet()
{
}
bullet::bullet(DemoApp * app, action * scene, colVec  * colObj,sprite * bt,sprite * wang, int hurt, float speed) {
	this->app = (app);
	this->scene = (scene);
	this->colObj = (colObj);
	this->bt = bt;
	this->wang = wang;
	this->hurt = hurt;
	this->speed = speed;
	this->view = new sprite(this->app, this->bt->img);
	this->changeType("bt");
	this->scInfo= new sprite(0, 0);
	this->scInfo->width = this->app->width ;
	this->scInfo->height = this->app->height ;
};
void bullet::moveForword() {
	utils::usePoint ps = {
		this->view->g_x, this->view->g_y
	};
	utils::usePoint   l_p = { 0,0 };
	this->colObj->polarCoordinates(ps, this->view->angle + 270.f, this->speed,l_p);

	this->setX(l_p.x);
	this->setY(l_p.y);
};
int bullet::frameFun(vector<fish *>*fishArr) {
	if (this->bulletType == "bt") {

		if (!this->inScreen()) {
			this->changeType("wang");
			return 1;
		}
		//this->moveForword();

	}
	else if (this->bulletType == "wang") {
		if (this->w_time<=0) {
			this->removeScene(this);
			return 0;
		}
		else {
			this->w_time--;
		}
	}
	this->isTest(fishArr);
	return 0;
};
void initGold(string img,fish fs,int i,int xa, int num) {
	gold * l_gd = new gold();
	l_gd->view = new sprite(frame1::app, frame1::bottom[img]->img);
	frame1::initAmt2(l_gd->view, 0, 60, 60, 10, 1);
	l_gd->removeScren = frame1::removeGold;
	l_gd->goldNum = num;
	l_gd->setX(fs.view->g_x + i*xa);
	l_gd->setY(fs.view->g_y);
	l_gd->startPoint.x = l_gd->view->g_x;
	l_gd->startPoint.y = l_gd->view->g_y;
	l_gd->endPoint = {
		frame1::bottomBox->g_x,
		frame1::bottomBox->g_y + 10,
	};
	l_gd->getCenterPoint();
	frame1::goldArr.push_back(l_gd);
	frame1::maxBox->addChild(l_gd->view);
}
void bullet::createGold(fish * fs) {
	int g = floor(fs->getGold / 10);
	int y = fs->getGold % 10;
	int xa = 50;
	for (int i = 0;i < g;i++) {
		initGold("jin", *fs, i, xa, 10);
	}
	for (int i = 0;i < y;i++) {
		initGold("yin", *fs, i, xa, 1);
	}
};
void bullet::isTest(vector<fish *>*fishArr) {
	unsigned int len = fishArr->size();
	if (this->bulletType == "bt") {
		for (unsigned int i = 0;i < len;i++) {
			fish * l_fs = (*fishArr)[i];
			if (this->colObj->obb(&this->view, &l_fs->view)&& l_fs->type=="swim") {
				this->changeType("wang");
				if (random() * 200 < ((this->hurt + 1) * 10 - l_fs->deathInt) || random() * 2<0.01*this->hurt) {
					l_fs->changeType("death");
					this->createGold(l_fs);
				}
				return;
			};
		}
	}
	else if (this->bulletType == "wang") {
		if (!this->w_time % 5 == 0) {
			return;
		}
		for (unsigned int i = 0;i < len;i++) {
			fish * l_fs = (*fishArr)[i];
			if (this->colObj->obb(&this->view, &l_fs->view) && l_fs->type == "swim") {
				if (random() * 200 <((this->hurt + 1) * 10 - l_fs->deathInt)) {
					l_fs->changeType("death");
					this->createGold(l_fs);
					return;
				}
			};
		}
	}

};
bool bullet::inScreen() {
	bool bl= this->colObj->aabb(&this->view, &this->scInfo);
	return bl;
}
void bullet::changeType(string type) {
	this->bulletType = type;
	if (type == "bt") {
		this->view->img = this->bt->img;
		this->view->width = this ->bt->width;
		this->view->height = this->bt->height;
	}
	else if (type == "wang") {
		this->view->img = this->wang->img;
		this->view->width = this->wang->width;
		this->view->height = this->wang->height;
		this->view->pivot.x= 0.5;
		this->view->pivot.y = 0.5;
		this->setX(this->view->g_x - this->view->width / 2);
		this->setY(this->view->g_y - this->view->height / 2);
	}
}
void bullet::setX(float x) {
	this->view->setX(x);
}
void bullet::setY(float y) {
	this->view->setY(y);
}