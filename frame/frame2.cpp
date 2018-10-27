#include "../stdafx.h"
#include "frame2.h"
#include "frame1.h"
#include "../instance/colVec.h"
action * frame2::scene = NULL;
DemoApp * frame2::app = NULL;
colVec * frame2::colObj = NULL;
DisplayObject * frame2::maxBox = NULL;
float frame2::zoom = 0.7;
vector <sprite * > frame2::spArr;
void frame2::init(DemoApp * app, colVec * colObj) {
	frame2::scene = new action(app);
	frame2::app = app;
	frame2::colObj = colObj;
	app->use_onClick["frame2"] = frame2::onClick;
	frame2::maxBox = new DisplayObject(0, 0);
	scene->addChild((sprite*)frame2::maxBox);
}
sprite * frame2::initTxtSprite(string txt, int x, int y) {
	sprite * txt1 = new sprite(x, y);
	txt1->spriteType = "textSprite";
	txt1->txt = txt;
	txt1->rgb = 0xffffff;
	txt1->width = txt1->getTxtWidth(frame2::app);
	return txt1;
}
void frame2::visible() {
	if (frame2::spArr.size() != 0) {
		return;
	}
	sprite * bg = new sprite(frame2::app, L"img/Interface/startbg.jpg");
	bg->width = app->width;
	bg->height = app->height;
	frame2::maxBox->addChild(bg);
	sprite * txt1 = frame2::initTxtSprite("请选择场景",15,20);
	frame2::maxBox->addChild(txt1);
	int w = 1024;
	int h = 682;

	frame2::spArr.push_back(new sprite(frame2::app, L"img/Interface/1a.jpg"));
	frame2::spArr.push_back(new sprite(frame2::app, L"img/Interface/1b.jpg"));
	frame2::spArr.push_back(new sprite(frame2::app, L"img/Interface/1c.jpg"));
	frame2::spArr.push_back(new sprite(frame2::app, L"img/Interface/1d.jpg"));
	frame2::spArr.push_back(new sprite(frame2::app, L"img/Interface/1e.jpg"));
	frame2::spArr.push_back(new sprite(frame2::app, L"img/Interface/1f.jpg"));
	frame2::spArr.push_back(frame2::initTxtSprite("这里有大乌龟", 0, 0));
	frame2::spArr.push_back(frame2::initTxtSprite("这里有电鳗鱼", 0, 0));
	frame2::spArr.push_back(frame2::initTxtSprite("这里有大鲨鱼", 0, 0));
	frame2::spArr.push_back(frame2::initTxtSprite("这里有黄金大鲨鱼", 0, 0));
	frame2::spArr.push_back(frame2::initTxtSprite("这里大珍珠", 0, 0));
	frame2::spArr.push_back(frame2::initTxtSprite("这里有传说中的美人鱼哦！", 0, 0));

	float zoom = (float)(300.f / w);
	int x = 0;
	int y = 0;
	bool b1 = true;
	for (unsigned int i = 0;i < 6;i++) {
		frame2::spArr[i]->width = w;
		frame2::spArr[i]->height = h;
		x =(i%3)* (300 + 50)+85;
		y = 320 * (int)(i / 3)+80;
		frame2::spArr[i]->use_int["useInt"] = i;

		frame2::maxBox->addChild(frame2::spArr[i]);
		frame2::spArr[i]->setX(x);
		frame2::spArr[i]->zoom = zoom;
		frame2::spArr[i]->setY(y);

		frame2::maxBox->addChild(frame2::spArr[i+6]);
		frame2::spArr[i+6]->setX(x);
		frame2::spArr[i+6]->setY(y+ frame2::spArr[i]->getHeight());
	}
};

void frame2::onClick(int x, int y) {
	

	unsigned int len = frame2::spArr.size();
	for (unsigned int i = 0;i < len;i++) {
		if (frame2::spArr[i]->inRect(frame2::app->mouse)) {
			frame1::nowScane = frame2::spArr[i]->use_int["useInt"];
			frame2::app->nowScene = 1;
			frame1::visible();
		}
	}
}