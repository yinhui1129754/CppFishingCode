// d2dWin32.cpp : 定义应用程序的入口点。
//

#include "../stdafx.h"
#include "d2dWin32.h"
//#include "frame0.h"
void frame1(DemoApp*);

int APIENTRY wWinMain(_In_ HINSTANCE hInstance,
                     _In_opt_ HINSTANCE hPrevInstance,
                     _In_ LPWSTR    lpCmdLine,
                     _In_ int       nCmdShow)
{
    UNREFERENCED_PARAMETER(hPrevInstance);
    UNREFERENCED_PARAMETER(lpCmdLine);

	// Use HeapSetInformation to specify that the process should
	// terminate if the heap manager detects an error in any heap used
	// by the process.
	// The return value is ignored, because we want to continue running in the
	// unlikely event that HeapSetInformation fails.
	HeapSetInformation(NULL, HeapEnableTerminationOnCorruption, NULL, 0);

	if (SUCCEEDED(CoInitialize(NULL)))
	{
		{
			DemoApp app;
			app.addFun(frame1);
			if (SUCCEEDED(app.Initialize()))
			{
				app.RunMessageLoop();
			}
		}
		CoUninitialize();
	}

	return 0;
}


void frame1(DemoApp *app) {
	if (!(app)->sceneArr.empty()) {
		(app)->sceneArr[(app)->nowScene]->render(&app);
	}
	/*unsigned int len = frame0::p1.size();
	for (unsigned int i = 0;i < len;i++) {
		(app)->content->drawArc(frame0::p1[i].x, frame0::p1[i].y, 10, 10);
	}*/
}