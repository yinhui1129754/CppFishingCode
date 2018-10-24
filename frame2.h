#pragma once
class action;
class DemoApp;
class colVec;
namespace frame2 {
	extern action * scene;
	extern DemoApp * app;
	extern colVec *colObj;
	extern DisplayObject * maxBox;
	extern float zoom;
	extern void init(DemoApp * app, colVec * colObj);
	extern void visible();
	extern void onClick(int x, int y);
	extern vector <sprite * > spArr;
	extern sprite *initTxtSprite(string txt,int x,int y);
}