#pragma once
extern  class DemoApp;

namespace createBefore {
	void createWindowBefore(DemoApp * app);
	void createWindow(DemoApp * app);
}
namespace messageMapping {
	void onClick(int x,int y);
	void onMouseDown(int x, int y);
	void onMouseUp(int x, int y);
	void onKeyDown(int code);
	void onKeyUp(int code);
	void onMouseMove(int x, int y);
	void onClose();
}