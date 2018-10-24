#pragma once
class Content
{
public:
		Content(HWND h_wnd);
		Content();
		~Content();
		//设置线样式
		void strokeStyle(UINT32 hex, FLOAT alpha);
		void setLineStyle(int model);
		//线条绘制
		/*app.content->initPath();
		app.content->beginPath(0, 0);
		app.content->addPoint(100, xxx);
		app.content->addPoint(80+xxx, xxx+20);
		app.content->closePath();
		app.content->stroke();
		app.content->releasePath();*/
		void initPath(D2D1_FILL_MODE mode = D2D1_FILL_MODE_ALTERNATE);
		void releasePath();
		void beginPath(int x, int y);
		void addPoint(int x, int y);
		void addPoint(D2D1_POINT_2F  point);
		void addBezier(D2D1_POINT_2F start,D2D1_POINT_2F center,D2D1_POINT_2F end);
		void addArc(int x, int y, int xSize, int ySize, int angle, D2D1_SWEEP_DIRECTION angleFx = D2D1_SWEEP_DIRECTION_COUNTER_CLOCKWISE, D2D1_ARC_SIZE size = D2D1_ARC_SIZE_SMALL);
		void closePath(D2D1_FIGURE_END type = D2D1_FIGURE_END_OPEN);
		void stroke();
		void fill();
		//设置填充样式
		void fillStyle(UINT32 hex, FLOAT alpha);
		//绘制线端
		void drawLine(int x, int y, int x2, int y2);
		//清除窗口
		void clear();
		//开始绘制
		void beginDraw();
		//结束绘制
		void closeDraw();
		//填充矩形
		void fillRect(int x, int y, int width, int height);
		void fillArc(int x, int y, int xWidth, int yWidth);
		void drawArc(int x, int y, int xWidth, int yWidth);
		void drawRect(int x, int y, int width, int height);
		//绘制图形1
		void drawImage(WCHAR * url,int x,int y);
		void drawImage(WCHAR * url, int x, int y,int width,int height);
		void drawImage(WCHAR * url, int x, int y, int zoom);
		void drawImage(WCHAR * url, int x, int y, int width, int height, int srcX, int srcY, int srcWidth, int srcHeight);
		//绘制图形2
		void drawImage(ID2D1Bitmap * img, int x, int y);
		void drawImage(ID2D1Bitmap * img, int x, int y, int width, int height);
		void drawImage(ID2D1Bitmap * img, int x, int y, int zoom);
		void drawImage(ID2D1Bitmap * img, int x, int y, int width, int height, int srcX, int srcY, int srcWidth, int srcHeight);
		void drawImage(ID2D1Bitmap * img, int x, int y, int width, int height, u_rect * frame);
		void fillImage(WCHAR * url, int x, int y, int width, int height, int srcX = 0, int srcY = 0, float xZoom = 1, float yZoom = 1, int angle = 0);
		void fillImage(ID2D1Bitmap * img, int x, int y, int width, int height, int srcX = 0, int srcY = 0, float xZoom = 1, float yZoom = 1, int angle = 0);
		//获取资源
		ID2D1Bitmap * Content::getSoucre(WCHAR * url);
		//变换
		void rotate(int angle,int x =0,int y = 0);
		void scale(int zoom, int x = 0, int y = 0);
		void skew(int angleX, int angleY, int x = 0, int y = 0);
		void trisition(int x, int y);
		void save();
		void restore();
		//绘制文字
		void drawText(LPWSTR  txt,int x,int y);
		void drawText(string  txt, int x, int y);
		void drawText(LPWSTR  txt, int x, int y,int w,int h);
		void drawText(string  txt, int x, int y,int w,int h);
		void getTextInfo(LPWSTR  txt, D2D1_SIZE_F& size);
	
		void getTextInfo(string  txt, D2D1_SIZE_F& size);
public:
	int lineWidth=1;
	int lineStyle = 0;//0 实线 1虚线
	IWICImagingFactory * m_imgFac;
	HWND p_hwnd;
	string status = "Content";
	D2D1_MATRIX_3X2_F m1;
	D2D1_MATRIX_3X2_F bufM1;

private:
	ID2D1Factory * m_fac;
	ID2D1HwndRenderTarget * m_render = NULL;
	ID2D1SolidColorBrush * pen = NULL;
	ID2D1SolidColorBrush *brush = NULL;
	ID2D1BitmapBrush * bitmapBrush;
	ID2D1StrokeStyle * m_lineStyle = NULL;
	vector <WCHAR *> imgName;
	vector <ID2D1Bitmap *> imgSource;
	IDWriteFactory * m_writeFac = NULL;
	IDWriteTextFormat * m_forMat = NULL;
	ID2D1PathGeometry * m_path = NULL;
	ID2D1GeometrySink *m_slink = NULL;

};

