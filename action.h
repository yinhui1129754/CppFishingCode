#pragma once
//#include "DemoApp.h"
class DisplayObject;
class DemoApp;
class ticker;
class sprite;
class action
{
public:
	action(DemoApp * app);
	~action();
	void render (DemoApp ** app);
	void addTicker(ticker * tk);
	ticker * getTickerById(string id);
	void addChild(sprite *);
public:
	vector <ticker *> tk;
public:
	string  status = "action";
	DisplayObject * Container;
	DemoApp * app;
	

};

