#include "../stdafx.h"
#include "../Resource.h"
#include "../trigger/createBefore.h"

DemoApp::DemoApp() :
	m_hwnd(NULL),
	content(NULL)
{

}

DemoApp::~DemoApp()
{

}

void DemoApp::addScene(action * scane) {
		this->sceneArr.push_back(scane);
};
//全屏
void DemoApp::fullSreen() {
	//int cx = GetSysTemMetrice(SM_CXSCREEN);
	if (this->isFull) {
		return;
	}
	this->isFull = true;
	int width = GetSystemMetrics(SM_CXSCREEN);
	int height =  GetSystemMetrics(SM_CYSCREEN);
	this->wLong = GetWindowLong(m_hwnd, GWL_STYLE);
	SetWindowLong(m_hwnd, GWL_STYLE, WS_POPUP); 
	SetWindowPos(this->m_hwnd, HWND_TOPMOST, 0, 0, width, height, SWP_SHOWWINDOW);
}
//取消全屏
void DemoApp::cancelFullSreen() {
		if (!this->isFull) {
			return;
		}
		this->isFull = false;
		SetWindowLong(m_hwnd, GWL_STYLE, this->wLong);
		SetWindowPos(this->m_hwnd, HWND_NOTOPMOST, 0, 0, width, height, SWP_SHOWWINDOW);
}
void DemoApp::RunMessageLoop()
{
	MSG msg;
	BOOL isLoop = TRUE;

	QueryPerformanceFrequency(&this->frequency);
	while (isLoop)
	{
		if (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE)) {
			TranslateMessage(&msg);
			DispatchMessage(&msg);
			if (msg.message == WM_QUIT)
			{
				isLoop = FALSE;
			}
		}
		if (!this->gameBool) {
			//窗口处于非激活状态防止cpu爆炸
			Sleep(10);
		}
		this->content->beginDraw();
		QueryPerformanceCounter(&this->newtime);
		this->msTime = ((float)(newtime.QuadPart - oldtime.QuadPart) / frequency.QuadPart * 1000);
		
		if (this->msTime >=(int)1000/70)
		{
			this->content->clear();
			this->OnRender();
			QueryPerformanceCounter(&this->oldtime);
		}
		this->content->closeDraw();
	}

	//CloseHandle(this->thread1);
	
}
HRESULT DemoApp::Initialize()
{
	HRESULT hr=S_OK;

	// Initialize device-indpendent resources, such
	// as the Direct2D factory.
	if (SUCCEEDED(hr))
	{
		// Register the window class.
		WNDCLASSEX wcex = { sizeof(WNDCLASSEX) };
		wcex.style = CS_HREDRAW | CS_VREDRAW;
		wcex.lpfnWndProc = DemoApp::WndProc;
		wcex.cbClsExtra = 0;
		wcex.cbWndExtra = sizeof(LONG_PTR);
		wcex.hInstance = HINST_THISCOMPONENT;
		wcex.hbrBackground = NULL;
		wcex.lpszMenuName = NULL;
		wcex.hCursor = LoadCursor(NULL, IDI_APPLICATION);
		wcex.lpszClassName = L"MXSJ";
		wcex.hIcon = LoadIcon(HINST_THISCOMPONENT, (LPCTSTR)IDI_D2DWIN32);
		RegisterClassEx(&wcex);
			



		// Create the window.
		m_hwnd = CreateWindow(
			L"MXSJ",
			L"捕鱼人",
			WS_OVERLAPPEDWINDOW^WS_MAXIMIZEBOX^WS_THICKFRAME,
			CW_USEDEFAULT,
			CW_USEDEFAULT,
			1200,
			750,
			NULL,
			NULL,
			HINST_THISCOMPONENT,
			this
		);
		hr = m_hwnd ? S_OK : E_FAIL;
		content = new Content(m_hwnd);
		content->strokeStyle(0xff00ff, 1);
		content->lineWidth = 2;
		content->fillStyle(0xffff00, 1);
		createBefore::createWindowBefore(this);
		
	
		
		if (SUCCEEDED(hr))
		{
			ShowWindow(m_hwnd, SW_SHOWNORMAL);
			UpdateWindow(m_hwnd);
		}

	}
	createBefore::createWindow(this);
	return hr;
}
/*void DemoApp::addScene(action * scane) {
	this->sceneArr.push_back(scane);
};*/
void DemoApp::addFun(void (*funs)(DemoApp *)) {
	vector<void (*)(DemoApp*)>::iterator it;
	it = find(this->fun.begin(), this->fun.end(), (funs));
	if (it == this->fun.end()) {
		(this->fun).push_back((funs));
	}
};
HWND DemoApp::getHwnd() {
	return this->m_hwnd;
};
LRESULT CALLBACK DemoApp::WndProc(HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	LRESULT result = 0;
	WORD  isActive = HIWORD(wParam);
	if (message == WM_CREATE)
	{
		LPCREATESTRUCT pcs = (LPCREATESTRUCT)lParam;

		DemoApp *pDemoApp = (DemoApp *)pcs->lpCreateParams;
		RECT rc;
		GetClientRect(hwnd,&rc);
		pDemoApp->width = rc.right - rc.left;
		pDemoApp->height = rc.bottom - rc.top;

		::SetWindowLongPtrW(
			hwnd,
			GWLP_USERDATA,
			PtrToUlong(pDemoApp)
		);
		
		result = 1;
	}
	else
	{
		DemoApp *pDemoApp = reinterpret_cast<DemoApp *>(static_cast<LONG_PTR>(
			::GetWindowLongPtrW(
				hwnd,
				GWLP_USERDATA
			)));
		//
		if (pDemoApp == NULL) {
			return DefWindowProc(hwnd, message, wParam, lParam);
		}
		
		bool wasHandled = false;

		if (pDemoApp)
		{


			switch (message)
			{
			case WM_SIZE:
			{
				
				UINT width = LOWORD(lParam);
				UINT height = HIWORD(lParam);
				pDemoApp->OnResize(width, height);
			}
			result = 0;
			wasHandled = true;
			break;
			case WM_KEYUP:
				messageMapping::onKeyUp(wParam);
				result = 0;
				wasHandled = true;
				break;
			case WM_KEYDOWN:
				messageMapping::onKeyDown(wParam);
				result = 0;
				wasHandled = true;
				break;
			case WM_MOUSEMOVE:
				pDemoApp->mouse->x = LOWORD(lParam);
				pDemoApp->mouse->y = HIWORD(lParam);
				messageMapping::onMouseMove(pDemoApp->mouse->x, pDemoApp->mouse->y);
				result = 0;
				wasHandled = true;
				break;
			case WM_LBUTTONUP:
				pDemoApp->mouse->x=LOWORD(lParam);
				pDemoApp->mouse->y = HIWORD(lParam);
				messageMapping::onMouseUp(pDemoApp->mouse->x, pDemoApp->mouse->y);
				messageMapping::onClick(pDemoApp->mouse->x, pDemoApp->mouse->y);
				result = 1;
				wasHandled = true;
				break;
			case WM_LBUTTONDOWN:
				pDemoApp->mouse->x = LOWORD(lParam);
				pDemoApp->mouse->y = HIWORD(lParam);
				messageMapping::onMouseDown(pDemoApp->mouse->x, pDemoApp->mouse->y);
				result = 1;
				wasHandled = true;
				break;
			case WM_DISPLAYCHANGE:
			{
				InvalidateRect(hwnd, NULL, FALSE);
			}
			result = 0;
			wasHandled = true;
			break;
			case WM_ACTIVATE:
				if (isActive > 0) {
					pDemoApp->gameBool = false;
				}
				else {
					pDemoApp->gameBool = true;
				}
				
				result = 0;
				wasHandled = true;
				break;
			case WM_DESTROY:
			{
				
				messageMapping::onClose();
				PostQuitMessage(0);
			}
			result = 1;
			wasHandled = true;
			break;
			}
		}

		if (!wasHandled)
		{
			result = DefWindowProc(hwnd, message, wParam, lParam);
		}
	}

	return result;
}
HRESULT DemoApp::OnRender()
{
	LRESULT hr = S_OK;

	for (unsigned int i = 0; i < (this->fun).size();i++)
	{
		(this->fun)[i](this);
	}

	return hr;
}
void DemoApp::OnResize(UINT width, UINT height)
{

}
void DemoApp::getSource(vector<string> arr) {
	for (unsigned int i=0;i < arr.size();i++) {
		this->content->getSoucre(g_chartowchar2(arr[i].c_str()));
	}
};