#include "../stdafx.h"
#include "ticker.h"


ticker::ticker()
{

}
void ticker::start() {
	this->started = true;
};
void ticker::stop() {
	this->started = false;
};
void ticker::setTimmer(float time) {
	this->timmer = time;
};
void ticker::addFun(void(*fs)(DemoApp ** app, ticker *tk)) {
	this->tickerArr.push_back(fs);
}
void ticker::setId(string str) {
	this->id = str;
};
void ticker::render(DemoApp ** app) {
	if (this->started != true) {
		return;
	}
	this->newTimmer += (*app)->msTime;
	this->msTime = this->newTimmer;
	this->fpsTimmer += (*app)->msTime;
	if (this->newTimmer >= this->timmer) {
		this->fpsInt++;
		this->newTimmer = 0;
		unsigned int len = this->tickerArr.size();
		for (unsigned int i = 0;i < len;i++) {
			this->tickerArr[i](app,this);
		}
	
	}
	if (this->fpsTimmer >= 1000) {
		this->fps = this->fpsInt;
		this->fpsInt = 0;
		this->fpsTimmer = 0;
	}
}
ticker::~ticker()
{
}
