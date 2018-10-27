// stdafx.cpp : 只包括标准包含文件的源文件
// d2dWin32.pch 将作为预编译头
// stdafx.obj 将包含预编译类型信息

#include "../stdafx.h"
// TODO: 在 STDAFX.H 中引用任何所需的附加头文件，
//而不是在此文件中引用
wchar_t * g_chartowchar2(const char* cchar){
	wchar_t *m_wchar;

	int len = MultiByteToWideChar(CP_ACP, 0, cchar, strlen(cchar), NULL, 0);
	m_wchar = new wchar_t[len + 1];
	MultiByteToWideChar(CP_ACP, 0, cchar, strlen(cchar), m_wchar, len);
	m_wchar[len] = '\0';
	return m_wchar;
}

float random() {
	static int i = 0;
	i++;
	srand(time(NULL)*i);
	float a = (float)(rand() % 1000) / 1000;
	return a;
}