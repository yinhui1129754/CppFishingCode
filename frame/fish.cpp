#include "../stdafx.h"
#include "fishConfig.h"

#include "fish.h"


fish::fish()
{
}

fish::fish(DemoApp * app, action * scene, colVec * colObj, sprite * img, float speed ) {
	this->app = (app);
	this->scene = (scene);
	this->colObj = (colObj);
	this->view = new sprite(this->app, (img)->img);
	this->speed = speed;
	this->scInfo = new sprite(0, 0);
};
fish::~fish()
{
}
bool fish::inScreen() {
	bool bl = this->colObj->aabb(&this->view, &this->scInfo);
	return bl;
}
void fish::frameFun() {
	if (this->type == "swim") {
		this->moveForword();
	/*	if (this->moveTime <= 0) {
			
			this->moveTime = this->moveAllTime;
		}
		else {
			this->moveTime--;
		}*/
			
			if (this->view->angle > this->maxAngle) {
				this->angleAdd = false;
			}
			else if (this->view->angle<this->minAngle) {
				this->angleAdd = true;
			}
			if (this->angleAdd) {
				this->view->angle++;
			}
			else {
				this->view->angle--;
			}
	}
	else if(this->type =="death") {
		if (this->deathFrameTime <= 0) {
			this->removeScene(this);

		}
		else {
			this->deathFrameTime--;
		}
	}


};
void fish::moveForword() {
	utils::usePoint ps = {
		this->view->g_x, this->view->g_y
	};
	utils::usePoint   l_p = { 0,0 };
	this->colObj->polarCoordinates(ps, this->view->angle, this->speed, l_p);
	this->setX(round(l_p.x));
	this->setY(round(l_p.y));
}
void fish::setX(float x) {
	this->view->setX(x);
}
void fish::setY(float y) {
	this->view->setY(y);
}

void fish::changeType(string type) {
	if (type != this->type) {
		this->type = type;
		if (this->type == "swim") {
			this->view->frameArr = this->swim;
		}
		else if (this->type == "death") {
			this->view->frameArr = this->death;
		}
	}
};