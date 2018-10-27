#include "../stdafx.h"
#include "frame0.h"

#include "frame2.h"
#include "../instance/colVec.h"
//action * frame0::scene = NULL;
action *frame0::scene = NULL;
DemoApp * frame0::app = NULL;
colVec * frame0::colObj = NULL;
DisplayObject * frame0::maxBox = NULL;
float frame0::zoom = 0.7;
bool frame0::isInit = false;
vector <utils::usePoint> frame0::p1;
void frame0::init(DemoApp * app, colVec * colObj){
	frame0::scene = new action(app);
	frame0::app = app;

	frame0::colObj = colObj;
	app->use_onClick["frame0"] = frame0::onClick;
	frame0::maxBox = new DisplayObject(0, 0);
	scene->addChild((sprite*)frame0::maxBox);
	
}
void frame0::visible(){

	sprite * bg = new sprite(frame0::app,L"img/Interface/startbg.jpg");
	bg->width = app->width;
	bg->height = app->height;
	
	sprite * lg = new sprite(frame0::app, L"img/Interface/login.png");
	lg->zoom = frame0::zoom;
	
	sprite * sn = new sprite(frame0::app, L"img/Interface/sign.png");
	sn->zoom = frame0::zoom;
	sn->setId("start");

	frame0::maxBox->addChild(bg);
	frame0::maxBox->addChild(lg);
	frame0::maxBox->addChild(sn);

	lg->setX((bg->getWidth() / 2 - lg->getWidth() / 2));
	lg->setY((bg->getHeight() / 2 - lg->getHeight() / 2)- bg->getHeight()/100*15);

	sn->setX((bg->getWidth() / 2 - sn->getWidth() / 2));
	sn->setY((bg->getHeight() / 2 - lg->getHeight() / 2) - bg->getHeight() / 100 * 15+lg->getHeight()+30);

	
};
void frame0::onClick(int x, int y) {
	sprite * sn = frame0::maxBox->getChildById("start");

	if (sn->inRect(frame0::app->mouse)) {	

		app->nowScene = 2;
		frame2::visible();
	}
}

