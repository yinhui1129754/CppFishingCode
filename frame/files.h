#pragma once
class files
{
public:
	files();
	~files();
	void getFile(LPWSTR url);
	void files::close();
	void files::readFile();
	void files::size();
	void files::writeFile();
	void files::empty();
public:
	HANDLE hFile;
	DWORD  len;
	DWORD len2;
	string s;
	int num;
	string s2;
	char  lp[2000];

};

