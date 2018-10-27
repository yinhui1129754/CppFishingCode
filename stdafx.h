// stdafx.h : 标准系统包含文件的包含文件，
// 或是经常使用但不常更改的
// 特定于项目的包含文件
//

#pragma once

#include "instance/targetver.h"

#define WIN32_LEAN_AND_MEAN             // 从 Windows 头中排除极少使用的资料
// Windows 头文件: 
#include <windows.h>

#include <functional>
// C 运行时头文件
#include <stdlib.h>
#include <malloc.h>
#include <memory.h>
#include <wchar.h>
//C++运行库
#include <iostream>
#include <thread>
#include <sstream>

#include <set>
#define M_PI       3.14159265358979323846   // pi
#include <cmath>
#include <time.h>
// TODO:  在此处引用程序需要的其他头文件
#include <d2d1.h>
#include <d2d1helper.h>
#include <dwrite.h>
#include <wincodec.h>
#pragma comment(lib,"d2d1.lib")
#pragma comment (lib, "dwrite.lib")
#include <vector>
using namespace std;
#include "instance/utils.h"
#include"instance/oMap.h"
//#include "oMap.h"
template<class Interface>
inline void SafeRelease(
	Interface **ppInterfaceToRelease
)
{
	if (*ppInterfaceToRelease != NULL)
	{
		(*ppInterfaceToRelease)->Release();

		(*ppInterfaceToRelease) = NULL;
	}
}


#ifndef Assert
#if defined( DEBUG ) || defined( _DEBUG )
#define Assert(b) do {if (!(b)) {OutputDebugStringA("Assert: " #b "\n");}} while(0)
#else
#define Assert(b)
#endif //DEBUG || _DEBUG
#endif



#ifndef HINST_THISCOMPONENT
EXTERN_C IMAGE_DOS_HEADER __ImageBase;
#define HINST_THISCOMPONENT ((HINSTANCE)&__ImageBase)
#endif
wchar_t * g_chartowchar2(const char* cchar);
template <typename T1, typename T2>
string g_concat(const T1 &v1, const T2 &v2)
{
	stringstream ss;
	ss << v1 << v2;
	return ss.str();
}
float random();
typedef struct  {
	int x;
	int y;
	int width;
	int height;
} u_rect;


#include "render/ticker.h"
#include "render/action.h"
#include "render/sprite.h"
#include "render/Content.h"
#include "instance/DemoApp.h"
#include "instance/colVec.h"