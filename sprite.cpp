#include "stdafx.h"
#include "sprite.h"
sprite::sprite(int x, int y) {
	this->x = x;
	this->y = y;
	this->initG_x();
	this->initG_y();
}
sprite::sprite(DemoApp * app, WCHAR * url, string spriteType, int w2, int h2)
{
	this->img = app->content->getSoucre(url);
	if (w2 == -1) {
		this->width = (int)this->img->GetSize().width;
	}
	else {
		this->width = w2;
	}
	if (h2 == -1) {
		this->height = (int)this->img->GetSize().height;
	}
	else {
		this->height = h2;
	}
}
sprite::sprite(DemoApp * app, ID2D1Bitmap *url, string spriteType, int w2, int h2)
{
	this->img = url;
	if (w2 == -1) {
		this->width = (int)this->img->GetSize().width;
	}
	else {
		this->width = w2;
	}
	if (h2 == -1) {
		this->height = (int)this->img->GetSize().height;
	}
	else {
		this->height = h2;
	}
}
float  sprite::getTxtWidth(DemoApp * app) {
	D2D1_SIZE_F size = {0,0};
//	string d = this->txt;
	LPWSTR  d = g_chartowchar2(this->txt.c_str());
	app->content->getTextInfo(d, size);
	return size.width;
};
float  sprite::getTxtHeight(DemoApp * app) {
	D2D1_SIZE_F size = { 0,0 };
	LPWSTR  d = g_chartowchar2(this->txt.c_str());
	app->content->getTextInfo(d, size);
	return size.height;
};
sprite::~sprite()
{

}
void sprite::render(DemoApp * app) {
	if (!this->visible) {
		return;
	}
	if (this->spriteType == "animateSprite") {
		unsigned int len = this->frameArr.size();
		if (this->speedNowTime + app->msTime >= this->speedTime) {
			this->speedNowTime = 0;
			if (this->nowFrame <len -1) {
				this->nowFrame++;
			}
			else {
				if (this->loop > 0) {
					this->loop--;
				
				}
				if (this->loop == 0) {

					this->amtEnd(this);
				}
				else {
					this->nowFrame = 0;
				}
				
			}
		}
		else {
			this->speedNowTime += app->msTime;
		}
		if (len >= 0 ) {

			this->frame = &(this->frameArr[this->nowFrame]);

		}
		else {
			this->frame = NULL;
		}
	}
	int x1 = 0;
	int y1 = 0;
	//绘制自己的变换情况
	app->content->save();
	if (this->angle != 0) {
		app->content->rotate(this->angle, this->g_x+this->getWidth()*this->pivot.x , this->g_y+this->getHeight()*this->pivot.y );
	}

	if (this->frame != NULL) {

		app->content->drawImage(this->img, this->g_x+ x1, this->g_y+y1, this->width*this->zoom, this->height*this->zoom,this->frame);
	}
	else if (this->spriteType == "fillSprite") {
		app->content->fillImage(this->img, this->g_x+ x1, this->g_y+ y1, this->width*this->zoom, this->height*this->zoom);
	}
	else if (this->spriteType == "textSprite") {
		app->content->strokeStyle(this->rgb, this->alpha);
		app->content->drawText(this->txt,this->g_x,this->g_y,this->width,this->height);
	}
	else {
		app->content->drawImage(this->img, this->g_x+ x1, this->g_y+ y1, this->width*this->zoom, this->height*this->zoom);
	}
	app->content->restore();
	//递归绘制所有子元素
	unsigned int len = this->children.size();
	for (unsigned int i = 0;i < len;i++) {
		if (this->children[i]->children.size() > 0) {
			this->children[i]->render(app);
		}
	}
}