#pragma once
namespace utils {
	struct usePoint
	{
		float x;
		float y;
	};
	template<class T>
	bool vecRemove(vector<T *> & vc, T * sp) {
		vector<T *>::iterator s = find(vc.begin(),vc.end(),sp);

		vc.erase(s);
		return true;
	}
	/*template<typename t>
void log(const t &v1) {
	stringstream ss;
	ss << v1;
	LPWSTR a = g_chartowchar2(ss.str().c_str());
	OutputDebugString(a);
}*/
	struct useSpSt {
		float x; 
		float y;
		int width; 
		int height; 
		float angle;
		float pivotX; 
		float pivotY;
	};
}