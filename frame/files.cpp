#include "../stdafx.h"
#include "files.h"


files::files()
{
}


files::~files()
{
	
}
void files::getFile(LPWSTR url) {
	this->hFile = CreateFile(url, GENERIC_READ| GENERIC_WRITE, 0, NULL, OPEN_ALWAYS, FILE_ATTRIBUTE_NORMAL, 0);
	if (hFile == INVALID_HANDLE_VALUE) {
		MessageBox(NULL, L"´íÎó", L"txt", MB_OK);
	}
};
void files::close() {
	CloseHandle(this->hFile);
}
void files::size() {
	this->len = GetFileSize(this->hFile, NULL);
}
void files::readFile() {
	this->size();
	if (!ReadFile(this->hFile, this->lp, this->len, &this->len2, NULL)) {
		MessageBox(NULL, L"´íÎó", L"txt", MB_OK);
	};
	stringstream ss;
	ss << this->lp;
	this->s = ss.str();
	this->num=atoi(this->s.c_str());
}
void files::empty() {
	int lens = GetFileSize(this->hFile, NULL);
	stringstream ss;
	for (int i = 0;i < lens;i++) {
		ss << "\0";
	}

	this->s2 = ss.str();
	WriteFile(this->hFile, this->s2.c_str(), lens, &this->len2, NULL);
}
void files::writeFile() {
	SetFilePointer(this->hFile, 0, 0, FILE_BEGIN);
	stringstream ss;
	ss << this->num;
	this->s2 = ss.str();
	int len3 = this->s2.size();
	if (len3 < this->len) {
		len3 = this->len;
	}
	WriteFile(this->hFile, this->s2.c_str(), len3, &this->len2, NULL);
	SetEndOfFile(this->hFile);
}