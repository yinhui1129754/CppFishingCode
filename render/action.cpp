#include "../stdafx.h"
#include "action.h"
action::action(DemoApp * app)
{
	this->Container = new DisplayObject();
	this->app = app;
}


action::~action()
{

}
void action::addChild(sprite * child) {
	this->Container->addChild(child);
}
void action::addTicker(ticker * tk) {
	this->tk.push_back(tk);
}
ticker * action::getTickerById(string id) {
	unsigned int len = this->tk.size();
	for (unsigned int i = 0;i < len; i++) {
		if (this->tk[i]->id == id) {
			return this->tk[i];
		}
	}
	return NULL;
};
void action::render(DemoApp ** app) {
	this->Container->render(this->app);
	unsigned int len = this->tk.size();
	for (unsigned int i = 0;i < len;i++) {
		this->tk[i]->render(app);
	}
}