#pragma once
#include "DisplayObject.h"
extern class DemoApp;
class sprite :public DisplayObject
{
public:
	sprite(int x,int y);
	sprite(DemoApp * app, WCHAR * url, string spriteType="default",int width=-1,int height = -1);
	sprite(DemoApp * app, ID2D1Bitmap * url, string spriteType = "default", int width = -1, int height = -1);
	~sprite();
	virtual void render(DemoApp*);
	u_rect * frame = NULL;
public:
	ID2D1Bitmap * img;
	string  status = "sprite";
	string spriteType = "default";//animateSprite fillSprite textSprite
	
	
	//animateSprite
	vector<u_rect  >frameArr;//帧数组
	unsigned int nowFrame = 0;//当前帧
	float speedTime = 0;//毫秒
	float speedNowTime = 0;//毫秒
	int loop = -1;
	void (*amtEnd)(sprite *);
	//fillSprite

	//textSprite
	string txt = "";
	UINT rgb = 0x000000;
	float  alpha = 1;
	float getTxtWidth(DemoApp * app);
	float getTxtHeight(DemoApp * app);
};

