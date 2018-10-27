#pragma once
class Content;
class sprite;
class action;
class DemoApp
{
public:
	DemoApp();
	~DemoApp();
	HRESULT Initialize();
	void RunMessageLoop();
	void addFun(void (*fun)(DemoApp*));
	void addScene(action * scane);
	POINT * mouse  = new POINT();
	void fullSreen();
	void cancelFullSreen();
	bool isFull = false;
	void getSource(vector<string>);
	//DWORD  newT = 0;
	//DWORD oldT = 0;
public :
	Content * content;
	LARGE_INTEGER oldtime;
	LARGE_INTEGER newtime;
	LARGE_INTEGER frequency;
	oMap<string, void (*)(int,int)> use_onClick;
	oMap<string, void(*)(int, int)> use_onMouseDown;
	oMap<string, void(*)(int, int)> use_onMouseUp;
	oMap<string, void (*)(int, int)> use_onMouseMove;
	oMap<string, void(*)()>use_onClose;

	oMap<string, void (*)(int)> use_onKeyDown;
	oMap<string, void (*)(int)> use_onKeyUp;
	int width;
	int height;
	unsigned int nowScene = 0;
	float msTime = 0;
	vector<action *> sceneArr;
	string  status  = "DeamApp";
	HWND getHwnd();
	bool gameBool = true;
	LONG wLong;

private: 
	HRESULT OnRender();

	// Resize the render target.
	void OnResize(
		UINT width,
		UINT height
	);

	// The windows procedure.
	static LRESULT CALLBACK WndProc(
		HWND hWnd,
		UINT message,
		WPARAM wParam,
		LPARAM lParam
	);

	vector <void (*)(DemoApp*)> fun;
private:
	HWND m_hwnd;
};